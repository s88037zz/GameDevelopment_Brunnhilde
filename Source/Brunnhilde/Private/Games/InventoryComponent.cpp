// Fill out your copyright notice in the Description page of Project Settings.


#include "Games/InventoryComponent.h"
#include "Games/BrunnhildeDef.h"
#include "Armours/Armour.h"
#include "Item.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Init
	Capacity = 20;
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{	

	Super::BeginPlay();

	for ( auto& Item : DefaultItems )
	{
		Items.Add( Item );
	}

	
	for ( EArmourTypes ArmourType :	TEnumRange< EArmourTypes >())
	{
		uint8 AmorurTypeInt = StaticCast< uint8 >( ArmourType );
		EquipedItems.Add( AmorurTypeInt, nullptr);
	}
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// ...
}

bool UInventoryComponent::AddItem( UItem* Item )
{
	if ( Items.Num() > Capacity || !IsValid( Item ) )
	{
		return false;
	}

	Item->OwningInventory = this;
	Item->World = GetWorld();
	Items.Add( Item );

	//Update UI
	OnInventoryUpdated.Broadcast();

	return true;
}

bool UInventoryComponent::RemoveItem( UItem* Item )
{
	if ( Item )
	{
		Item->OwningInventory = nullptr;
		Item->World = nullptr;
		Items.RemoveSingle( Item );
		OnInventoryUpdated.Broadcast();

		return true;
	}
	return false;
}

bool UInventoryComponent::EquipItem( UItem* Item )
{
	if ( CastChecked< UArmour, UItem>( Item ) )
	{
		UArmour* Armour = Cast< UArmour >( Item );

		uint8 AmorurTypeInt = StaticCast< uint8 >( Armour->AmorurType );
		EquipedItems.Add( AmorurTypeInt, Item );
	}
	return false;
}

bool UInventoryComponent::UnEquipItem( EArmourTypes ArmourType )
{
	uint8 AmorurTypeInt = StaticCast< uint8 >( ArmourType );

	if ( EquipedItems.Contains( AmorurTypeInt ) )
	{
		EquipedItems.Emplace( AmorurTypeInt, nullptr );
	}
	return false;
}
