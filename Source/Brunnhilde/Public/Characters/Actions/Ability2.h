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

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

/* Created In UE4 Deafault */
public:	
	// Sets default values for this component's properties
	UAbility2();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    /* Setter */
    void Initialize( ABrunnhildeCharacter* Character );
    void SetControlCharacter( ABrunnhildeCharacter* Character );
    double SetControlPlayAnimMontage( UAnimMontage* Montage );

    UFUNCTION( BlueprintCallable )
    virtual bool BeginAbility() PURE_VIRTUAL( UAbility2::BeginAbility, return true; );

public:
    ABrunnhildeCharacter* GetControlCharacter();
    UCharacterMovementComponent* GetControlMovement();
    UAnimMontage* GetControlActiveMontage();
    FTimerHandle GetControlMovementTimeHandle();
    USkeletalMeshComponent* GetControlMesh();
    
    void ChangeStateTo( ECharacterFSM State );
    bool IsState( ECharacterFSM State );
private:
    ABrunnhildeCharacter* ControlCharacter = nullptr;

};
