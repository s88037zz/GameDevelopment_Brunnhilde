// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Actions/AttackAbility.h"
#include "EnduranceComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BrunnhildeCharacter.h"

bool UAttackAbility::BeginAbility()
{
    UAnimMontage* CurrentMontage = GetControlCharacter()->GetCurrentMontage();
    if( CurrentMontage || !IsState( ECharacterFSM::ECFSM_Fighting ) || AttackCounter >= AttackCombos.Num() )
    {
        return false;
    }

    AttackCounter = 0;
    ABrunnhildeCharacter* Character = GetControlCharacter();

    Character->NextMontageQueue.Push( AttackCombos[ AttackCounter ]->AttackMontage );
    Character->SetRequiredNextMontage( true );
    AttackCounter = ( AttackCounter + 1 ) % AttackCombos.Num();
    return true;
}

void UAttackAbility::Initialize( ABrunnhildeCharacter* Character )
{
    Super::Initialize( Character );
    InitComboMontage();
    AttackCounter = 0;
}

bool UAttackAbility::UpdateAbility()
{
    if ( !IsState( ECharacterFSM::ECFSM_Attacking )
         || !IsInAcceptableActtionRange
         || AttackCounter >= AttackCombos.Num() )
    {
        return false;
    }

    ABrunnhildeCharacter* Character = GetControlCharacter();
    if ( Character->GetEnduranceCmp()->GetCurrentEndurance() < EnduranceCost )
    {
        return false;
    }

    Character->NextMontageQueue.Push( AttackCombos[ AttackCounter ]->AttackMontage );
    //由Notification設定
    //Character->SetRequiredNextMontage( true );

    IsInAcceptableActtionRange = false; //將AnimNotification設定的變數Reset
    AttackCounter = ( AttackCounter + 1 ) % AttackCombos.Num();
    return true;
}

int UAttackAbility::ResetAttackCounter()
{
    AttackCounter = 0;
    return AttackCounter;
}

void UAttackAbility::InitComboMontage()
{
    for ( auto& AttackMontageClass : AttackComboClasses )
    {
        UAttackCombo* Combo = NewObject<UAttackCombo>( this, AttackMontageClass );
        check( IsValid( Combo ) );
        AttackCombos.Add( Combo );
    }
}
/*
void UAttackAbility::HandleAttackInput02()

{
    // Handle Input
    if ( Character->CurrentState == ECharacterFSM::ECFSM_Attacking )
    {
        GetControlMovement()->DisableMovement();


        UGameplayStatics::PlaySoundAtLocation( GetWorld(), CurrentActiveCombo->SoundEffect,
                                               Character->GetTransform().GetLocation() );
        GetWorld()->GetFirstPlayerController()
            ->PlayerCameraManager->PlayCameraShake( CurrentActiveCombo->OnHitShakingType );
       
        Character->SetMovementTimerHandle( Duration, true );
        Character->GetEnduranceCmp()->Reduce( EnduranceCost );

        GetWorld()->GetTimerManager().SetTimer( AttackStatusHandle, [this]()
        {
            ResetAttackCounter();
        }, Duration, false );
    }
    else
    {
        UAnimMontage* CurrentAttackMontage = GetControlActiveMontage();
        if ( CurrentAttackMontage )
        {
            UGameplayStatics::PlaySoundAtLocation( GetWorld(), AttackCombos[AttackCounter]->SoundEffect,
                                                       Character->GetTransform().GetLocation() );
            GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake( CurrentActiveCombo->OnHitShakingType );
            Character->GetEnduranceCmp()->Reduce( EnduranceCost );        
        }
    }
}
*/