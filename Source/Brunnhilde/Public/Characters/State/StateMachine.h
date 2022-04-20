// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StateMachine.generated.h"

class UAnimMontage;

/**
 * 
 */
UCLASS(Blueprintable)
class BRUNNHILDE_API UStateMachine : public UObject
{
	GENERATED_BODY()

public:
	UStateMachine() = default;

	void Tick();

	//State
	void OnIdle();
	void OnReadyToAttackState();
	void OnAttackingState();
	void OnAccpetedNextComboState();

	//Transition
	void DoAttackAction();
	void DoDrawnWeapon();
	void DoSheathWeapon();

private:
	enum class ECharacterFSM : uint8
	{
		ECFSM_Idle,
		ECFSM_ReadyToAttack,
		ECFSM_Attacking,
		ECFSM_AcceptedAttackCombo
	};

	ECharacterFSM eCurrentState = ECharacterFSM::ECFSM_Idle;
	UAnimMontage* AttckMontage = nullptr;
};
