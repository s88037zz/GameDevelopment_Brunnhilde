// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Item.h"

AItem::AItem()
{
}

AItem::AItem( AItem* Item ) : AItem()
{
	ItemSetting = Item->GetItemSetting();
}


AItem* AItem::DeepCopy()
{
	AItem* CopyItem = GetWorld()->SpawnActor< AItem >();
	CopyItem->ItemSetting = ItemSetting;
	return CopyItem;
}

void AItem::DeepCopyTo( AItem* CopyItem )
{
	if ( !IsValid( CopyItem ) )
	{
		return;
	}
	CopyItem->ItemSetting = ItemSetting;
}

void AItem::SetupPickMesh()
{
    MeshCmp->SetStaticMesh( ItemSetting.PickupMesh );
}

void AItem::SetupDroppedMesh()
{
    MeshCmp->SetStaticMesh( ItemSetting.DroppedMesh );
}

//for regular properties:
void AItem::PostEditChangeProperty( struct FPropertyChangedEvent& e )
{
	FName PropertyName = ( e.Property != NULL ) ? e.Property->GetFName() : NAME_None;
	if ( PropertyName == GET_MEMBER_NAME_CHECKED( AItem, ItemSetting ) )
	{
		//Update Equiped Socket
		switch ( ItemSetting.ItemType )
		{
			case EItemTypes::EIT_WEAPON:
				ItemSetting.EquipedSocket = DEFAULT_WEAPON_EQEUIPED_SOCKET;
				ItemSetting.HoldSocket = DEFAULT_WEAPON_HOLD_SOCKET;
				break;
			case EItemTypes::EIT_ARMOUR_Head:
				ItemSetting.EquipedSocket = DEFAULT_ARMOUR_HEAD_SOCKET;
				ItemSetting.HoldSocket = NONE_SOCKET;
				break;
			case EItemTypes::EIT_ARMOUR_Chest:
				ItemSetting.EquipedSocket = DEFAULT_ARMOUR_CHEST_SOCKET;
				ItemSetting.HoldSocket = NONE_SOCKET;
				break;
			case EItemTypes::EIT_ARMOUR_Hand:
				ItemSetting.EquipedSocket = DEFAULT_ARMOUR_HAND_SOCKET;
				ItemSetting.HoldSocket = NONE_SOCKET;
				break;
			case EItemTypes::EIT_ARMOUR_Feet:
				ItemSetting.EquipedSocket = DEFAULT_ARMOUR_FEET_SOCKET;
				ItemSetting.HoldSocket = NONE_SOCKET;
				break;
			case EItemTypes::EIT_PROP:
			default:
				ItemSetting.EquipedSocket = NONE_SOCKET;
				ItemSetting.HoldSocket = NONE_SOCKET;
				break;
		}
	}
	Super::PostEditChangeProperty( e );
}
