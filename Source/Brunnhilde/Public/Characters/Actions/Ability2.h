// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Games/BrunnhildeDef.h"
#include "Ability2.generated.h"

class UCharacterMovementComponent;
class USkeletalMeshComponent;
class ABrunnhildeCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BRUNNHILDE_API UAbility2 : public UActorComponent
{
	GENERATED_BODY()

/* Created In UE4 Deafault */
public:	
	// Sets default values for this component's properties
	UAbility2();

    UFUNCTION( BlueprintCallable )
    virtual bool BeginAbility() PURE_VIRTUAL( UAbility2::BeginAbility, return true; );

    UFUNCTION( BlueprintCallable )
    virtual void Initialize( ABrunnhildeCharacter* Character );

public:
    ABrunnhildeCharacter* GetControlCharacter();
    UCharacterMovementComponent* GetControlMovement();
    UAnimMontage* GetControlActiveMontage();
    FTimerHandle GetControlMovementTimeHandle();
    USkeletalMeshComponent* GetControlMesh();
    
    /* Setter */
    void SetControlCharacter( ABrunnhildeCharacter* Character );
    double SetControlPlayAnimMontage( UAnimMontage* Montage );

    void ChangeStateTo( ECharacterFSM State );
    bool IsState( ECharacterFSM State );
private:
    ABrunnhildeCharacter* ControlCharacter = nullptr;

};
