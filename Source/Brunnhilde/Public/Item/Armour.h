// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.h"
#include "Armour.generated.h"

UCLASS()
class BRUNNHILDE_API AArmour : public AItem
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AArmour();

	virtual void Use( class ABrunnhildeCharacter* Character ) override;
	virtual void Equip( ABrunnhildeCharacter* Character, FString AttachSocket ) override;
	virtual void UnEquip() override;
};
