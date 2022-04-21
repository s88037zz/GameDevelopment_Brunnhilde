// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/State/StateMachine.h"

void UStateMachine::Tick()
{
    switch ( eCurrentState )
    {

        case ECharacterFSM::ECFSM_ReadyToAttack:
            OnReadyToAttackState();
            break;
        case ECharacterFSM::ECFSM_Attacking:
            OnAttackingState();
            break;
        case ECharacterFSM::ECFSM_AcceptedAttackCombo:
            OnAccpetedNextComboState();
            break;
        default:
            return;
    }

}

void UStateMachine::OnIdle()
{

}

void UStateMachine::OnReadyToAttackState()
{
}

void UStateMachine::OnAttackingState()
{
}
void UStateMachine::OnAccpetedNextComboState()
{
}
void UStateMachine::DoAttackAction()
{
    if ( ECharacterFSM::ECFSM_ReadyToAttack == eCurrentState )
    {
        eCurrentState = ECharacterFSM::ECFSM_Attacking;
    }
    else if ( ECharacterFSM::ECFSM_Attacking == eCurrentState )
    {
        eCurrentState = ECharacterFSM::ECFSM_AcceptedAttackCombo;
    }
    return;
}

void UStateMachine::DoDrawnWeapon()
{

}

void UStateMachine::DoSheathWeapon()
{

}