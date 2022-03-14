// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Actions/Ability2.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "BrunnhildeCharacter.h"

// Sets default values for this component's properties
UAbility2::UAbility2()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	ControlCharacter = nullptr;
}


// Called when the game starts
void UAbility2::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAbility2::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAbility2::Initialize( ABrunnhildeCharacter* Character )
{
	SetControlCharacter( Character );
}

void UAbility2::SetControlCharacter( ABrunnhildeCharacter* Character )
{
	ControlCharacter = Character;
}


double UAbility2::SetControlPlayAnimMontage( UAnimMontage* Montage )
{
	if ( !IsValid( ControlCharacter ) || !IsValid( Montage ) )
	{
		return 0;
	}

	return ControlCharacter->PlayAnimMontage( Montage, Montage->RateScale );
}

ABrunnhildeCharacter* UAbility2::GetControlCharacter()
{
    return ControlCharacter;
}


UCharacterMovementComponent* UAbility2::GetControlMovement()
{
    if ( IsValid( ControlCharacter ) )
    {
        return ControlCharacter->GetCharacterMovement();
    }
    return nullptr;
}

UAnimMontage* UAbility2::GetControlActiveMontage()
{
    if ( IsValid( ControlCharacter ) )
    {
        return ControlCharacter->GetCurrentMontage();
    }
    return nullptr;
}

FTimerHandle UAbility2::GetControlMovementTimeHandle()
{
    if ( IsValid( ControlCharacter ) )
    {
        return ControlCharacter->GetMovementTimeHandle();
    }
    return FTimerHandle();
}

USkeletalMeshComponent* UAbility2::GetControlMesh()
{
    if ( IsValid( ControlCharacter ) )
    {
        return ControlCharacter->GetMesh();
    }
    return nullptr;
}