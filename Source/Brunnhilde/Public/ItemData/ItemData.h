// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemData.generated.h"

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

	virtual void Use( class ABrunnhildeCharacter* Character ) PURE_VIRTUAL( AItem, );

	UFUNCTION( BlueprintImplementableEvent )
	void OnUse( class ABrunnhildeCharacter* Character );
	
};
