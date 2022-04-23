// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Actions/Ability2.h"
#include "PickUpItemAbility.generated.h"

/**
 * 
 */
UCLASS( Blueprintable )
class BRUNNHILDE_API UPickUpItemAbility : public UAbility2
{
	GENERATED_BODY()

public:
	virtual void BeginAbility() override;

	void PickUp();

public:
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	UAnimMontage* FlinchMontage_R;	UAnimMontage* PickUpMontage = nullptr;
};
