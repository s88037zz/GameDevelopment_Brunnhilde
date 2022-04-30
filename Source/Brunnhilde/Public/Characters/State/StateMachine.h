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
	void Process();

	UFUNCTION( BlueprintCallable, Category="Funcs | Settings" )
	ABrunnhildeCharacter* GetControlCharacter() { return Character; }
	UFUNCTION( BlueprintCallable, Category="Funcs | Settings" )
	void Initialize( ABrunnhildeCharacter* Character );

	//State
	void OnIdleState();
	void OnFightingState();
	void OnAttackingState();
	void OnAccpetedNextComboState();
	void OnFlinchState();
	void OnKnockDownState();

	//Transition
	UFUNCTION( BlueprintCallable, Category="Funcs | Actions" )
	void AttackAction();
	UFUNCTION( BlueprintCallable, Category="Funcs | Actions" )
	void DrawnWeaponAction();
	UFUNCTION( BlueprintCallable, Category="Funcs | Actions" )
	void SheathWeaponAction();
	UFUNCTION( BlueprintCallable, Category="Funcs | Actions" )
	void BeDamagedAction();
	UFUNCTION( BlueprintCallable, Category="Funcs | Actions" )
	void PickItemAction();
	UFUNCTION( BlueprintCallable, Category="Funcs | Actions" )
	void SprintAction();
	UFUNCTION( BlueprintCallable, Category="Funcs | Actions" )
	void LockEnemyAction();

	UFUNCTION( BlueprintCallable, Category="Funcs | Notifications" )
	void DrawnWeaponNotifcation();
	UFUNCTION( BlueprintCallable, Category="Funcs | Notifications" )
	void SheathWeaponNotifcation();
public:
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category=" Profile | Abilities" )
	TSubclassOf< UDrawnNSheathAbility > DrawnSheathClass;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category=" Profile | Abilities" )
	TSubclassOf< UAttackAbility >       AttackClass;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category=" Profile | Abilities" )
	TSubclassOf< UFlinchAbility2 >      FlinchClass;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category=" Profile | Abilities" )
	TSubclassOf< UPickUpItemAbility >   PickUpItemClass;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category=" Profile | Abilities" )
	TSubclassOf< ULockEnemyAbility >    LockEnemyClass;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category=" Profile | Abilities" )
	TSubclassOf< USprintAbility2 >      SprintClass;


	UPROPERTY( BlueprintReadWrite, Category=" Profile | Abilities" )
	UDrawnNSheathAbility* DrawnSheathAbility;
	UPROPERTY( BlueprintReadWrite, Category=" Profile | Abilities" )
	UAttackAbility*       AttackAbility;
	UPROPERTY( BlueprintReadWrite, Category=" Profile | Abilities" )
	UFlinchAbility2*      FlinchAbility;
	UPROPERTY( BlueprintReadWrite, Category=" Profile | Abilities" )
	UPickUpItemAbility*   PickUpItemAbility;
	UPROPERTY( BlueprintReadWrite, Category=" Profile | Abilities" )
	ULockEnemyAbility*    LockEnemyAbility;
	UPROPERTY( BlueprintReadWrite, Category=" Profile | Abilities" )
	USprintAbility2*      SprintAbility;

private:
	void ChangeStateTo( ECharacterFSM State );
	bool IsState( ECharacterFSM State );
	void SetControlCharacter( ABrunnhildeCharacter* ControlCharacter );
	void SetupAbilities();

private:
	ABrunnhildeCharacter* Character = nullptr;
	FTimerHandle CharacterStateHandle;

};
