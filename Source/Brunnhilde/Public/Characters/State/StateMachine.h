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
	void Tick();

	UFUNCTION( BlueprintCallable )
	ABrunnhildeCharacter* GetControlCharacter() { return Character; }
	UFUNCTION( BlueprintCallable )
	void Initialize( ABrunnhildeCharacter* Character );
	UFUNCTION( BlueprintCallable )
	void SetupPlayerInputComponent( UInputComponent* PlayerInputComponent );

	UFUNCTION( BlueprintCallable, Category="Notification" )
	void HandleDrawnNotification();
	UFUNCTION( BlueprintCallable, Category="Notification" )
	void HandleSheathNotification();

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

public:
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Abilities" )
	TSubclassOf< UDrawnNSheathAbility > DrawnSheathClass;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Abilities" )
	TSubclassOf< UAttackAbility >       AttackClass;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Abilities" )
	TSubclassOf< UFlinchAbility2 >      FlinchClass;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Abilities" )
	TSubclassOf< UPickUpItemAbility >   PickUpItemClass;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Abilities" )
	TSubclassOf< ULockEnemyAbility >    LockEnemyClass;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Abilities" )
	TSubclassOf< USprintAbility2 >      SprintClass;


	UPROPERTY( BlueprintReadWrite, Category="Abilities" )
	UDrawnNSheathAbility* DrawnSheathAbility;
	UPROPERTY( BlueprintReadWrite, Category="Abilities" )
	UAttackAbility*       AttackAbility;
	UPROPERTY( BlueprintReadWrite, Category="Abilities" )
	UFlinchAbility2*      FlinchAbility;
	UPROPERTY( BlueprintReadWrite, Category="Abilities" )
	UPickUpItemAbility*   PickUpItemAbility;
	UPROPERTY( BlueprintReadWrite, Category="Abilities" )
	ULockEnemyAbility*    LockEnemyAbility;
	UPROPERTY( BlueprintReadWrite, Category="Abilities" )
	USprintAbility2*      SprintAbility;

private:
	void ChangeStateTo( ECharacterFSM State );
	bool IsState( ECharacterFSM State );
	void SetControlCharacter( ABrunnhildeCharacter* ControlCharacter );
	void SetupAbilities();
private:
	ABrunnhildeCharacter* Character = nullptr;
	UAnimMontage* NextMontage = nullptr;


};
