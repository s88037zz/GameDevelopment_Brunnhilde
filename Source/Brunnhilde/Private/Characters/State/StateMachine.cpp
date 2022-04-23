// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/State/StateMachine.h"
#include "Characters/BrunnhildeCharacter.h"
#include "Characters/Actions/NormalAttackAbility.h"
#include "Characters/Actions/FlinchAbility2.h"
#include "Characters/Actions/DrawnNSheathAbility.h"
#include "Characters/Actions/PickUpItemAbility.h"
#include "Characters/Actions/LockEnemyAbility.h"
#include "Characters/Actions/SprintAbility2.h"
#include "Components/InputComponent.h"

UStateMachine::UStateMachine( ABrunnhildeCharacter* Character )
{
    SetControlCharacter( Character );
}

void UStateMachine::Tick()
{
    switch ( m_Character->CurrentState )
    {
        case ECharacterFSM::ECFSM_Idle:
            OnIdleState();
            break;
        case ECharacterFSM::ECFSM_Fighting:
            OnFightingState();
            break;
        case ECharacterFSM::ECFSM_Attacking:
            OnAttackingState();
            break;
        case ECharacterFSM::ECFSM_AcceptedAttackCombo:
            OnAccpetedNextComboState();
            break;
        case ECharacterFSM::ECFSM_Flinch:
            OnFlinchState();
            break;
        case ECharacterFSM::ECFSM_KnockDown:
            OnKnockDownState();
            break;
        default:
            return;
    }

}

void UStateMachine::SetControlCharacter( ABrunnhildeCharacter* Character )
{
    m_Character =  Character;
    if ( AttackAbility )         AttackAbility->SetControlCharacter( Character );
    if ( FlinchAbility )         FlinchAbility->SetControlCharacter( Character );
    if ( DrawnSheathAbility )    DrawnSheathAbility->SetControlCharacter( Character );
    if ( PickUpItemAbility )     PickUpItemAbility->SetControlCharacter( Character );
    if ( PickUpItemAbility )     SprintAbility->SetControlCharacter( Character );
    if ( SprintAbility )         SprintAbility->SetControlCharacter( Character );
}

void UStateMachine::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
    check( PlayerInputComponent );
    PlayerInputComponent->BindAction( "Attack",    IE_Pressed,   this, &UStateMachine::AttackAction );
    PlayerInputComponent->BindAction( "Pickup",    IE_Pressed,   this, &UStateMachine::PickItemAction );
    PlayerInputComponent->BindAction( "Sprint",    IE_Pressed,   this, &UStateMachine::SprintAction );
    PlayerInputComponent->BindAction( "Sprint",    IE_Released,  this, &UStateMachine::SprintAction );
    PlayerInputComponent->BindAction( "LockEnemy", IE_Released,  this, &UStateMachine::LockEnemyAction );
}

void UStateMachine::HandleDrawnNotification()
{
    //Check validate
    if ( !IsValid( m_Character ) )
    {
        return;
    }

    //AttackAbility->HandleNotification_AttackComboNext();
}

void UStateMachine::HandleSheathNotification()
{
}

void UStateMachine::OnIdleState()
{
    m_NextMontage = nullptr;
    ChangeStateTo( ECharacterFSM::ECFSM_Idle );
}

void UStateMachine::OnFightingState()
{
}

void UStateMachine::OnAttackingState()
{
}
void UStateMachine::OnAccpetedNextComboState()
{
}
void UStateMachine::OnFlinchState()
{
}
void UStateMachine::OnKnockDownState()
{
}

void UStateMachine::AttackAction()
{
    if ( ECharacterFSM::ECFSM_Idle == m_Character->CurrentState )
    {
        DrawnSheathAbility->BeginAbility();
    }
    else if ( ECharacterFSM::ECFSM_Fighting == m_Character->CurrentState )
    {
        AttackAbility->BeginAbility();
        ChangeStateTo( ECharacterFSM::ECFSM_Attacking );
    }
    else if ( ECharacterFSM::ECFSM_Attacking == m_Character->CurrentState )
    {
        AttackAbility->BeginAbility();
        ChangeStateTo( ECharacterFSM::ECFSM_AcceptedAttackCombo );
    }
    return;
}

void UStateMachine::DrawnWeaponAction()
{
    if ( nullptr == DrawnSheathAbility )
    {
        return;
    }

    if ( ECharacterFSM::ECFSM_Idle == m_Character->CurrentState )
    {
        DrawnSheathAbility->BeginAbility();
        ChangeStateTo( ECharacterFSM::ECFSM_Fighting );
    }
    return;
}

void UStateMachine::SheathWeaponAction()
{
    if ( nullptr == DrawnSheathAbility )
    {
        return;
    }

    if ( ECharacterFSM::ECFSM_Fighting != m_Character->CurrentState )
    {
        return;
    }

    DrawnSheathAbility->BeginAbility();
    ChangeStateTo( ECharacterFSM::ECFSM_Idle );
}

void UStateMachine::BeDamagedAction()
{   
    if ( nullptr == FlinchAbility )
    {
        return;
    }

    if ( ECharacterFSM::ECFSM_Flinch ==  m_Character->CurrentState )
    {
        FlinchAbility->BeginAbility();
        ChangeStateTo( ECharacterFSM::ECFSM_KnockDown );
    }
    else
    {
        FlinchAbility->BeginAbility();
        ChangeStateTo( ECharacterFSM::ECFSM_Flinch );
    }
}

void UStateMachine::ChangeStateTo( ECharacterFSM State )
{
    m_Character->CurrentState = State;
}

bool UStateMachine::IsState( ECharacterFSM State )
{
    if ( !m_Character )
    {
        return false;
    }
    return m_Character->CurrentState == State;
}

void UStateMachine::PickItemAction()
{
    if ( ECharacterFSM::ECFSM_Idle == m_Character->CurrentState ||
         ECharacterFSM::ECFSM_Fighting == m_Character->CurrentState )
    {
        PickUpItemAbility->BeginAbility();
    }
}

void UStateMachine::SprintAction()
{
    SprintAbility->BeginAbility();
}

void UStateMachine::LockEnemyAction()
{
}
