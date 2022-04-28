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
void UStateMachine::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
    check( PlayerInputComponent );
    PlayerInputComponent->BindAction( "NormalAttack",   IE_Pressed,   this, &UStateMachine::AttackAction );
    PlayerInputComponent->BindAction( "Pickup",         IE_Pressed,   this, &UStateMachine::PickItemAction );
    PlayerInputComponent->BindAction( "Sprint",         IE_Pressed,   this, &UStateMachine::SprintAction );
    PlayerInputComponent->BindAction( "Sprint",         IE_Released,  this, &UStateMachine::SprintAction );
    PlayerInputComponent->BindAction( "LockEnemy",      IE_Released,  this, &UStateMachine::LockEnemyAction );
}

void UStateMachine::OnIdleState()
{
}

void UStateMachine::OnFightingState()
{
}

void UStateMachine::OnAttackingState()
{
    UAnimMontage* CurrnetMontage =  Character->GetCurrentMontage();
    if ( CurrnetMontage && Character->IsRequiredNextMontage() )
    {
        if( Character->NextMontageQueue.Num() == 0 )
        {
            return;
        }
        UAnimMontage* NextMontage = Character->NextMontageQueue.Pop( true );
        if( NextMontage )
        {
            Character->PlayAnimMontage( NextMontage );
        }
    }
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
        if ( AttackAbility->BeginAbility() )        ChangeStateTo( ECharacterFSM::ECFSM_AcceptedAttackCombo );
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

    if ( AttackAbility )         AttackAbility->SetControlCharacter( Character );
    if ( FlinchAbility )         FlinchAbility->SetControlCharacter( Character );
    if ( DrawnSheathAbility )    DrawnSheathAbility->SetControlCharacter( Character );
    if ( PickUpItemAbility )     PickUpItemAbility->SetControlCharacter( Character );
    if ( PickUpItemAbility )     SprintAbility->SetControlCharacter( Character );
    if ( SprintAbility )         SprintAbility->SetControlCharacter( Character );
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