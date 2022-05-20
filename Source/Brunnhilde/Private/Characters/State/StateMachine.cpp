// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/State/StateMachine.h"
#include "Characters/BrunnhildeCharacter.h"
#include "Characters/Actions/NormalAttackAbility.h"
#include "Characters/Actions/FlinchAbility2.h"
#include "Characters/Actions/DrawnNSheathAbility.h"
#include "Characters/Actions/PickUpItemAbility.h"
#include "Characters/Actions/LockEnemyAbility.h"
#include "Characters/Actions/SprintAbility2.h"
#include "Characters/Actions/DeadAbility.h"
#include "Characters/Actions/DropingTreasureAbility.h"
#include "Games/EnduranceComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Item/Weapon.h"
#include "Components/InputComponent.h"

UStateMachine::UStateMachine()
{
    PrimaryComponentTick.bCanEverTick = true;
    bAutoActivate = true;
}

void UStateMachine::UpdateState()
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
        case ECharacterFSM::ECFSM_Dead:
            OnDeadState();
        case ECharacterFSM::ECFSM_Pickup:
            OnPickupItemState();
        default:
            return;
    }

}

void UStateMachine::BeginPlay()
{
    Super::BeginPlay();
}

void UStateMachine::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
    Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
    UpdateState();
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
        //Anim
        UAnimMontage* NextMontage = Character->NextMontageQueue.Pop( true );
        Character->PlayAnimMontage( NextMontage );

        //Effect
        USoundBase* HitSound = AttackAbility->GetCurrentCombo()->SoundEffect;
        if( IsValid( HitSound ) )
        {
            UGameplayStatics::PlaySoundAtLocation( GetWorld(), HitSound,
                                                   Character->GetTransform().GetLocation() );
        }
        
        TSubclassOf < UMatineeCameraShake > CameraShake =  AttackAbility->GetCurrentCombo()->OnHitShakingType;
        if ( IsValid( HitSound ) )
        {
            GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake( CameraShake );
        }

        //Cost
        Character->GetEnduranceCmp()->Reduce( AttackAbility->EnduranceCost );

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
void UStateMachine::OnDeadState()
{
    if ( !IsValid( DeadAbility ) )
    {
        return;
    }

    UAnimMontage* CurMontage = Character->GetCurrentMontage();
    if ( !CurMontage )
    {
        return;
    }
    
    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer( TimerHandle, [&]()
    {
        AActor* Actor = Cast< AActor >( GetControlCharacter() );
        if ( nullptr == Actor )
        {
            return;
        }
        GetWorld()->DestroyActor( Actor );
    }, DeadAbility->TimeToDisappear, false ); 
    
}
void UStateMachine::OnPickupItemState()
{
    UAnimMontage* CurrMontage = Character->GetCurrentMontage();
    if ( !CurrMontage )
    {
        ECharacterFSM State = DrawnSheathAbility->bWeaponDrawn ? ECharacterFSM::ECFSM_Fighting : ECharacterFSM::ECFSM_Idle;
        Character->CurrentState = State;
    }
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

void UStateMachine::PickupItemAction()
{
    if ( IsValid( PickUpItemAbility ) && IsState( ECharacterFSM::ECFSM_Idle ) && IsState( ECharacterFSM::ECFSM_Fighting ) )
    {
        PickUpItemAbility->BeginAbility();
    }
}

void UStateMachine::DrawnWeaponNotifcation()
{
    if ( !IsValid( DrawnSheathAbility ) )
    {
        return;
    }

    AWeapon* Weapon = Character->GetEquipedWeapon();
    if ( Weapon )
    {
        Weapon->OnDrawn( Character );
        DrawnSheathAbility->bWeaponDrawn = true;
    }
}

void UStateMachine::SheathWeaponNotifcation()
{
    if ( !IsValid( DrawnSheathAbility ) )
    {
        return;
    }

    AWeapon* WeaponData = Character->GetEquipedWeapon();
    if ( WeaponData )
    {
        WeaponData->OnSheath( Character );
        DrawnSheathAbility->bWeaponDrawn = false;
    }
}

void UStateMachine::SetControlCharacter( ABrunnhildeCharacter* ControlCharacter )
{
    this->Character = ControlCharacter;
}

void UStateMachine::SetupAbilities()
{
    if ( DrawnSheathClass )  DrawnSheathAbility        = NewObject< UDrawnNSheathAbility >( this, DrawnSheathClass );
    if ( AttackClass )       AttackAbility             = NewObject< UAttackAbility >( this, AttackClass );
    if ( FlinchClass )       FlinchAbility             = NewObject< UFlinchAbility2 >( this, FlinchClass );
    if ( PickUpItemClass )   PickUpItemAbility         = NewObject< UPickUpItemAbility >( this, PickUpItemClass );
    if ( LockEnemyClass )    LockEnemyAbility          = NewObject< ULockEnemyAbility >( this, LockEnemyClass );
    if ( SprintClass )       SprintAbility             = NewObject< USprintAbility2 >( this, SprintClass );
    if ( DeadClass )         DeadAbility               = NewObject< UDeadAbility >( this, DeadClass );
    if ( DropingTreasureClass ) DropingTreasureAbility = NewObject< UDropingTreasureAbility >( this, DropingTreasureClass );

    if ( AttackAbility )         AttackAbility->Initialize( Character );  
    if ( FlinchAbility )         FlinchAbility->Initialize( Character );
    if ( DrawnSheathAbility )    DrawnSheathAbility->Initialize( Character );
    if ( PickUpItemAbility )     PickUpItemAbility->Initialize( Character );
    if ( PickUpItemAbility )     SprintAbility->Initialize( Character );
    if ( SprintAbility )         SprintAbility->Initialize( Character );
    if ( DeadAbility )           DeadAbility->Initialize( Character );
    if ( DropingTreasureAbility )   DropingTreasureAbility->Initialize( Character );
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
