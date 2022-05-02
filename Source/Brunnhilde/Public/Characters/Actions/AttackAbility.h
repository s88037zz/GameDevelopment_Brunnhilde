// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/Ability2.h"
#include "Actions/AttackCombo.h"
#include "AttackAbility.generated.h"
/**
 * 
 */
UCLASS( Blueprintable )
class BRUNNHILDE_API UAttackAbility : public UAbility2
{
	GENERATED_BODY()

public:
	virtual bool BeginAbility() override;
	bool UpdateAbility();

	virtual void Initialize( ABrunnhildeCharacter* Character ) override;
	void InitComboMontage();

	/* common used*/
	int ResetAttackCounter();
	UAttackCombo* GetCurrentCombo() const { return AttackCombos[ AttackCounter ]; }
	int GetAttackCounter() const { return AttackCounter; }

public:
	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	TArray< TSubclassOf<UAttackCombo> > AttackComboClasses;

	/* Endurance Cost in each attack */
	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	int EnduranceCost = 10;

	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	bool IsInAcceptableActtionRange = false;

	UFUNCTION( BlueprintCallable )
	TArray< UAttackCombo* > GetAttackCombos() const { return AttackCombos; }

	FTimerHandle AttackStatusHandle;

private:
	TArray< UAttackCombo* > AttackCombos;
	int AttackCounter = 0;

};

