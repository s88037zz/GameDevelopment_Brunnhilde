// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Actions/Ability2.h"
#include "DeadAbility.generated.h"

/**
 * 
 */
UCLASS( Blueprintable )
class BRUNNHILDE_API UDeadAbility : public UAbility2
{
	GENERATED_BODY()

public:
	virtual void Initialize( ABrunnhildeCharacter* Character ) override;

	UFUNCTION( BlueprintCallable )
	void OnDied();

public:
	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	UAnimMontage* DeathMontage;

	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	float  TimeToDisappear = 1.f;
};
