// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Actions/PickUpItemAbility.h"
#include "Item/Weapon.h"
#include "BrunnhildeCharacter.h"
#include "Games/InventoryComponent.h"


void UPickUpItemAbility::BeginAbility()
{
    PickUp();
}

void UPickUpItemAbility::PickUp()
{
    ABrunnhildeCharacter* Character = GetControlCharacter();

    TArray<AActor*> OverlappingActors;
    TSubclassOf<AWeapon> ClassFilter;
    GetControlCharacter()->GetOverlappingActors( OverlappingActors, ClassFilter );
    for ( auto& Actor : OverlappingActors )
    {
        AItem* Item = Cast< AItem >( Actor );
        if ( IsValid( Item ) )
        {
            UItemData* ItemData = NewObject<UItemData>( Item );
            Character->Inventory->AddItem( ItemData );
        }
        
        GetWorld()->DestroyActor( Actor );
        break;        
    } 
}