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

	// ...
}


// Called when the game starts
void USprintAbility2::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USprintAbility2::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USprintAbility2::StartSprint()
{ 
    ABrunnhildeCharacter* Character = GetControlCharacter();
    Character->GetCharacterMovement()->MaxWalkSpeed = MaxSprintSpeed;

    GetWorld()->GetTimerManager().SetTimer( SprintCostTimer, [this]()
    {
        float Cost = EnduranceCost / 100;
        GetControlCharacter()->GetEnduranceCmp()->Reduce( Cost );
    }, 0.01, true );
}


void USprintAbility2::StopSprint()
{
    ABrunnhildeCharacter* Character = GetControlCharacter();

    Character->GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
    GetWorld()->GetTimerManager().ClearTimer( SprintCostTimer );
}
