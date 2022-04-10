// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Item.h"
#include "ItemData/ItemData.h"

AItem::AItem()
{
    Weight = 1.0f;
    ItemDisplayName = FText::FromString( "Item" );
    UseActionText =  FText::FromString( "Text" );
}

AItem::AItem( UItemData* ItemData ) : AItem()
{

    this->ItemData = ItemData;
}
