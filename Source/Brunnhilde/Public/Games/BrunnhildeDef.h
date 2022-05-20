// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BrunnhildeDef.generated.h"


UENUM( BlueprintType )
enum class EItemTypes : uint8
{
	EIT_PROP           UMETA( DisplayName = "Prop"),
	EIT_ARMOUR_Head    UMETA( DisplayName = "ArmourHead" ),
	EIT_ARMOUR_Chest   UMETA( DisplayName = "ArmourChest" ),
	EIT_ARMOUR_Hand    UMETA( DisplayName = "ArmourHand" ),
	EIT_ARMOUR_Feet    UMETA( DisplayName = "ArmourFeet" ),
	EIT_WEAPON         UMETA( DisplayName = "Weapon" )
};

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

UENUM( BlueprintType )
enum class ECharacterFSM : uint8
{
	ECFSM_Idle,
	ECFSM_Fighting,
	ECFSM_Attacking,
	ECFSM_AcceptedAttackCombo,
	ECFSM_Flinch,
	ECFSM_KnockDown,
	ECFSM_Dead,
	ECFSM_Pickup
};

USTRUCT( BlueprintType )
struct FCharcaterAttributes
{
	GENERATED_BODY()
public:
	inline void operator=( FCharcaterAttributes Attri )
	{
		Constitution    = Attri.Constitution;
		Mentality       = Attri.Mentality;
		Endurance       = Attri.Endurance;
		Strength        = Attri.Strength;
		Dexterity       = Attri.Dexterity;
		Intelligence    = Attri.Intelligence;
		Wisdom          = Attri.Wisdom;
	};
public:
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Profile | Attribution", meta=( Clamp = 0 ) )
	int Constitution;
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Profile | Attribution", meta=( Clamp = 0 ) )
	int Mentality;
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Profile | Attribution", meta=( Clamp = 0 ) )
	int Endurance;
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Profile | Attribution", meta=( Clamp = 0 ) )
	int Strength;
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Profile | Attribution", meta=( Clamp = 0 ) )
	int Dexterity;
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Profile | Attribution", meta=( Clamp = 0 ) )
	int Intelligence;
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Profile | Attribution", meta=( Clamp = 0 ) )
	int Wisdom;
};

#define NONE_SOCKET     ""
#define DEFAULT_WEAPON_EQEUIPED_SOCKET     "Weapon_Equiped_Socket"
#define DEFAULT_WEAPON_HOLD_SOCKET         "Weapon_Hold_Socket"
#define DEFAULT_ARMOUR_HEAD_SOCKET         "Armour_Head_Socket"
#define DEFAULT_ARMOUR_CHEST_SOCKET        "Armour_Chest_Socket"
#define DEFAULT_ARMOUR_HAND_SOCKET         "Armour_Hand_Socket"
#define DEFAULT_ARMOUR_FEET_SOCKET         "Armour_Feet_Socket"