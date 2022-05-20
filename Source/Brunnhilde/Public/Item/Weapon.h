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
	virtual AItem* DeepCopy() override;

	// 物件被使用或裝備...時要做的事
	virtual void OnUse( ABrunnhildeCharacter* Character ) override;
	virtual void OnEquiped( ABrunnhildeCharacter* Character )  override;
	virtual void OnUnEquiped( ABrunnhildeCharacter* Character )  override;
	virtual void OnDrawn( ABrunnhildeCharacter* Character )  override;
	virtual void OnSheath( ABrunnhildeCharacter* Character )  override;

	UFUNCTION( BlueprintCallable, Category="Weapon | UFUNCTION" )
	int  GetCurElfEnergy() { return CurElfEnergy; }
	UFUNCTION( BlueprintCallable, Category="Weapon | UFUNCTION" )
	void SetCurElfEnergy( int Energy ) { CurElfEnergy = Energy; }
	UFUNCTION( BlueprintCallable, Category="Weapon | UFUNCTION" )
	bool IsEnergeMax() { return CurElfEnergy >= MaxElfEnergy; }

	UFUNCTION( BlueprintCallable, Category="Weapon | UFUNCTION" )
	void HandleDrop();
	/*
	UFUNCTION( BlueprintCallable, Category="Weapon | UFUNCTION" )
	virtual void DeepCopy( AItem* CopyItem ) override;
	*/
	UFUNCTION( BlueprintCallable, Category="Weapon | UFUNCTION" )
	void ApplyDamage02( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
					  int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult );
	UFUNCTION( BlueprintCallable, Category="Weapon | UFUNCTION" )
	void ApplyDamage( AActor* DamagedActor, float BaseDamage, AController* EventInstigator, AActor* DamageCauser, TSubclassOf<UDamageType> DamageTypeClass );

public:
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | States" )
	int MaxElfEnergy = 100;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | States" )
	int RechargeValue = 20;

private:
	int CurElfEnergy = 0;
	FTimerHandle ResetCounterHandle;
};
