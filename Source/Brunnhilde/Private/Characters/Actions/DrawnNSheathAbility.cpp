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

        if ( TimeCounter > Idle2SheathTime )
        {
            Sheath();
            TimeCounter = 0;
        }
    }
   
}

void UDrawnNSheathAbility::BeginAbility()
{
    if ( bWeaponDrawn )
    {
        Sheath();
    }
    else
    {
        Drawn();
    }
}

void UDrawnNSheathAbility::Drawn()
{
    if ( GetControlCharacter()->GetCurrentMontage() ||
         GetControlMovement()->IsFalling() )
    {
        return;
    }


    ABrunnhildeCharacter* Character =  Cast<ABrunnhildeCharacter>( GetControlCharacter() );
    if ( !bWeaponDrawn &&
         Character->Inventory->IsWeaponEquiped() )
    {

        GetControlMovement()->DisableMovement();

        double Duration = SetControlPlayAnimMontage( DrawnWeaponMontage );

        FTimerHandle TimerHandle = GetControlMovementTimeHandle();

        GetWorld()->GetTimerManager().SetTimer( TimerHandle, [this]()
        {
            GetControlMovement()->SetMovementMode( MOVE_Walking );      

        }, Duration, false );

        bWeaponDrawn = true;
    }

}

void UDrawnNSheathAbility::Sheath()
{
    if ( GetControlCharacter()->GetCurrentMontage() ||
         GetControlMovement()->IsFalling() )
    {
        return;
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
    }
}

void UDrawnNSheathAbility::ResetIdle2SheathCounter()
{
    TimeCounter = 0.f;
}
