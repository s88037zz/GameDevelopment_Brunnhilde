// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemData/WeaponData.h"
#include "Characters/BrunnhildeCharacter.h"
#include "InventoryComponent.h"


UWeaponData::UWeaponData() : UEquipmentData()
{
	ItemType = EItemTypes::EIT_WEAPON;
}

UWeaponData::UWeaponData( UWeaponData* WeaponData ) : UEquipmentData( WeaponData )
{
    Damage = WeaponData->Damage;
}

void UWeaponData::EquipOn( ABrunnhildeCharacter* Character )
{
	if ( nullptr == Character )
	{
		return;
	}

	Character->Inventory->EquipItem( this );
	return;
}
