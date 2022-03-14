// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Actions/AttackAbility.h"
#include "EnduranceComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BrunnhildeCharacter.h"


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
    InitMontage();
}

void UAttackAbility::InitMontage()
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
    if ( Character->IsSaveAttack() )
    {
        Character->SetSaveAttack( false );
        GetControlMovement()->DisableMovement();

        AttackCounter = ( AttackCounter + 1 ) % AttackCombos.Num();
        double Duration = SetControlPlayAnimMontage( AttackCombos[AttackCounter]->AttackMontage );
        Character->SetMovementTimerHandle( Duration, true );

    }
    else
    {
        ResetAttackCounter();
        Character->SetAttacking( false );
        Character->SetActiveAbility( nullptr );

    }

}

void UAttackAbility::HandleAttackInput02()
{
    //Check validation
    ABrunnhildeCharacter* Character = GetControlCharacter();
    if ( !IsValid( Character ) )
    {
        return;
    }

    UCharacterMovementComponent* ControlMovement = GetControlMovement();
    if ( !IsValid( ControlMovement ) )
    {
        return;
    }

    // Is Endurance Enough
    if ( Character->GetEnduranceCmp()->GetCurrentEndurance() < EnduranceCost )
    {
        return;
    }

    // Handle Input
    if ( Character->IsAttacking() == false )
    {
        Character->SetAttacking( true );
        Character->SetActiveAbility( this );
        GetControlMovement()->DisableMovement();

        AttackCounter = ResetAttackCounter();
        if ( IsValid( AttackCombos[AttackCounter] ) )
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
            GetControlCharacter()->SetAttacking( false );
            GetControlCharacter()->SetActiveAbility( nullptr );
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
                    GetControlCharacter()->SetAttacking( false );
                    GetControlCharacter()->SetActiveAbility( nullptr );
                }, Duration, false );
            }
        }
    }
}

void UAttackAbility::BeginPlay()
{
    Super::BeginPlay();
    InitMontage();
}
