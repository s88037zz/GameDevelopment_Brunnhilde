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

	virtual void OnUse( ABrunnhildeCharacter* Character ) override;
	virtual void OnEquiped( ABrunnhildeCharacter* Character )  override;
	virtual void OnUnEquiped( ABrunnhildeCharacter* Character )  override;
	//virtual void OnDrawn( ABrunnhildeCharacter* Character ) override;
	//virtual void OnSeath( ABrunnhildeCharacter* Character ) override;

};
