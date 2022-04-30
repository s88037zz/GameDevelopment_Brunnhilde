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

	/* common used*/
	int ResetAttackCounter();
	int GetNextComboIdx();
	void Initialize( ABrunnhildeCharacter* Character );
	void InitComboMontage();
	//  method1: input + notification
	void HandleNotification_AttackComboNext();
	// method2: only input
	void HandleAttackInput02();
	bool IsAcceptedActtion();

public:
	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	TArray< TSubclassOf<UAttackCombo> > AttackComboClasses;

	/* Endurance Cost in each attack */
	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	int EnduranceCost = 10;

	UFUNCTION( BlueprintCallable )
	TArray< UAttackCombo* > GetAttackCombos() const { return AttackCombos; }

    int AttackCounter = 0;
	FTimerHandle AttackStatusHandle;

private:
	TArray< UAttackCombo* > AttackCombos;
	UAttackCombo* CurrentActiveCombo;
};

