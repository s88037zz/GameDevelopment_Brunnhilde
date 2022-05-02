// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Actions/DeadAbility.h"
#include "Characters/BrunnhildeCharacter.h"
#include "Games/HealthComponent.h"

void UDeadAbility::Initialize( ABrunnhildeCharacter* Character )
{
    SetControlCharacter( Character );
    Character->HealthCmp->OnDied.AddDynamic( this, &UDeadAbility::OnDied );
}

void UDeadAbility::OnDied()
{
    if ( !GetControlCharacter() || !IsValid( DeathMontage ) )
    {
        return;
    }
    GetControlCharacter()->CurrentState = ECharacterFSM::ECFSM_Dead;
    SetControlPlayAnimMontage( DeathMontage );  
}
