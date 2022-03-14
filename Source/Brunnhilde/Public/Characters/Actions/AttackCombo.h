// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimMontage.h"
#include "AttackCombo.generated.h"

/**
 * 
 */
UCLASS( config=Engine, Blueprintable, Blueprintable)
class BRUNNHILDE_API UAttackCombo : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	UAnimMontage* AttackMontage;

	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	USoundBase* SoundEffect;

	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	float LeftTimeToCombo = 0.5;
	
	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	TSubclassOf< UMatineeCameraShake > OnHitShakingType;
};
