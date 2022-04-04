// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Games/BrunnhildeDef.h"
#include "Item.h"
#include "Armour.generated.h"

UCLASS()
class BRUNNHILDE_API UArmour : public UItem
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	UArmour();

protected:
	virtual void Use( class ABrunnhildeCharacter* Character ) override;

public:
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
	EItemRarityTypes RarityType;

	UPROPERTY( EditAnyWhere, BlueprintReadWrite, Category="Attribution" )
	EArmourTypes AmorurType;
};
