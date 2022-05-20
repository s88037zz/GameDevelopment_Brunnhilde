// Fill out your copyright notice in the Description page of Project Settings.


#include "Games/InventoryComponent.h"
#include "Item/Armour.h"
#include "Item/Weapon.h"
#include "BrunnhildeCharacter.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent( ABrunnhildeCharacter* Owner )
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
		if ( nullptr == Item )
		{
			return;
		}
		// Hides visible components
		Item->SetActorHiddenInGame( true );
		// Disables collision components
		Item->SetActorEnableCollision( false );
		// Stops the Actor from ticking
		Item->SetActorTickEnabled( false );

		Items.Add( Item );
	}
}


bool UInventoryComponent::AddItem( AItem* Item )
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

bool UInventoryComponent::RemoveItem( AItem* Item )
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


bool UInventoryComponent::UseItem( AItem* Item )
{
	if ( nullptr == Item || Item->GetItemSetting().ItemType != EItemTypes::EIT_PROP )
	{
		return false;
	}

	if ( GetOwner() )
	{
		return false;
	}

	ABrunnhildeCharacter* Character = Cast<ABrunnhildeCharacter>( GetOwner() );
	if ( IsValid( Character ) )
	{
		Item->OnUse( Character );
	}
	RemoveItem( Item );
	OnInventoryUpdated.Broadcast();
	return true;
}


bool UInventoryComponent::EquipItem( AItem* Item )
{
	if ( nullptr == Item )
	{
		return false;
	}

	if ( nullptr == GetOwner() )
	{
		return false;
	}
	ABrunnhildeCharacter* Character = Cast< ABrunnhildeCharacter >( GetOwner() );
	AItem* NewEquipment = Cast< AItem >( Item );

	if ( !IsValid( NewEquipment ) || !IsValid( Character ) )
	{
		return false;
	}

	// Unequip Current Euqipment with same type
	UnEquipItem( NewEquipment->GetItemSetting().ItemType );
	
	//Excute Equip Weapon
	NewEquipment->OnEquiped( Character );
			
	//Update Inventory Data
	EquipedEquipments.Add( NewEquipment->GetItemSetting().ItemType, Item );
	RemoveItem( Item );
	OnEquipmentUpdated.Broadcast();
	return true;
}

bool UInventoryComponent::UnEquipItem( EItemTypes EquipementType )
{

	ABrunnhildeCharacter* Character = Cast< ABrunnhildeCharacter >( GetOwner() );
	if ( nullptr == Character )
	{
		return false;
	}

	if ( EquipedEquipments.Contains( EquipementType ) )
	{
		AItem* Item = EquipedEquipments[ EquipementType ];
		Item->OnUnEquiped( Character );

		//Update Inventory Data
		EquipedEquipments.Emplace( EquipementType, nullptr );
		if ( IsValid( Item ) )
		{
			AddItem( Item );
		}
		OnEquipmentUpdated.Broadcast();
	}
	return true;
}

bool UInventoryComponent::IsWeaponEquiped()
{
	if ( nullptr == GetOwner() || nullptr == Cast<ABrunnhildeCharacter>( GetOwner() ) )
	{
		return false;
	}
	return EquipedEquipments.Find( EItemTypes::EIT_WEAPON ) != nullptr;
}

AWeapon* UInventoryComponent::GetEquipedWeapon( EItemTypes eWeaponType )
{
	if ( IsWeaponEquiped() )
	{
		return Cast< AWeapon >( EquipedEquipments[ eWeaponType ] );
	}
	return nullptr;
}

AItem* UInventoryComponent::GetEquipmentByType( EItemTypes eType )
{
	if ( EquipedEquipments.Contains( eType ) )
	{
		return EquipedEquipments[ eType ];
	}
	return nullptr;
}