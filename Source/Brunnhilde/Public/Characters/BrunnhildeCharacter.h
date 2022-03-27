// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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

public:
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Montages", meta=( DisplayName="BlockingMontage" ) )
    UAnimMontage* BlockingMontage;

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Montages", meta=( DisplayName="DeadMontage" ) )
    UAnimMontage* DeadMontage;

    UPROPERTY( BlueprintReadWrite, EditAnywhere, Category="Weapons" )
    TArray< AWeapon* > WeaponInventory;

public:
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

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category="Inventory" )
	UInventoryComponent* Inventory;

public:
    UFUNCTION( BlueprintPure, Category="Profile" )
    AWeapon* GetEquippedWeapon();

    UFUNCTION( BlueprintCallable, Category="Profile" )
    AWeapon* SetEquippedWeapon( AWeapon* NewWeapon );

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | Equipment" )
    FName HoldWeaponSocket;

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | Equipment" )
    FName BackWeaponSocket;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | Equipment" )
	FName WeaponFightingSocket;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | Equipment" )
	float DamagedImpactRate = 1.0f;

	//¨¤¦â¯à¤OÂ¾
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | States" )
	int Constitution = 20;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | States" )
	int Mentality = 20;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | States" )
	int Endurance = 20;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | States" )
	int Strength = 20;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | States" )
	int	Dexterity = 20;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | States" )
	int Intelligence = 20;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | States" )
	int Wisdom = 20;

public: 
	UFUNCTION( BlueprintPure, Category="ActionsStates" )
	bool IsDrwanWeapon();
	
    UFUNCTION( BlueprintPure, Category="ActionsStates" )
  	bool IsReadyToAttack();

    UFUNCTION( BlueprintPure, Category="ActionsStates" )
	bool IsAttacking();

	UFUNCTION( BlueprintPure, Category="ActionsStates" )
	bool IsSaveAttack();

	UFUNCTION( BlueprintPure, Category="ActionsStates" )
	bool IsFlinching();

	UFUNCTION( BlueprintPure, Category="ActionsStates" )
	bool IsLockedEnemy();

public:

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
	void UseItem( class UItem* Item );

public:
	
	UFUNCTION( BlueprintCallable, Category="Notification")
	void HandleDrawnWeapon_Notification();

    UFUNCTION( BlueprintCallable, Category="Notification" )
	void HandleSheathWeapon_Notification();

public:
	UFUNCTION(BlueprintImplementableEvent, Category="Events")
	void OnLightAttack();

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
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	/** Returns HealthComponent subobject **/
	FORCEINLINE class UHealthComponent* GetHealthCmp() const { return HealthCmp;  }
	/** Returns EnduranceComponent subobject **/
	FORCEINLINE class UEnduranceComponent* GetEnduranceCmp() const { return EnduranceCmp; }

	UFUNCTION( BlueprintCallable )
	UPickUpItemAbility* GetPickUpItemAbility() const { return PickUpItemAbility; }

	UFUNCTION( BlueprintCallable )
	UDrawnNSheathAbility* GetDrawnNSheathAbility() const { return DrawnNSheathAbility; }

	UFUNCTION( BlueprintCallable )
    UNormalAttackAbility* GetNormalAttackAbility() const { return NormalAttackAbility; }

	//FORCEINLINE UNormalAttackAbility* GetNormalAttackAbility() const { return NormalAttackAbility; }
	FORCEINLINE UMeleeAttackAbility* GetMeleeAttackAbility() const { return MeleeAttackAbility; }
	FORCEINLINE UFlinchAbility2* GetFlinchAbility() const { return FlinchAbility; }
	FORCEINLINE UAbility2* GetCurrentActiveAbility() const { return CurrentActiveAbility; }

	FORCEINLINE FVector GetObjectDroppedLocation() const { return ObjectDroppedLocation->GetComponentLocation(); }
	FORCEINLINE FTimerHandle GetMovementTimeHandle() const { return TimeHandle; }

	
public:
	void SetMovementTimerHandle( double Duration, bool bEnableMovement );
	void SetAttacking( bool bAttack );
	void SetReadyToAttack( bool bStatus );
	void SetSaveAttack( bool bInputAttack );
	void SetIsFlinching( bool bFlinch );
	void SetActiveAbility( UAbility2* ActiveAbility );
	void SetLockedEnemy( bool Locked );

public:
    double GetMontageLeftTime( UAnimMontage* Montage, USkeletalMeshComponent* OwnerMesh );


private:
	AWeapon* EquippedWeapon;	
	FTimerHandle TimeHandle;

    bool bReadyToAttack;
    bool bAttacking;
    bool bSaveAttack;
	bool bFlinching;
	bool bIsLockedEnemy;

	ULockEnemyAbility* LockEnemyAbility = nullptr;
	UAbility2* CurrentActiveAbility = nullptr;
    FTimerHandle ResetCounterHandle;

};
