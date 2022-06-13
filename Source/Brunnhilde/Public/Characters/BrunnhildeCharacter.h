// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Games/BrunnhildeDef.h"
#include "BrunnhildeCharacter.generated.h"


class UAnimComposite;
class AWeapon;
class UCameraComponent;
class USpringArmComponent;
class UHealthComponent;
class UEnduranceComponent;
class UInventoryComponent;
class USceneComponent;
class UTransactionComponent;
class UStateMachine;
class UAnimMontage;

UCLASS(config=Game)
class ABrunnhildeCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABrunnhildeCharacter();

public:
	UFUNCTION( BlueprintCallable, Category="Funcs | Actions" )
	void Attack();
	UFUNCTION( BlueprintCallable, Category="Funcs | Actions" )
	void PickItem();
	UFUNCTION( BlueprintCallable, Category="Funcs | Actions" )
	void Sprint();
	UFUNCTION( BlueprintCallable, Category="Funcs | Actions" )
	void LockEnemy();

	UFUNCTION( BlueprintCallable, Category="Funcs | Members" )
	AWeapon* GetEquipedWeapon();
	UFUNCTION( BlueprintCallable, Category="Funcs | Members" )
	UStateMachine* GetStateMachine();
	UFUNCTION( BlueprintCallable, Category="Funcs | Members" )
	FVector GetObjectDroppedLocation() const;
	UFUNCTION( BlueprintCallable, Category="Funcs | Members" )
	FVector GetStandLocation() const;
	UFUNCTION( BlueprintCallable, Category="Funcs | Members" )
	FTimerHandle GetMovementTimeHandle() const { return TimeHandle; }
	UFUNCTION( BlueprintCallable, Category="Funcs | Members" )
	void SetMovementTimerHandle( float Duration, bool bEnableMovement );
	UFUNCTION( BlueprintCallable, Category="Funcs | Members" )
	float GetMontageLeftTime( UAnimMontage* Montage, USkeletalMeshComponent* OwnerMesh );
	UFUNCTION( BlueprintCallable, Category="Funcs | Members" )
	bool IsRequiredNextMontage() const { return RequiredNextMontage; }
	UFUNCTION( BlueprintCallable, Category="Funcs | Members" )
	void SetRequiredNextMontage( bool Required );

	UFUNCTION( BlueprintCallable, Category="Funcs | Components")
	USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	UFUNCTION( BlueprintCallable, Category="Funcs | Components" )
	UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	UFUNCTION( BlueprintCallable, Category="Funcs | Components" )
	UHealthComponent* GetHealthCmp() const { return HealthCmp; }
	UFUNCTION( BlueprintCallable, Category="Funcs | Components" )
	UEnduranceComponent* GetEnduranceCmp() const { return EnduranceCmp; }
	UFUNCTION( BlueprintCallable, Category="Funcs | Components" )
	UTransactionComponent* GetTransactionCmp() const { return TransactionCmp; }
	UFUNCTION( BlueprintCallable, Category="Funcs | Components" )
	UInventoryComponent* GetInventoryCmp() const { return InventoryCmp; }
	
	UFUNCTION( BlueprintCallable, Category="Funcs | Others" )
	void HandleEquipmentUpdated();

public:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = ( AllowPrivateAccess = "true" ) )
	 USpringArmComponent* CameraBoom;
	/** Follow camera */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = ( AllowPrivateAccess = "true" ) )
	UCameraComponent* FollowCamera;
	/** Blood **/
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Ailities", meta = ( AllowPrivateAccess = "true" ) )
	UHealthComponent* HealthCmp;
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Ailities", meta = ( AllowPrivateAccess = "true" ) )
	UEnduranceComponent* EnduranceCmp;
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Ailities", meta = ( AllowPrivateAccess = "true" ) )
	UTransactionComponent* TransactionCmp;
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Other", meta = ( AllowPrivateAccess = "true" ) )
	USceneComponent* ObjectDroppedCmp;


	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category=Camera )
	float BaseTurnRate;
	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category=Camera )
	float BaseLookUpRate;

	// 角色重要能力
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Inventory" )
	UInventoryComponent* InventoryCmp;

	//裝備參數設定
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | Equipment" )
	float DamagedImpactRate = 1.0f;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | State Machine" )
	ECharacterFSM CurrentState = ECharacterFSM::ECFSM_Idle;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | State Machine" )
	TSubclassOf< UStateMachine > StateMachineClass;

	//角色能力值
	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category="Profile | State Values" )
	int Constitution = 20;
	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category="Profile | State Values" )
	int Mentality = 20;
	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category="Profile | State Values" )
	int Endurance = 20;
	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category="Profile | State Values" )
	int Strength = 20;
	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category="Profile | State Values" )
	int	Dexterity = 20;
	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category="Profile | State Values" )
	int Intelligence = 20;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | State Values" )
	int DefaultConstitution = 20;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | State Values" )
	int DefaultMentality = 20;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | State Values" )
	int DefaultEndurance = 20;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | State Values" )
	int DefaultStrength = 20;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | State Values" )
	int	DefaultDexterity = 20;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | State Values" )
	int DefaultIntelligence = 20;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="Profile | Montages" )
	TArray< UAnimMontage* > NextMontageQueue;

/* Third Person Character Default function */
protected:
	/* Begin Play ( Regist Delegete) */
	void BeginPlay() override;
    virtual void Tick( float DeltaSeconds ) override;
	/** Resets HMD orientation in VR. */
	void OnResetVR();
	/** Called for forwards/backward input */
	void MoveForward(float Value);
	/** Called for side to side input */
	void MoveRight(float Value);
	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);
	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);
	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void ResetStatsToDefault();

private:
	FTimerHandle TimeHandle;
    FTimerHandle ResetCounterHandle;
	UStateMachine* StateMachine = nullptr;
	bool RequiredNextMontage = false;

};
