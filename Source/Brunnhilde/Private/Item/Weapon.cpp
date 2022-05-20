// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapon.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "BrunnhildeCharacter.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AWeapon::AWeapon(): AItem()
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

	ItemSetting.EquipedSocket = DEFAULT_WEAPON_EQEUIPED_SOCKET;
	ItemSetting.HoldSocket    = DEFAULT_WEAPON_HOLD_SOCKET;
}

AWeapon::AWeapon( AWeapon* Weapon ) 
:AItem( Weapon )
{
	AWeapon();
}

AItem* AWeapon::DeepCopy()
{
	AWeapon* Weapon = GetWorld()->SpawnActor< AWeapon >();
	Super::DeepCopyTo( Weapon );
	return Weapon;
}

void AWeapon::OnUse( ABrunnhildeCharacter* Character )
{
}

void AWeapon::OnEquiped( ABrunnhildeCharacter* Character )
{
	if ( Character )
	{
		// Let weapon can attach on character
 		AttachToComponent( Character->GetMesh(),
						   FAttachmentTransformRules::SnapToTargetIncludingScale,
						   FName( *ItemSetting.EquipedSocket ) );
		MeshCmp->SetStaticMesh( ItemSetting.PickupMesh );
		SetActorHiddenInGame( false );
		//SetActorEnableCollision( true )
		SetActorTickEnabled( true );
		SetOwner( Character );
	}
}


void AWeapon::OnUnEquiped( ABrunnhildeCharacter* Character )
{
	FDetachmentTransformRules Rule = FDetachmentTransformRules::KeepWorldTransform;
	DetachFromActor( Rule );
	MeshCmp->SetStaticMesh( nullptr );
	SetOwner( nullptr );
}

void AWeapon::OnDrawn( ABrunnhildeCharacter* Character )
{
	if ( IsValid( Character ) )
	{
		GetMeshComponent()->AttachToComponent( Character->GetMesh(), 
											   FAttachmentTransformRules::SnapToTargetIncludingScale,
											   FName( *ItemSetting.HoldSocket ) );
	}
}

void AWeapon::OnSheath( ABrunnhildeCharacter* ACharacter )

{
	ABrunnhildeCharacter* Character = Cast<ABrunnhildeCharacter>( ACharacter );
	if ( IsValid( Character ) )
	{
		GetMeshComponent()->AttachToComponent( Character->GetMesh(),
											   FAttachmentTransformRules::SnapToTargetIncludingScale,
											   FName( *ItemSetting.EquipedSocket ) );
	}
}

void AWeapon::HandleDrop()
{
    AActor* PlayerActor = UGameplayStatics::GetPlayerCharacter( GetWorld(), 0 );
    if ( PlayerActor )
    {
        ABrunnhildeCharacter* Character = Cast<ABrunnhildeCharacter>( PlayerActor );
        if ( Character )
        {
			FVector DroppedLocation = Character->GetObjectDroppedLocation();
			FDetachmentTransformRules DetachRule = FDetachmentTransformRules::KeepRelativeTransform;
            SetActorLocation( DroppedLocation );
            DetachFromActor( DetachRule );
			MeshCmp->RecreatePhysicsState(); // physic usually update in next frame
            MeshCmp->SetSimulatePhysics( true );
            SetOwner( nullptr );
		}
    }
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

        if ( OwnCharacter->CurrentState == ECharacterFSM::ECFSM_Attacking )
        {		
        }
		
	}
}

void AWeapon::ApplyDamage( AActor* DamagedActor, float BaseDamage, AController* EventInstigator, 
						   AActor* DamageCauser, TSubclassOf<UDamageType> DamageTypeClass )
{
	UGameplayStatics::ApplyDamage( DamagedActor, BaseDamage, EventInstigator,
								   DamageCauser, DamageTypeClass );
	CurElfEnergy += RechargeValue;
	CurElfEnergy = FMath::Clamp( CurElfEnergy, 0, MaxElfEnergy );
}