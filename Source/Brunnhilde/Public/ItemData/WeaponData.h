// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData/EquipmentData.h"
#include "WeaponData.generated.h"

class ABrunnhildeCharacter;
class AWeapon;
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
    virtual void OnEquiped( ABrunnhildeCharacter* Character ) override;
    virtual void OnUnEquiped( ABrunnhildeCharacter* Character ) override;
    virtual void OnDrawn( ABrunnhildeCharacter* Character ) override;
    virtual void OnSeath( ABrunnhildeCharacter* Character ) override;

public:
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Weapon | UPROPERTY" )
    FString EquipedSocket = DEFAULT_WEAPON_EQEUIPED_SOCKET;

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Weapon| UPROPERTY" )
    FString HoldSocket = DEFAULT_WEAPON_HOLD_SOCKET;
};
