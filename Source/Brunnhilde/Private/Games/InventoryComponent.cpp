// Fill out your copyright notice in the Description page of Project Settings.


#include "Games/InventoryComponent.h"
#include "Games/BrunnhildeDef.h"
#include "Armours/Armour.h"
#include "ItemData/ArmourData.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{	
	for ( auto& Item : DefaultItems )
	{
		Items.Add( Item );
	}
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// ...
}

bool UInventoryComponent::AddItemData( UItemData* Item )
{
	if ( Items.Num() > Capacity || !IsValid( Item ) )
	{
		return false;
	}

	Item->OwningInventory = this;
	Items.Add( Item );

	//Update UI
	OnInventoryUpdated.Broadcast();
	
	return true;
}

bool UInventoryComponent::RemoveItemData( UItemData* Item )
{
	if ( Item )
	{
		Item->OwningInventory = nullptr;
		Items.RemoveSingle( Item );
		OnInventoryUpdated.Broadcast();

		return true;
	}
	
	return false;
}

bool UInventoryComponent::EquipItemData( UItemData* Item )
{
	UArmourData* ArmourData = Cast< UArmourData >( Item );

	if ( IsValid( ArmourData ) )
	{
		uint8 AmorurTypeInt = StaticCast< uint8 >( ArmourData->AmorurType );
		EquipedItems.Add( AmorurTypeInt, Item );
		OnEquipmentUpdated.Broadcast();

		return true;
	}
	
	return false;
}

bool UInventoryComponent::UnEquipItemData( EArmourTypes ArmourType )
{
	uint8 AmorurTypeInt = StaticCast< uint8 >( ArmourType );

	if ( EquipedItems.Contains( AmorurTypeInt ) )
	{
		EquipedItems.Emplace( AmorurTypeInt, nullptr );
		OnEquipmentUpdated.Broadcast();
	}

	return false;
}