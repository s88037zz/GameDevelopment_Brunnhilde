// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/State/StateMachine.h"
#include "Characters/BrunnhildeCharacter.h"
#include "Characters/Actions/NormalAttackAbility.h"
#include "Characters/Actions/FlinchAbility2.h"
#include "Characters/Actions/DrawnNSheathAbility.h"
#include "Characters/Actions/PickUpItemAbility.h"
#include "Characters/Actions/LockEnemyAbility.h"
#include "Characters/Actions/SprintAbility2.h"
#include "ItemData/ItemData.h"
#include "Components/InputComponent.h"



void UStateMachine::Process()
{
    switch ( Character->CurrentState )
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

void UStateMachine::Initialize( ABrunnhildeCharacter* ControlCharacter )
{
    SetControlCharacter( ControlCharacter );
    SetupAbilities();
}

void UStateMachine::OnIdleState()
{
}

void UStateMachine::OnFightingState()
{
    if ( Character->NextMontageQueue.Num() != 0 && Character->IsRequiredNextMontage() )
    {
        UAnimMontage* NextMontage = Character->NextMontageQueue.Pop(true);
        Character->PlayAnimMontage( NextMontage );
    }

    UAnimMontage* CurMontage = Character->GetCurrentMontage();
    if ( !CurMontage )
    {
        ECharacterFSM State = DrawnSheathAbility->bWeaponDrawn ? ECharacterFSM::ECFSM_Fighting : ECharacterFSM::ECFSM_Idle;
        Character->CurrentState = State;
    }
}

void UStateMachine::OnAttackingState()
{
    if ( Character->IsRequiredNextMontage() && Character->NextMontageQueue.Num() != 0 )
    {
        UAnimMontage* NextMontage = Character->NextMontageQueue.Pop( true );
        Character->PlayAnimMontage( NextMontage );
    }

    if ( !Character->IsValidLowLevel() )
    {
        return;
    }
    UAnimMontage* CurrMontage = Character->GetCurrentMontage();
    if ( !CurrMontage )
    {
        ECharacterFSM State = DrawnSheathAbility->bWeaponDrawn ? ECharacterFSM::ECFSM_Fighting : ECharacterFSM::ECFSM_Idle;
        Character->CurrentState = State;
    }
}

void UStateMachine::OnAccpetedNextComboState()
{
    UAnimMontage* CurrnetMontage =  Character->GetCurrentMontage();
    if ( !IsState( ECharacterFSM::ECFSM_Flinch ) && Character->IsRequiredNextMontage() )
    {
        ChangeStateTo( ECharacterFSM::ECFSM_Attacking );
    }
}
void UStateMachine::OnFlinchState()
{
    AttackAbility->ResetAttackCounter();
    Character->NextMontageQueue.Empty();

    UAnimMontage* Montage = Character->GetCurrentMontage();
    if ( !Montage )
    {
        ECharacterFSM State = DrawnSheathAbility->bWeaponDrawn ? ECharacterFSM::ECFSM_Fighting : ECharacterFSM::ECFSM_Idle;
        Character->CurrentState = State;
    }
}
void UStateMachine::OnKnockDownState()
{
}

void UStateMachine::AttackAction()
{
    if ( ECharacterFSM::ECFSM_Idle == Character->CurrentState )
    {
        if( DrawnSheathAbility->BeginAbility() )    ChangeStateTo( ECharacterFSM::ECFSM_Fighting );
    }
    else if ( ECharacterFSM::ECFSM_Fighting == Character->CurrentState )
    {
        if ( AttackAbility->BeginAbility() )        ChangeStateTo( ECharacterFSM::ECFSM_Attacking );
    }
    else if ( ECharacterFSM::ECFSM_Attacking == Character->CurrentState )
    {
        if ( AttackAbility->UpdateAbility() )       ChangeStateTo( ECharacterFSM::ECFSM_AcceptedAttackCombo );
    }
    return;
}

void UStateMachine::DrawnWeaponAction()
{
    if ( nullptr == DrawnSheathAbility )
    {
        return;
    }

    if ( ECharacterFSM::ECFSM_Idle == Character->CurrentState )
    {
        if ( DrawnSheathAbility->BeginAbility() )
        {
            ChangeStateTo( ECharacterFSM::ECFSM_Fighting );
        }
    }
    return;
}

void UStateMachine::SheathWeaponAction()
{
    if ( nullptr == DrawnSheathAbility )
    {
        return;
    }

    if ( ECharacterFSM::ECFSM_Fighting == Character->CurrentState )
    {
        if ( DrawnSheathAbility->BeginAbility() )
        {
            ChangeStateTo( ECharacterFSM::ECFSM_Fighting );
        }
    }
}

void UStateMachine::BeDamagedAction()
{   
    if ( nullptr == FlinchAbility )
    {
        return;
    }

    if ( ECharacterFSM::ECFSM_Flinch ==  Character->CurrentState )
    {
        if ( FlinchAbility->BeginAbility() )
        {
            ChangeStateTo( ECharacterFSM::ECFSM_KnockDown );
        }
    }
    else
    {
        if ( FlinchAbility->BeginAbility() )
        {
            ChangeStateTo( ECharacterFSM::ECFSM_Flinch );
        }
    }
}


void UStateMachine::PickItemAction()
{
    if ( ECharacterFSM::ECFSM_Idle == Character->CurrentState ||
         ECharacterFSM::ECFSM_Fighting == Character->CurrentState )
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

void UStateMachine::DrawnWeaponNotifcation()
{
    if ( !IsValid( DrawnSheathAbility ) )
    {
        return;
    }

    UItemData* WeaponData = Character->GetEquipedWeapon();
    if ( WeaponData )
    {
        WeaponData->OnDrawn( Character );
        DrawnSheathAbility->bWeaponDrawn = true;
    }
}

void UStateMachine::SheathWeaponNotifcation()
{
    if ( !IsValid( DrawnSheathAbility ) )
    {
        return;
    }

    UItemData* WeaponData = Character->GetEquipedWeapon();
    if ( WeaponData )
    {
        WeaponData->OnSeath( Character );
        DrawnSheathAbility->bWeaponDrawn = false;
    }
}

void UStateMachine::SetControlCharacter( ABrunnhildeCharacter* ControlCharacter )
{
    this->Character = ControlCharacter;
}

void UStateMachine::SetupAbilities()
{
    if ( DrawnSheathClass )  DrawnSheathAbility = NewObject< UDrawnNSheathAbility >( this, DrawnSheathClass );
    if ( AttackClass ) AttackAbility      = NewObject< UAttackAbility >( this, AttackClass );
    if ( FlinchClass ) FlinchAbility      = NewObject< UFlinchAbility2 >( this, FlinchClass );
    if ( PickUpItemClass ) PickUpItemAbility  = NewObject< UPickUpItemAbility >( this, PickUpItemClass );
    if ( LockEnemyClass ) LockEnemyAbility   = NewObject< ULockEnemyAbility >( this, LockEnemyClass );
    if ( SprintClass ) SprintAbility      = NewObject< USprintAbility2 >( this, SprintClass );

    if ( AttackAbility )         AttackAbility->Initialize( Character );  
    if ( FlinchAbility )         FlinchAbility->Initialize( Character );
    if ( DrawnSheathAbility )    DrawnSheathAbility->Initialize( Character );
    if ( PickUpItemAbility )     PickUpItemAbility->Initialize( Character );
    if ( PickUpItemAbility )     SprintAbility->Initialize( Character );
    if ( SprintAbility )         SprintAbility->Initialize( Character );
}

bool UStateMachine::IsState( ECharacterFSM State )
{
    if ( !Character )
    {
        return false;
    }
    return Character->CurrentState == State;
}

void UStateMachine::ChangeStateTo( ECharacterFSM State )
{
     Character->CurrentState = State;
}
