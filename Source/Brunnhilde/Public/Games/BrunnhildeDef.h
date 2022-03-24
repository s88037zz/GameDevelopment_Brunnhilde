// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BrunnhildeDef.generated.h"

/**
 * 
 */
UCLASS()
class BRUNNHILDE_API UBrunnhildeDef : public UObject
{
	GENERATED_BODY()
public:
	UBrunnhildeDef() = default;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category="Inventory | CompetencyTypes", DisplayName="Competency Types" )
	TArray< FString > CompetencyTypes = { "Constitution", "Mentality", "Endurance", "Strength",
												"Dexterity", "Intelligence", "Wisdom" };

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category="Inventory | ArmourTypes", DisplayName="Armour Types" )
	TArray< FString > ArmourTypes = { "Head", "Chest", "Hand", "Feet" };
};
