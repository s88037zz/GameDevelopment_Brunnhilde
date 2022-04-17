// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData/ItemData.h"
#include "EquipmentData.generated.h"


class UStaticMesh;

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

	UPROPERTY( EditAnyWhere, BlueprintReadWrite, Category="Equipment | UPROPERTY" )
	int Constitution = 0;

	UPROPERTY( EditAnyWhere, BlueprintReadWrite, Category="Equipment | UPROPERTY" )
	int Mentality = 0;

	UPROPERTY( EditAnyWhere, BlueprintReadWrite, Category="Equipment | UPROPERTY" )
	int Endurance = 0;

	UPROPERTY( EditAnyWhere, BlueprintReadWrite, Category="Equipment | UPROPERTY" )
	int Strength = 0;

	UPROPERTY( EditAnyWhere, BlueprintReadWrite, Category="Equipment | UPROPERTY" )
	int Dexterity = 0;

	UPROPERTY( EditAnyWhere, BlueprintReadWrite, Category="Equipment | UPROPERTY" )
	int Intelligence = 0;

	UPROPERTY( EditAnyWhere, BlueprintReadWrite, Category="Equipment | UPROPERTY" )
	int Wisdom = 0;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Equipment | UPROPERTY" )
	float Damage = 10;
};
