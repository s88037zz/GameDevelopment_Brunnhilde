// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Actions/PickUpItemAbility.h"
#include "Item/Weapon.h"
#include "BrunnhildeCharacter.h"


void UPickUpItemAbility::PickUp()
{
    TArray<AActor*> OverlappingActors;
    TSubclassOf<AWeapon> ClassFilter;
    GetControlCharacter()->GetOverlappingActors( OverlappingActors, ClassFilter );
    AWeapon* EquippedWeapon = GetControlCharacter()->GetEquippedWeapon();

    for ( auto& Actor : OverlappingActors )
    {
        // Not the same with current weapon
        if ( Cast< AWeapon >( Actor ) &&
             Actor != EquippedWeapon )
        {
            AWeapon* Weapon = Cast< AWeapon >( Actor );

            if ( EquippedWeapon )
            {
                EquippedWeapon->HandleDrop();
            }

            UMeshComponent* WeaponMesh = Weapon->GetMeshComponent();
            if ( WeaponMesh->IsSimulatingPhysics() )
            {
                Weapon = Weapon->HandlePickupByCopy();
            }
            else
            {
                Weapon->HandlePickup( GetControlCharacter() );
            }

            GetControlCharacter()->SetEquippedWeapon( Weapon );

            if ( !GetControlCharacter()->WeaponInventory.Contains( Weapon ) )
            {
                GetControlCharacter()->WeaponInventory.Add( Weapon );
            }

            break;
        }
    }
}