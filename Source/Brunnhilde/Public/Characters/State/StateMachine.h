// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Games/BrunnhildeDef.h"
#include "StateMachine.generated.h"

class UAnimMontage;
class UAttackAbility;
class UFlinchAbility2;
class UDrawnNSheathAbility;
class ABrunnhildeCharacter;
class UPickUpItemAbility;
class ULockEnemyAbility;
class USprintAbility2;
class UPlayerInputComponent;
/**
 * 
 */
UCLASS(Blueprintable)
class BRUNNHILDE_API UStateMachine : public UObject
{
	GENERATED_BODY()

public:
	UStateMachine() = default;
	UStateMachine( ABrunnhildeCharacter* Character );

	void Tick();

	UFUNCTION( BlueprintCallable )
	ABrunnhildeCharacter* GetControlCharacter() { return m_Character; }
	UFUNCTION( BlueprintCallable )
	void SetControlCharacter( ABrunnhildeCharacter* Character );
	UFUNCTION( BlueprintCallable )
	void SetupPlayerInputComponent( UInputComponent* PlayerInputComponent );


	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Abilities" )
	UDrawnNSheathAbility* DrawnSheathAbility;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Abilities" )
	UAttackAbility* AttackAbility;
	UFUNCTION( BlueprintCallable, Category="Notification" )
	void HandleDrawnNotification();
	UFUNCTION( BlueprintCallable, Category="Notification" )
	void HandleSheathNotification();
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Abilities" )
	UFlinchAbility2* FlinchAbility;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Abilities" )
	UPickUpItemAbility* PickUpItemAbility;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Abilities" )
    ULockEnemyAbility* LockEnemyClass;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Abilities" )
	USprintAbility2* SprintAbility;

	//State
	void OnIdleState();
	void OnFightingState();
	void OnAttackingState();
	void OnAccpetedNextComboState();
	void OnFlinchState();
	void OnKnockDownState();

	//Transition
	void AttackAction();
	void DrawnWeaponAction();
	void SheathWeaponAction();
	void BeDamagedAction();
	void PickItemAction();
	void SprintAction();
	void LockEnemyAction();

private:
	void ChangeStateTo( ECharacterFSM State );
	bool IsState( ECharacterFSM State );

private:
	ABrunnhildeCharacter* m_Character = nullptr;
	UAnimMontage* m_NextMontage = nullptr;


};
