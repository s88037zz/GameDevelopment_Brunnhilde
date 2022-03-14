// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Actions/Ability2.h"
#include "DrawnNSheathAbility.generated.h"

/**
 * 
 */
UCLASS()
class BRUNNHILDE_API UDrawnNSheathAbility : public UAbility2
{
	GENERATED_BODY()
	
public:
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Montage" )
	UAnimMontage* DrawnWeaponMontage;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Montage" )
	UAnimMontage* SheathWeaponMontage;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	float Idle2SheathTime = 5.0f;

protected:
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

public:
	UFUNCTION( BlueprintCallable )
	void Drawn();
	
	UFUNCTION( BlueprintCallable )
	void Sheath();

	UFUNCTION( BlueprintCallable )
	void ResetIdle2SheathCounter();

public:
	bool bWeaponDrawn;

private:
	float TimeCounter;
};
