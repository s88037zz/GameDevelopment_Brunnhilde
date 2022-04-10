// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData/ItemData.h"
#include "WeaponData.generated.h"

class ABrunnhildeCharacter;

/**
 * 
 */
UCLASS()
class BRUNNHILDE_API UWeaponData : public UItemData
{
	GENERATED_BODY()

public:
    UWeaponData() = default;
    UWeaponData( UWeaponData* Weapon );

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Weapon | Profile | States" )
    float Damage = 10;

public:
    virtual void EquipOn( ABrunnhildeCharacter* Character ) override;
};
