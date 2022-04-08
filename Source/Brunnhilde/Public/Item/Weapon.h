// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Weapon.generated.h"

class UWeaponData;

UCLASS()
class BRUNNHILDE_API AWeapon : public AItem
{
	GENERATED_BODY()

    UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="Weapon | Components", meta=( AllowPrivateAccess="true" ) )
	class USceneComponent* RootCmp;

    UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="Weapon | Components", meta=( AllowPrivateAccess="true" ) )
	class UArrowComponent* ArrowCmp;
	
    UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="Weapon | Components", meta=( AllowPrivateAccess="true" ) )
	class UStaticMeshComponent* MeshCmp;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="Weapon | Components", meta=( AllowPrivateAccess="true" ) )
	class UBoxComponent* BoxCmp;

protected:
	virtual void Use( class ABrunnhildeCharacter* Character ) override;

public:	
	// Sets default values for this actor's properties
	AWeapon();
	AWeapon( AWeapon* Weapon );
	AWeapon( UWeaponData* WeaponData );

	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category="Weapon | Profile | States" )
	class UWeaponData* WeaponData;

	UFUNCTION( BlueprintCallable, Category="Functions" )
	UMeshComponent* GetMeshComponent() { return MeshCmp; }

	UFUNCTION( BlueprintImplementableEvent, Category="Weapon | ImplementableEvents")
	void OnEquipped();
 
    UFUNCTION( BlueprintImplementableEvent, Category="Weapon | ImplementableEvents" )
    void OnUnEquipped();

    UFUNCTION( BlueprintImplementableEvent, Category="Weapon | ImplementableEvents" )
    void OnHit();

	UFUNCTION( BlueprintCallable, Category="Weapon | Functions")
	void HandlePickup( AActor* EquippedActor );

	UFUNCTION( BlueprintCallable, Category="Weapon | Functions" )
	AWeapon* HandlePickupByCopy();

	UFUNCTION( BlueprintCallable, Category="Weapon | Functions" )
	void HandleDrop();

	UFUNCTION( BlueprintCallable, Category="Weapon | Functions" )
	AWeapon* DeepCopy();

	UFUNCTION( BlueprintCallable, Category="Weapon | Functions" )
	void ApplyDamage02( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
					  int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult );

private:
	int LastOwnerAttackCounter;
	FTimerHandle ResetCounterHandle;
};
