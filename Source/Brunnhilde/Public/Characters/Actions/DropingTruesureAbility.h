// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Actions/Ability2.h"
#include "DropingTruesureAbility.generated.h"

class AItem;

/**
 * 
 */
UCLASS( Blueprintable )
class BRUNNHILDE_API UDropingTruesureAbility : public UAbility2
{
	GENERATED_BODY()
public:
	virtual bool BeginAbility() override;
	virtual void Initialize( ABrunnhildeCharacter* Character ) override;

	UFUNCTION()
	void OnDiead();

public:
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	TArray< AItem* > Treasures;
};
