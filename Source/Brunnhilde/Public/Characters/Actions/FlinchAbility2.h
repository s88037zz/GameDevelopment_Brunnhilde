// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Actions/Ability2.h"
#include "FlinchAbility2.generated.h"

/**
 * 
 */

class UMatineeCameraShake;

enum class EDamagedDirection : int
{
	Right = 0,
	Front = 1,
	Left = 2
};

UCLASS( Blueprintable )
class BRUNNHILDE_API UFlinchAbility2 : public UAbility2
{
	GENERATED_BODY()
public:
	virtual bool BeginAbility() override;

	UFUNCTION( BlueprintCallable )
	void OnTakeDamaged( AActor * DamagedActor,
						float Damage,
						const class UDamageType* DamageType,
						class AController* InstigatedBy,
						AActor * DamageCauser );

public:
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	UAnimMontage* FlinchMontage_L;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	UAnimMontage* FlinchMontage_Mid;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	UAnimMontage* FlinchMontage_R;

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	TSubclassOf< UMatineeCameraShake > OnTakeDamageShakingType;

private:
	EDamagedDirection GetDamageDirection( AActor * DamagedCreator );

private:
	int DamagedCounter = -1;
};
