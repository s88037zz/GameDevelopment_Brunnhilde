// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData/ItemData.h"
#include "Games/BrunnhildeDef.h"
#include "ArmourData.generated.h"
/**
 * 
 */
UCLASS()
class BRUNNHILDE_API UArmourData : public UItemData
{
	GENERATED_BODY()

public:
	UArmourData() = default;
	UArmourData( UArmourData* ArmourData );

	UPROPERTY( EditAnyWhere, BlueprintReadWrite, Category="Attribution" )
	int Constitution = 0;

	UPROPERTY( EditAnyWhere, BlueprintReadWrite, Category="Attribution" )
	int Mentality = 0;

	UPROPERTY( EditAnyWhere, BlueprintReadWrite, Category="Attribution" )
	int Endurance = 0;

	UPROPERTY( EditAnyWhere, BlueprintReadWrite, Category="Attribution" )
	int Strength = 0;

	UPROPERTY( EditAnyWhere, BlueprintReadWrite, Category="Attribution" )
	int Dexterity = 0;

	UPROPERTY( EditAnyWhere, BlueprintReadWrite, Category="Attribution" )
	int Intelligence = 0;

	UPROPERTY( EditAnyWhere, BlueprintReadWrite, Category="Attribution" )
	int Wisdom = 0;

	UPROPERTY( EditAnyWhere, BlueprintReadWrite, Category="Attribution" )
	EItemRarityTypes RarityType = EItemRarityTypes::EIRT_Common;

	UPROPERTY( EditAnyWhere, BlueprintReadWrite, Category="Attribution" )
	EArmourTypes AmorurType = EArmourTypes::EAT_Head;

public:
	virtual void EquipOn( ABrunnhildeCharacter* Character ) override;
};
