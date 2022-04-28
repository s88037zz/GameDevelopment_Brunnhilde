// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Actions/SprintAbility2.h"
#include "BrunnhildeCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Games/EnduranceComponent.h"

// Sets default values for this component's properties
USprintAbility2::USprintAbility2()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

    bIsSprint = false;
}


bool USprintAbility2::BeginAbility()
{
    if ( bIsSprint )
    {
        StopSprint();
    }
    if ( !bIsSprint )
    {
        StartSprint();
    }
    return true;
}


void USprintAbility2::StartSprint()
{ 
    if ( bIsSprint )
    {
        return;
    }

    ABrunnhildeCharacter* Character = GetControlCharacter();

    Character->GetCharacterMovement()->MaxWalkSpeed = MaxSprintSpeed;
    GetWorld()->GetTimerManager().SetTimer( SprintCostTimer, [this]()
    {
        float Cost = EnduranceCost / 100;
        GetControlCharacter()->GetEnduranceCmp()->Reduce( Cost );
    }, 0.01, true );
    bIsSprint = true;
}


void USprintAbility2::StopSprint()
{
    if ( !bIsSprint )
    {
        return;
    }

    ABrunnhildeCharacter* Character = GetControlCharacter();

    Character->GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
    GetWorld()->GetTimerManager().ClearTimer( SprintCostTimer );
    bIsSprint = false;
}
