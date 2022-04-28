// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/Ability2.h"
#include "SprintAbility2.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BRUNNHILDE_API USprintAbility2 : public UAbility2
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USprintAbility2();

	virtual bool BeginAbility() override;

public:
	/* Endurance Cost  per second */
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	float EnduranceCost = 5;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	float MaxWalkSpeed = 600.f;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	float MaxSprintSpeed = 1000.f;

	UFUNCTION( BlueprintCallable )
	void StartSprint();

	UFUNCTION( BlueprintCallable )
	void StopSprint();

private:
	FTimerHandle SprintCostTimer;
	bool bIsSprint;
};
