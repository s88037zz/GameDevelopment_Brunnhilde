// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemData.generated.h"

class ABrunnhildeCharacter;
class AItem;
/**
 * 
 */
UCLASS( Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced )
class BRUNNHILDE_API UItemData : public UObject
{
	GENERATED_BODY()

public:
	UItemData();
	UItemData( UItemData* ItemData);

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Item | Profile " )
	FText UseActionText;

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Item | Profile " )
	class UStaticMesh* PickupMesh;

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Item | Profile " )
	class UTexture2D* Thumnail;

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Item | Profile " )
	FText ItemDisplayName;

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Item | Profile ", meta=( MultiLine=true ) )
	FText ItemDiscription;

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Item | Profile ", meta=( Clamp=0.0 ) )
	float Weight;

	UPROPERTY()
	class UInventoryComponent* OwningInventory;

	// 物件要作用在哪個角色上
	virtual void UseOn( ABrunnhildeCharacter* Character ) PURE_VIRTUAL( UItemData, );
	virtual void EquipOn( ABrunnhildeCharacter* Character ) PURE_VIRTUAL( UItemData, );
	
	virtual AItem* CreateInstance();

	UFUNCTION( BlueprintImplementableEvent )
	void OnUse( ABrunnhildeCharacter* Character );
	
};
