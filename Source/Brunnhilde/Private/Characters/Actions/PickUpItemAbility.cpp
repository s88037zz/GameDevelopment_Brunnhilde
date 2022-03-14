// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Actions/PickUpItemAbility.h"
#include "Weapon.h"
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
                EquippedWeapon->OnDrop();
            }

            UMeshComponent* WeaponMesh = Weapon->GetMeshComponent();
            if ( WeaponMesh->IsSimulatingPhysics() )
            {
                Weapon = Weapon->OnPickup_Copy();
            }
            else
            {
                Weapon->OnPickup( GetControlCharacter() );
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