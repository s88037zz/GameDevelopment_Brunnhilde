// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Actions/PickUpItemAbility.h"
#include "Item/Weapon.h"
#include "BrunnhildeCharacter.h"
#include "Games/InventoryComponent.h"


bool UPickUpItemAbility::BeginAbility()
{
    PickUp();
    return true;
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
            Character->InventoryCmp->AddItem( Item );
        }
        
        GetWorld()->DestroyActor( Actor );
        break;        
    } 
}