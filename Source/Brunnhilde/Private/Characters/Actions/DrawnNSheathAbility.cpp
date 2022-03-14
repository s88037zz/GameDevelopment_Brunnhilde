// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Actions/DrawnNSheathAbility.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapons/Weapon.h"
#include "BrunnhildeCharacter.h"
#include "Components/SkeletalMeshComponent.h"

void UDrawnNSheathAbility::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
    if ( false == bWeaponDrawn )
    {
        return;
    }

    if ( nullptr == GetControlCharacter()->GetCurrentActiveAbility() &&
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

void UDrawnNSheathAbility::Drawn()
{
    if ( GetControlCharacter()->GetCurrentMontage() ||
         GetControlMovement()->IsFalling() )
    {
        return;
    }


    if ( !bWeaponDrawn &&
         GetControlCharacter()->GetEquippedWeapon() )
    {
        GetControlMovement()->DisableMovement();

        double Duration = SetControlPlayAnimMontage( DrawnWeaponMontage );

        FTimerHandle TimerHandle = GetControlMovementTimeHandle();
        GetWorld()->GetTimerManager().SetTimer( TimerHandle, [this]()
        {
            GetControlCharacter()->SetReadyToAttack( true );
            GetControlMovement()->SetMovementMode( MOVE_Walking );      
        }, Duration, false );

    }

}

void UDrawnNSheathAbility::Sheath()
{
    if ( GetControlCharacter()->GetCurrentMontage() ||
         GetControlMovement()->IsFalling() )
    {
        return;
    }

    if ( bWeaponDrawn &&
         GetControlCharacter()->GetEquippedWeapon() )
    {
        GetControlCharacter()->SetReadyToAttack( false );
        GetControlMovement()->DisableMovement();
        double Duration = SetControlPlayAnimMontage( SheathWeaponMontage );

        FTimerHandle TimerHandle = GetControlMovementTimeHandle();
        GetWorld()->GetTimerManager().SetTimer( TimerHandle, [this]()
        {
            GetControlMovement()->SetMovementMode( MOVE_Walking );
        }, Duration, false );

    }
}

void UDrawnNSheathAbility::ResetIdle2SheathCounter()
{
    TimeCounter = 0.f;
}
