// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData/EquipmentData.h"
#include "WeaponData.generated.h"

class ABrunnhildeCharacter;

/**
 * 
 */
UCLASS()
class BRUNNHILDE_API UWeaponData : public UEquipmentData
{
	GENERATED_BODY()

public:
    UWeaponData();
    UWeaponData( UWeaponData* Weapon );

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Weapon | Profile | States" )
    float Damage = 10;

public:
    virtual void EquipOn( ABrunnhildeCharacter* Character ) override;
};
