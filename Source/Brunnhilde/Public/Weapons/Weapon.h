// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class UArrowComponent;
class UBoxComponent;

UCLASS()
class BRUNNHILDE_API AWeapon : public AActor
{
	GENERATED_BODY()

    UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="Weapon", meta=( AllowPrivateAccess="true" ) )
	USceneComponent* RootCmp;

    UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="Weapon", meta=( AllowPrivateAccess="true" ) )
    UArrowComponent* ArrowCmp;
	
    UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="Weapon", meta=( AllowPrivateAccess="true" ) )
    UStaticMeshComponent* MeshCmp;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="Weapon", meta=( AllowPrivateAccess="true" ) )
	UBoxComponent* BoxCmp;

public:	
	// Sets default values for this actor's properties
	AWeapon();
	AWeapon( AWeapon* Weapon );

    UPROPERTY( BlueprintReadWrite, EditAnywhere, Category="Weapon" )
    float Damage = 10;

	UFUNCTION( BlueprintImplementableEvent, Category="Weapon")
	void OnEquipped();
 
    UFUNCTION( BlueprintImplementableEvent, Category="Weapon" )
    void OnUnEquipped();

    UFUNCTION( BlueprintImplementableEvent, Category="Weapon" )
    void OnHit();

	UFUNCTION()
	void OnPickup( AActor* EquippedActor );

	UFUNCTION()
	AWeapon* OnPickup_Copy();

	UFUNCTION()
	void OnDrop();

	UFUNCTION()
	AWeapon* Duplicate();

	UFUNCTION( BlueprintCallable )
	void ApplyDamage02( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
					  int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult );

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	FORCEINLINE UMeshComponent* GetMeshComponent() { return MeshCmp; }

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	int LastOwnerAttackCounter;
	FTimerHandle ResetCounterHandle;

};
