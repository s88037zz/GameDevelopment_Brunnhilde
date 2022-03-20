// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "BrunnhildeCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootCmp = CreateDefaultSubobject<USceneComponent>( TEXT( "Root" ) );
	RootComponent = RootCmp;

	ArrowCmp = CreateDefaultSubobject<UArrowComponent>( TEXT( "Arrow" ) );
	ArrowCmp->SetArrowColor( FLinearColor::Blue );
	ArrowCmp->AttachToComponent( RootCmp, FAttachmentTransformRules::KeepRelativeTransform );

	MeshCmp = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "WeaponMesh" ) );
	MeshCmp->AttachToComponent( RootCmp, FAttachmentTransformRules::KeepRelativeTransform );
	MeshCmp->SetCollisionEnabled( ECollisionEnabled::NoCollision );

	BoxCmp = CreateDefaultSubobject<UBoxComponent>( TEXT( "HitBox" ) );
	BoxCmp->AttachToComponent( RootCmp, FAttachmentTransformRules::KeepRelativeTransform );
	BoxCmp->SetCollisionEnabled( ECollisionEnabled::QueryAndPhysics );

	LastOwnerAttackCounter = -1;
}

AWeapon::AWeapon( AWeapon* Weapon ) :AWeapon()
{
	Damage = Weapon->Damage;
}

void AWeapon::OnPickup( AActor* EquippedActor )
{

	if ( EquippedActor )
	{
		ABrunnhildeCharacter* Character = Cast<ABrunnhildeCharacter>( EquippedActor );
		if ( Character )
		{
			// Let weapon can attach on character
			AttachToComponent( Character->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, Character->BackWeaponSocket );
			SetOwner( EquippedActor );
		}
	}

}

AWeapon* AWeapon::OnPickup_Copy()
{
	AActor* PlayerActor = UGameplayStatics::GetPlayerPawn( GetWorld(), 0 );
	if ( PlayerActor )
	{
		ABrunnhildeCharacter* Character = Cast<ABrunnhildeCharacter>( PlayerActor );
		if ( Character )
		{
			// Let weapon can attach on character
			AWeapon* Copy = Duplicate();
			if ( Copy )
			{
                Copy->AttachToComponent( Character->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, Character->BackWeaponSocket );
                Copy->SetOwner( PlayerActor );
                Destroy();
                return Copy;
			}		
		}
	}
	return nullptr;
}

void AWeapon::OnDrop()
{
    AActor* PlayerActor = UGameplayStatics::GetPlayerCharacter( GetWorld(), 0 );
    if ( PlayerActor )
    {
        ABrunnhildeCharacter* Character = Cast<ABrunnhildeCharacter>( PlayerActor );
        if ( Character )
        {
			FVector DroppedLocation = Character->GetObjectDroppedLocation();
            SetActorLocation( DroppedLocation );
            DetachRootComponentFromParent( true );
			MeshCmp->RecreatePhysicsState(); // physic usually update in next frame
            MeshCmp->SetSimulatePhysics( true );
            SetOwner( nullptr );
		}
    }
}

AWeapon* AWeapon::Duplicate()
{	
	FActorSpawnParameters Params;
	AWeapon* Copy = GetWorld()->SpawnActor< AWeapon >( GetClass(),
													   GetActorLocation(),
													   FRotator::ZeroRotator, 
													   Params );
	return Copy;
}

void AWeapon::ApplyDamage02( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						   int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult )
{
	if( nullptr == GetOwner() )
	{
		return;
	}

	if ( nullptr == OtherActor )
	{
		return;
	}

	if( GetOwner() == OtherActor )
	{
		return;
	}

	if ( Cast<ABrunnhildeCharacter>(GetOwner()) &&
		OtherActor->IsA( ABrunnhildeCharacter::StaticClass() ) )
	{
		ABrunnhildeCharacter* OwnCharacter = Cast<ABrunnhildeCharacter>( GetOwner() );
        ABrunnhildeCharacter* DamagedCharacter = Cast<ABrunnhildeCharacter>( OtherActor );

        if ( OwnCharacter->IsAttacking() )
        {
            UAbility2* ActiveAbility = OwnCharacter->GetCurrentActiveAbility();
			if( Cast<UAttackAbility>( ActiveAbility ) &&
				LastOwnerAttackCounter != Cast<UAttackAbility>( ActiveAbility )->AttackCounter )
			{
				UGameplayStatics::ApplyDamage( DamagedCharacter, Damage, nullptr, this, UDamageType::StaticClass() );
				LastOwnerAttackCounter = Cast<UAttackAbility>( ActiveAbility )->AttackCounter;
				
				UAnimMontage* CurrentMontage = OwnCharacter->GetCurrentMontage();
				if ( !CurrentMontage->IsValidLowLevel() ) 
				{
					return;
				};

				double delay = OwnCharacter->GetMontageLeftTime( CurrentMontage, OwnCharacter->GetMesh() );
				GetWorld()->GetTimerManager().SetTimer( ResetCounterHandle, [this]()
				{
					LastOwnerAttackCounter = -1;
				}, delay, false );
			}
        }
		
	}
}


// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	//BoxCmp->OnComponentBeginOverlap.AddDynamic( this, &AWeapon::ApplyDamage );
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

