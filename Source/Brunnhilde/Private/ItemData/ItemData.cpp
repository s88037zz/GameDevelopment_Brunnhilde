// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemData/ItemData.h"

UItemData::UItemData()
{
    Weight = 1.0f;
    ItemDisplayName = FText::FromString( "Item" );
    UseActionText =  FText::FromString( "Text" );
}

UItemData::UItemData( UItemData* ItemData )
{
    UseActionText         = ItemData->UseActionText;
    PickupMesh            = ItemData->PickupMesh;
    Thumnail              = ItemData->Thumnail;
    ItemDisplayName       = ItemData->ItemDisplayName;
    ItemDiscription       = ItemData->ItemDiscription;
    Weight                = ItemData->Weight;
    OwningInventory       = ItemData->OwningInventory;
}
