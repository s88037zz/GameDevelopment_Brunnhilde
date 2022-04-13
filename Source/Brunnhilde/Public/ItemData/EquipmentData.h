// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData/ItemData.h"
#include "EquipmentData.generated.h"

/**
 * 
 */
UCLASS()
class BRUNNHILDE_API UEquipmentData : public UItemData
{
	GENERATED_BODY()

public:
	UEquipmentData();
	UEquipmentData( UEquipmentData* Data );
	
};
