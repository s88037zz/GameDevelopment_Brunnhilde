// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Actions/Ability2.h"
#include "LockEnemyAbility.generated.h"

/**
 * 
 */
UCLASS( Blueprintable, BlueprintType )
class BRUNNHILDE_API ULockEnemyAbility : public UAbility2
{
	GENERATED_BODY()

public:
	virtual bool BeginAbility() override;

	void Lock();

};
