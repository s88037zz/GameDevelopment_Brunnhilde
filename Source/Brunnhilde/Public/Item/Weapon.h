// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Weapon.generated.h"

class UWeaponData;
class UStaticMesh;
UCLASS()
class BRUNNHILDE_API AWeapon : public AItem
{
	GENERATED_BODY()

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="Weapon | UPROPERTY", meta=( AllowPrivateAccess="true" ) )
	class UBoxComponent* BoxCmp;

public:	
	// Sets default values for this actor's properties
	AWeapon();
	AWeapon( AWeapon* Weapon );

	virtual void Use( class ABrunnhildeCharacter* Character ) override;
	virtual void Equip( ABrunnhildeCharacter* Character, FString AttachSocket ) override;
	virtual void UnEquip() override;

	UFUNCTION( BlueprintCallable, Category="Weapon | UFUNCTION" )
	void Drawn( AActor* ACharacter, FString AttachSocket );
	UFUNCTION( BlueprintCallable, Category="Weapon | UFUNCTION" )
	void Sheath( AActor* ACharacter, FString AttachSocket );

	UFUNCTION( BlueprintImplementableEvent, Category="Weapon | UFUNCTION" )
    void OnHit();

	/*
	UFUNCTION( BlueprintCallable, Category="Weapon | UFUNCTION" )
	AWeapon* HandlePickupByCopy();
	*/
	UFUNCTION( BlueprintCallable, Category="Weapon | UFUNCTION" )
	void HandleDrop();

	UFUNCTION( BlueprintCallable, Category="Weapon | UFUNCTION" )
	AWeapon* DeepCopy();

	UFUNCTION( BlueprintCallable, Category="Weapon | UFUNCTION" )
	void ApplyDamage02( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
					  int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult );

private:
	int LastOwnerAttackCounter;
	FTimerHandle ResetCounterHandle;
};
