// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BrunnhildeDef.generated.h"


UENUM( BlueprintType )
enum class EArmourTypes : uint8
{
	EAT_Head    UMETA( DisplayName = "Head" ),
	EAT_Chest   UMETA( DisplayName = "Chest" ),
	EAT_Hand    UMETA( DisplayName = "Hand" ),
	EAT_Feet    UMETA( DisplayName = "Feet" ),
};

UENUM( BlueprintType )
enum class ECompetencyTypes : uint8
{
	ECT_Constitution    UMETA( DisplayName = "Constitution" ),
	ECT_Mentality       UMETA( DisplayName = "Mentality" ),
	ECT_Endurance       UMETA( DisplayName = "Endurance" ),
	ECT_Strength        UMETA( DisplayName = "Strength" ),
	ECT_Dexterity       UMETA( DisplayName = "Dexterity" ),
	ECT_Intelligence    UMETA( DisplayName = "Intelligence" ),
	ECT_Wisdom          UMETA( DisplayName = "Wisdom" ),
}; 

UENUM( BlueprintType )
enum class EItemRarityTypes : uint8
{
	EIRT_Common UMETA( DisplayName = "Common" ),
	EIRT_Rare   UMETA( DisplayName = "Rare" ),
	EIRT_Epic   UMETA( DisplayName = "Epic" ),
	EIRT_Legend UMETA( DisplayName = "Legend" ),
};

