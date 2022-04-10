// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemData/WeaponData.h"
#include "Characters/BrunnhildeCharacter.h"
#include "InventoryComponent.h"

UWeaponData::UWeaponData( UWeaponData* WeaponData ) : UItemData( WeaponData )
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
