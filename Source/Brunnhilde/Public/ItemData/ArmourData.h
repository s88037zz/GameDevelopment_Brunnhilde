// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData/EquipmentData.h"
#include "ArmourData.generated.h"

class AArmour;

/**
 * 
 */
UCLASS()
class BRUNNHILDE_API UArmourData : public UEquipmentData
{
	GENERATED_BODY()

public:
	UArmourData();
	UArmourData( UArmourData* ArmourData );

	virtual void OnEquiped( ABrunnhildeCharacter* Character ) override;
	virtual void OnUnEquiped( ABrunnhildeCharacter* Character ) override;

public:
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Weapon| UPROPERTY" )
	FString EquipedSocket = DEFAULT_ARMOUR_HEAD_SOCKET;

};
