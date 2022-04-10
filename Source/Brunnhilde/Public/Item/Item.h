// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Actor.h"
#include "ItemData/ItemData.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS( Abstract, BlueprintType, Blueprintable, DefaultToInstanced )
class BRUNNHILDE_API AItem : public AActor
{
	GENERATED_BODY()
public: 
	AItem();
	AItem( UItemData* ItemData );

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Item" )
	FText UseActionText;

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Item" )
	class UStaticMesh* PickupMesh;

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Item" )
	class UTexture2D* Thumnail;

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Item" )
	FText ItemDisplayName;

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Item", meta=( MultiLine=true ) )
	FText ItemDiscription;

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Item", meta=( Clamp=0.0 ) )
	float Weight;

	UPROPERTY()
	class UInventoryComponent* OwningInventory;

	virtual void Use( class ABrunnhildeCharacter* Character ) PURE_VIRTUAL( AItem, );

	UFUNCTION( BlueprintImplementableEvent )
	void OnUse( class ABrunnhildeCharacter* Character );

private:
	UItemData* ItemData = nullptr;
};
