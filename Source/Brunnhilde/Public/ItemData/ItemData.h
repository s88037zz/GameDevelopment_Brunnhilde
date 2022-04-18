// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Games/BrunnhildeDef.h"
#include "ItemData.generated.h"

class ABrunnhildeCharacter;
class AItem;
class AActor;
class UInventoryComponent;
/**
 * 
 */
UCLASS( Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced )
class BRUNNHILDE_API UItemData : public UObject
{
	GENERATED_BODY()

public:
	UItemData();
	UItemData( UItemData* ItemData );

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
	UPROPERTY( EditAnyWhere, BlueprintReadWrite, Category="Attribution" )
	EItemRarityTypes RarityType = EItemRarityTypes::EIRT_Common;
	UPROPERTY( EditAnyWhere, BlueprintReadWrite, Category="Attribution" )
	EItemTypes ItemType = EItemTypes::EIT_PROP;

	UFUNCTION( BlueprintCallable )
	AItem* GetActor() { return ItemActor; }
	UFUNCTION( BlueprintCallable )
	void SetActor( AItem* Item ) { ItemActor = Item; }

	UPROPERTY()
	UInventoryComponent* OwningInventory;

	// 物件被使用或裝備...時要做的事
	virtual void OnUse( ABrunnhildeCharacter* Character ) PURE_VIRTUAL( UItemData, );
	virtual void OnEquiped( ABrunnhildeCharacter* Character )  PURE_VIRTUAL( UItemData, );
	virtual void OnUnEquiped( ABrunnhildeCharacter* Character )  PURE_VIRTUAL( UItemData, );
	virtual void OnDrawn( ABrunnhildeCharacter* Character )  PURE_VIRTUAL( UItemData, );
	virtual void OnSeath( ABrunnhildeCharacter* Character )  PURE_VIRTUAL( UItemData, );
protected:
	AItem* ItemActor = nullptr;
};
