// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemData/WeaponData.h"
#include "Item/Weapon.h"
#include "Characters/BrunnhildeCharacter.h"
#include "InventoryComponent.h"


UWeaponData::UWeaponData() : UEquipmentData()
{
	ItemType = EItemTypes::EIT_WEAPON;
}

UWeaponData::UWeaponData( UWeaponData* WeaponData ) : UEquipmentData( WeaponData )
{
    Damage     = WeaponData->Damage;
}

void UWeaponData::OnEquiped( ABrunnhildeCharacter* Character )
{

	if ( nullptr == Character )
	{
		return ;
	}

	if ( nullptr == PickupMesh )
	{
		return;
	}


	// Create Weapon Actor
	AWeapon* Weapon = GetWorld()->SpawnActor<AWeapon>( Character->GetActorTransform().GetLocation(),
											          Character->GetActorTransform().GetRotation().Rotator() );
	SetActor( Weapon );

	if ( Weapon )
	{	
		Weapon->GetMeshComponent()->SetStaticMesh( PickupMesh );
		Weapon->Equip( Character, EquipedSocket );
	}

	return ;
}

void UWeaponData::OnUnEquiped( ABrunnhildeCharacter* Character )
{
	if ( nullptr == Character )
	{
		return;
	}

	if ( nullptr == ItemActor )
	{
		return;
	}

	ItemActor->UnEquip();
	GetWorld()->DestroyActor( ItemActor );
}

void UWeaponData::OnDrawn( ABrunnhildeCharacter* Character )
{
	if ( nullptr == Character )
	{
		return ;
	}
	AWeapon* Weapon = Cast<AWeapon>( ItemActor );
	if ( IsValid( Weapon ) )
	{
		Weapon->Drawn( Character, HoldSocket );
	}
	return ;
}

void UWeaponData::OnSeath( ABrunnhildeCharacter* Character )
{
	if ( nullptr == Character )
	{
		return;
	}
	AWeapon* Weapon = Cast<AWeapon>( ItemActor );
	if ( IsValid( Weapon ) )
	{
		Weapon->Sheath( Character, EquipedSocket );
	}
	return;
}