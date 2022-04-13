// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemData/ArmourData.h"
#include "Characters/BrunnhildeCharacter.h"
#include "InventoryComponent.h"


UArmourData::UArmourData() : UEquipmentData()
{
	ItemType = EItemTypes::EIT_ARMOUR_Head;
}

UArmourData::UArmourData( UArmourData* ArmourData ) : UEquipmentData( ArmourData )
{
    Constitution    = ArmourData->Constitution;
    Mentality       = ArmourData->Mentality;
	Endurance       = ArmourData->Endurance;
	Strength        = ArmourData->Strength;
	Dexterity       = ArmourData->Dexterity;
	Intelligence    = ArmourData->Intelligence;
	Wisdom          = ArmourData->Wisdom;
}

void UArmourData::EquipOn( ABrunnhildeCharacter* Character )
{
	if ( nullptr == Character )
	{
		return;
	}

	Character->Inventory->EquipItem( this );
	return;
}
