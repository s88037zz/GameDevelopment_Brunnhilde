// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Actions/FlinchAbility2.h"
#include "Item/Weapon.h"
#include "BrunnhildeCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"


void UFlinchAbility2::BeginAbility()
{
	GetControlCharacter()->OnTakeAnyDamage.AddDynamic( this, &UFlinchAbility2::OnTakeDamaged );
}

void UFlinchAbility2::OnTakeDamaged( AActor* DamagedActor, float Damage, const UDamageType* DamageType,
									AController* InstigatedBy, AActor* DamageCauser )
{
	if ( nullptr == FlinchMontage_L || nullptr == FlinchMontage_Mid || nullptr == FlinchMontage_R )
	{
		return;
	}

	if ( Cast< AWeapon >( DamageCauser ) )
	{
		AWeapon* Weapon = Cast< AWeapon >( DamageCauser );
		ABrunnhildeCharacter* OwnerActor = Cast< ABrunnhildeCharacter >( Weapon->GetOwner() );

		// Weapon Exist Owner And Not Belong You
		if ( Weapon && OwnerActor && OwnerActor != GetControlCharacter() )
		{
			// Check Owner Is Attacking And Self Don't Play Any Montage
			if ( nullptr == GetControlActiveMontage() )
			{

				DamagedCounter++;

				EDamagedDirection DamagedDirection = GetDamageDirection( Weapon );

				double Duration = 0.f;
				if ( EDamagedDirection::Front == DamagedDirection )
				{
					Duration = SetControlPlayAnimMontage( FlinchMontage_Mid );
				}
				else if ( EDamagedDirection::Right == DamagedDirection )
				{
					Duration = SetControlPlayAnimMontage( FlinchMontage_L );
				}
				else
				{
					Duration = SetControlPlayAnimMontage( FlinchMontage_R );
				}

				GetControlMovement()->DisableMovement();
				FTimerHandle TimerHandle = GetControlMovementTimeHandle();
				GetWorld()->GetTimerManager().SetTimer( TimerHandle, [this]()
				{
					GetControlMovement()->SetMovementMode( MOVE_Walking );
				}, Duration, false );
				
				GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake( OnTakeDamageShakingType );
			}

		}
	}
}


EDamagedDirection UFlinchAbility2::GetDamageDirection( AActor* DamagedCreator )
{
	FVector RightVector = UKismetMathLibrary::GetRightVector( GetControlCharacter()->GetActorRotation() );
	FVector DeltaVector = UKismetMathLibrary::GetDirectionUnitVector( GetControlCharacter()->GetActorLocation(), DamagedCreator->GetActorLocation() );
	float DotValue = FVector::DotProduct( RightVector, DeltaVector ) / ( RightVector.Size() * DeltaVector.Size() );
	float Rotation = FMath::Acos( DotValue );

	double Duration = 0;
	double LeftBound =  ( UKismetMathLibrary::GetPI() / 3 ) * 2;
	double RightBound = ( UKismetMathLibrary::GetPI() / 3 );

	// Attack Come From Mid
	if ( Rotation < LeftBound &&
		 Rotation > RightBound )
	{
		return EDamagedDirection::Front;
	}
	// Attack Come From Left
	else if ( Rotation > LeftBound )
	{
		return EDamagedDirection::Left;
	}
	// Attack Come From Right
	else
	{
		return EDamagedDirection::Right;
	}
}