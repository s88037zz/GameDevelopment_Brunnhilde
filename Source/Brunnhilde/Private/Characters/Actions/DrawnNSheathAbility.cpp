// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Actions/DrawnNSheathAbility.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Item/Weapon.h"
#include "Characters/BrunnhildeCharacter.h"
#include "Games/InventoryComponent.h"
#include "Components/SkeletalMeshComponent.h"

void UDrawnNSheathAbility::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
    if ( false == bWeaponDrawn )
    {
        return;
    }
    if ( ECharacterFSM::ECFSM_Idle == GetControlCharacter()->CurrentState &&
        GetControlCharacter()->GetLastMovementInputVector() == FVector::ZeroVector )
    {
        TimeCounter += DeltaTime;

        if ( TimeCounter > Idle2SheathTime && bWeaponDrawn )
        {
            Sheath();
            TimeCounter = 0;
        }
    }
   
}

bool UDrawnNSheathAbility::BeginAbility()
{
    if ( !bWeaponDrawn )
    {
        return Drawn();
    }   
    return true;
}

bool UDrawnNSheathAbility::Drawn()
{
    if ( GetControlCharacter()->GetCurrentMontage() ||
         GetControlMovement()->IsFalling() )
    {
        return false;
    }


    ABrunnhildeCharacter* Character =  Cast<ABrunnhildeCharacter>( GetControlCharacter() );
    if ( !bWeaponDrawn )
    {
        if ( !Character->Inventory->IsWeaponEquiped() )
        {
            return false;
        }

        GetControlMovement()->DisableMovement();

        double Duration = SetControlPlayAnimMontage( DrawnWeaponMontage );

        FTimerHandle TimerHandle = GetControlMovementTimeHandle();

        GetWorld()->GetTimerManager().SetTimer( TimerHandle, [this]()
        {
            GetControlMovement()->SetMovementMode( MOVE_Walking );      

        }, Duration, false );
        bWeaponDrawn = true;
    }
    return true;
}

bool UDrawnNSheathAbility::Sheath()
{
    if ( GetControlCharacter()->GetCurrentMontage() ||
         GetControlMovement()->IsFalling() )
    {
        return false;
    }

    ABrunnhildeCharacter* Character =  Cast<ABrunnhildeCharacter>( GetControlCharacter() );
    if ( bWeaponDrawn &&
         Character->Inventory->IsWeaponEquiped() )
    {
        GetControlMovement()->DisableMovement();
        double Duration = SetControlPlayAnimMontage( SheathWeaponMontage );

        FTimerHandle TimerHandle = GetControlMovementTimeHandle();
        GetWorld()->GetTimerManager().SetTimer( TimerHandle, [this]()
        {
            GetControlMovement()->SetMovementMode( MOVE_Walking );
        }, Duration, false );

        bWeaponDrawn = false;
        return true;
    }
    return false;
}

void UDrawnNSheathAbility::ResetIdle2SheathCounter()
{
    TimeCounter = 0.f;
}
