// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

/* Created In Brunnhilde Project */

public: /* Setter */
    void Initialize( ABrunnhildeCharacter* Character );

    void SetControlCharacter( ABrunnhildeCharacter* Character );
    double SetControlPlayAnimMontage( UAnimMontage* Montage );
public: /* Getter */
    ABrunnhildeCharacter* GetControlCharacter();
    UCharacterMovementComponent* GetControlMovement();
    UAnimMontage* GetControlActiveMontage();
    FTimerHandle GetControlMovementTimeHandle();
    USkeletalMeshComponent* GetControlMesh();

private:
    ABrunnhildeCharacter* ControlCharacter = nullptr;

};
