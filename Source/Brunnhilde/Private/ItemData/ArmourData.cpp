// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemData/ArmourData.h"
#include "Item/Armour.h"
#include "Games/BrunnhildeDef.h"
#include "Characters/BrunnhildeCharacter.h"
#include "InventoryComponent.h"


UArmourData::UArmourData() : UEquipmentData()
{
	ItemType = EItemTypes::EIT_ARMOUR_Head;
	switch ( ItemType )
	{
		case EItemTypes::EIT_ARMOUR_Head:
			EquipedSocket = DEFAULT_ARMOUR_HEAD_SOCKET;
			break;
		case EItemTypes::EIT_ARMOUR_Chest:
			EquipedSocket = DEFAULT_ARMOUR_CHEST_SOCKET;
			break;
		case EItemTypes::EIT_ARMOUR_Hand:
			EquipedSocket = DEFAULT_ARMOUR_HAND_SOCKET;
			break;
		case EItemTypes::EIT_ARMOUR_Feet:
			EquipedSocket = DEFAULT_ARMOUR_FEET_SOCKET;
			break;
		default:
			EquipedSocket = DEFAULT_ARMOUR_HEAD_SOCKET;
			return;
	}
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

void UArmourData::OnEquiped( ABrunnhildeCharacter* Character )
{
	if ( nullptr == Character )
	{
		return ;
	}
	// Let weapon can attach on character
	AArmour* Armour = GetWorld()->SpawnActor<AArmour>( Character->GetActorTransform().GetLocation(),
														Character->GetActorTransform().GetRotation().Rotator() );
	Armour->GetMeshComponent()->SetStaticMesh( PickupMesh );
	SetActor( Armour );
	Armour->Equip( Character, EquipedSocket );
	return;
}


void UArmourData::OnUnEquiped( ABrunnhildeCharacter* Character )
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