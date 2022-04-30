// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Actions/AttackAbility.h"
#include "EnduranceComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BrunnhildeCharacter.h"

bool UAttackAbility::BeginAbility()
{
    AttackCounter = 0;

    ABrunnhildeCharacter* Character = GetControlCharacter();
    if ( IsState( ECharacterFSM::ECFSM_Fighting ) && AttackCounter < AttackCombos.Num() )
    {
        Character->NextMontageQueue.Push( AttackCombos[ AttackCounter ]->AttackMontage );
        Character->SetRequiredNextMontage( true );
        AttackCounter++;
    } 
    AttackCounter = AttackCounter % AttackCombos.Num();
    return true;
}

bool UAttackAbility::UpdateAbility()
{
    ABrunnhildeCharacter* Character = GetControlCharacter();
    if ( IsState( ECharacterFSM::ECFSM_Attacking ) )
    {
        if ( IsAcceptedActtion() && AttackCounter < AttackCombos.Num() )
        {
            Character->NextMontageQueue.Push( AttackCombos[ AttackCounter ]->AttackMontage );
            Character->SetRequiredNextMontage( true );
            AttackCounter++;
        }
    }
    return true;
}

int UAttackAbility::ResetAttackCounter()
{
    AttackCounter = 0;
    return AttackCounter;
}

int UAttackAbility::GetNextComboIdx()
{
    if( CurrentActiveCombo )
    {
        int Idx = AttackCombos.Find( CurrentActiveCombo );
        return ( Idx + 1 ) % AttackCombos.Num();
    }
    return ResetAttackCounter();
}


void UAttackAbility::Initialize( ABrunnhildeCharacter* Character )
{
    Super::Initialize( Character );
    InitComboMontage();
    AttackCounter = 0;
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


void UAttackAbility::HandleNotification_AttackComboNext()
{
    //Check validate
    ABrunnhildeCharacter* Character = GetControlCharacter();
    if ( !IsValid( Character ) )
    {
        return;
    }

    // Handle Notification
    if ( IsState( ECharacterFSM::ECFSM_AcceptedAttackCombo ) )
    {
        GetControlMovement()->DisableMovement();

        AttackCounter = ( AttackCounter + 1 ) % AttackCombos.Num();
        double Duration = SetControlPlayAnimMontage( AttackCombos[AttackCounter]->AttackMontage );
        Character->SetMovementTimerHandle( Duration, true );

        ChangeStateTo( ECharacterFSM::ECFSM_Attacking );
    }
    else
    {
        ResetAttackCounter();
        ChangeStateTo( ECharacterFSM::ECFSM_Idle );
    }

}

void UAttackAbility::HandleAttackInput02()

{
    //Check validation
    if ( !IsValid( GetControlCharacter() ) )
    {
        return;
    }

    if ( !IsValid( GetControlMovement() ) )
    {
        return;
    }

    // Is Endurance Enough

    ABrunnhildeCharacter* Character = GetControlCharacter();
    if ( Character->GetEnduranceCmp()->GetCurrentEndurance() < EnduranceCost )
    {
        return;
    }

    // Handle Input
    if ( Character->CurrentState == ECharacterFSM::ECFSM_Attacking )
    {
        GetControlMovement()->DisableMovement();

        AttackCounter = ResetAttackCounter();
        if ( AttackCombos.IsValidIndex( AttackCounter ) 
             && IsValid( AttackCombos[ AttackCounter ] ) )
        {
            CurrentActiveCombo = AttackCombos[AttackCounter];
        }
        else
        {
            return;
        }

        double Duration = SetControlPlayAnimMontage( CurrentActiveCombo->AttackMontage );

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

            double Length = CurrentAttackMontage->GetSectionLength( 0 );
            double LeftTime = Character->GetMontageLeftTime( CurrentAttackMontage,
                                                             GetControlMesh() );


            float Threshold = CurrentActiveCombo ? CurrentActiveCombo->LeftTimeToCombo : 0.5;

            if ( LeftTime / Length < Threshold )
            {

                AttackCounter = GetNextComboIdx();
                CurrentActiveCombo = AttackCombos[AttackCounter];


                double Duration = SetControlPlayAnimMontage( AttackCombos[AttackCounter]->AttackMontage );
                UGameplayStatics::PlaySoundAtLocation( GetWorld(), AttackCombos[AttackCounter]->SoundEffect,
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
        }
    }
}

bool UAttackAbility::IsAcceptedActtion()
{
    //Check validation
    if ( !IsValid( GetControlCharacter() ) )
    {
        return false;
    }

    if ( !IsValid( GetControlMovement() ) )
    {
        return false;
    }

    UAnimMontage* CurrentAttackMontage = GetControlActiveMontage();
    if ( CurrentAttackMontage )
    {

        double Length = CurrentAttackMontage->GetSectionLength( 0 );
        double LeftTime = GetControlCharacter()->GetMontageLeftTime( CurrentAttackMontage,
                                                 GetControlMesh() );


        float Threshold = CurrentActiveCombo ? CurrentActiveCombo->LeftTimeToCombo : 0.5;

        if ( LeftTime / Length < Threshold )
        {
            return true;
        }
    }
    return false;
}
