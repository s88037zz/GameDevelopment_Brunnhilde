// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Games/BrunnhildeDef.h"
#include "Actions/NormalAttackAbility.h"
#include "Actions/MeleeAttackAbility.h"
#include "Actions/FlinchAbility2.h"
#include "Actions/LockEnemyAbility.h"
#include "Actions/SprintAbility2.h"
#include "Actions/PickUpItemAbility.h"
#include "Actions/DrawnNSheathAbility.h"
#include "BrunnhildeCharacter.generated.h"


class UAnimMontage;
class UAnimComposite;
class AWeapon;
class UItemData;
class UHealthComponent;
class UEnduranceComponent;
class UInventoryComponent;

UCLASS(config=Game)
class ABrunnhildeCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** Blood **/
    UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Ailities", meta = ( AllowPrivateAccess = "true" ))
	class UHealthComponent* HealthCmp;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Ailities", meta = ( AllowPrivateAccess = "true" ) )
	class UEnduranceComponent* EnduranceCmp;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Other", meta = ( AllowPrivateAccess = "true" ) )
	class USceneComponent* ObjectDroppedLocation;

public:
	ABrunnhildeCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	//測試效果
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Montages", meta=( DisplayName="BlockingMontage" ) )
    UAnimMontage* BlockingMontage;

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Montages", meta=( DisplayName="DeadMontage" ) )
    UAnimMontage* DeadMontage;

    UPROPERTY( BlueprintReadWrite, EditAnywhere, Category="Weapons" )
    TArray< AWeapon* > WeaponInventory;

	// 角色重要能力
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Abilities" )
	UPickUpItemAbility* PickUpItemAbility;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Abilities" )
	UDrawnNSheathAbility* DrawnNSheathAbility;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Abilities" )
	UNormalAttackAbility* NormalAttackAbility;
	
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Abilities" )
	UMeleeAttackAbility* MeleeAttackAbility;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Abilities" )
	UFlinchAbility2* FlinchAbility;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Abilities" )
	TSubclassOf< ULockEnemyAbility > LockEnemyClass;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Abilities" )
	USprintAbility2* SprintAbility;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Inventory" )
	UInventoryComponent* Inventory;

	//裝備參數設定
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | Socket" )
    FName WeaponHoldSocket;

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | Socket" )
    FName WeaponEquippedSocket;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | Socket" )
	FName WeaponFightingSocket;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | Socket" )
	FName ArmourHeadSocket;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | Socket" )
	FName ArmourChestSocket;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | Socket" )
	FName ArmourHandSocket;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | Socket" )
	FName ArmourFeetSocket;


	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | Equipment" )
	float DamagedImpactRate = 1.0f;

	//角色能力值
	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category="Profile | States" )
	int Constitution = 20;

	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category="Profile | States" )
	int Mentality = 20;

	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category="Profile | States" )
	int Endurance = 20;

	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category="Profile | States" )
	int Strength = 20;

	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category="Profile | States" )
	int	Dexterity = 20;

	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category="Profile | States" )
	int Intelligence = 20;

	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category="Profile | States" )
	int Wisdom = 20;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | States" )
	int DefaultConstitution = 20;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | States" )
	int DefaultMentality = 20;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | States" )
	int DefaultEndurance = 20;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | States" )
	int DefaultStrength = 20;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | States" )
	int	DefaultDexterity = 20;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | States" )
	int DefaultIntelligence = 20;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | States" )
	int DefaultWisdom = 20;

public:
	//角色狀態機
	/*
	UFUNCTION( BlueprintPure, Category="ActionsStates" )
	bool IsDrwanWeapon();
	
    UFUNCTION( BlueprintPure, Category="ActionsStates" )
  	bool IsReadyToAttack();

    UFUNCTION( BlueprintPure, Category="ActionsStates" )
	bool IsAttacking();
	*/
	UFUNCTION( BlueprintPure, Category="ActionsStates" )
	bool IsSaveAttack();

	UFUNCTION( BlueprintPure, Category="ActionsStates" )
	bool IsFlinching();

	UFUNCTION( BlueprintPure, Category="ActionsStates" )
	bool IsLockedEnemy();

	// 角色使用能力
    UFUNCTION( BlueprintCallable, Category="Actions" )
    void PickupWeapon();

    UFUNCTION( BlueprintCallable, Category="Actions" )
    void DrawnWeapon();

    UFUNCTION( BlueprintCallable, Category="Actions" )
    void SheathWeapon();

    UFUNCTION( BlueprintCallable, Category="Actions" )
    void LightAttack();

	UFUNCTION( BlueprintCallable, Category="Actions" )
	void MeleeAttack();

    UFUNCTION( BlueprintCallable, Category="Actions" )
    void BlockAttack();

	UFUNCTION( BlueprintCallable, Category="Actions" )
	void LockEnemy();

    UFUNCTION( BlueprintCallable, Category="Actions" )
	void Dead();

	UFUNCTION( BlueprintCallable, Category="Actions" )
	void StartSprint();

	UFUNCTION( BlueprintCallable, Category="Actions" )
	void StopSprint();

	UFUNCTION( BlueprintCallable, Category="Actions" )
	void UseItem( UItemData* Item );

	//動畫判定
	UFUNCTION( BlueprintCallable, Category="Notification")
	void HandleDrawnNotification();

	UFUNCTION( BlueprintCallable, Category="Notification" )
	void HandleSheathNotification();

	UFUNCTION( BlueprintImplementableEvent, Category="Events" )
	void OnLightAttack();

	UFUNCTION( BlueprintCallable, Category="Notification" )
	void HandleEquipmentUpdated();


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

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	UFUNCTION( BlueprintCallable, Category="Getter" )
	UItemData* GetEquipedWeapon();

	// Getter
	class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	class UHealthComponent* GetHealthCmp() const { return HealthCmp;  }
	class UEnduranceComponent* GetEnduranceCmp() const { return EnduranceCmp; }

	UFUNCTION( BlueprintCallable )
	UPickUpItemAbility* GetPickUpItemAbility() const { return PickUpItemAbility; }

	UFUNCTION( BlueprintCallable )
	UDrawnNSheathAbility* GetDrawnNSheathAbility() const { return DrawnNSheathAbility; }

	UFUNCTION( BlueprintCallable )
    UNormalAttackAbility* GetNormalAttackAbility() const { return NormalAttackAbility; }

	UMeleeAttackAbility* GetMeleeAttackAbility() const { return MeleeAttackAbility; }
	UFlinchAbility2* GetFlinchAbility() const { return FlinchAbility; }
	UAbility2* GetCurrentActiveAbility() const { return CurrentActiveAbility; }
	FVector GetObjectDroppedLocation() const { return ObjectDroppedLocation->GetComponentLocation(); }
	FTimerHandle GetMovementTimeHandle() const { return TimeHandle; }
	ECharacterStates GetCurrentState() const { return CurrentState; }

	double GetMontageLeftTime( UAnimMontage* Montage, USkeletalMeshComponent* OwnerMesh );

	//Setter
	void SetMovementTimerHandle( double Duration, bool bEnableMovement );
	void SetSaveAttack( bool bInputAttack );
	void SetIsFlinching( bool bFlinch );
	void SetActiveAbility( UAbility2* ActiveAbility );
	void SetLockedEnemy( bool Locked );
	void SetCurrentState( ECharacterStates eState ) { CurrentState = eState; }

private:
	void ResetStatsToDefault();

private:
	AWeapon* EquippedWeapon;	
	FTimerHandle TimeHandle;

    bool bSaveAttack;
	bool bFlinching;
	bool bIsLockedEnemy;

	ULockEnemyAbility* LockEnemyAbility = nullptr;
	UAbility2* CurrentActiveAbility = nullptr;
    FTimerHandle ResetCounterHandle;

	ECharacterStates  CurrentState = ECharacterStates::ECS_Idle;
};
