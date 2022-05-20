// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Actor.h"
#include "Games/BrunnhildeDef.h"
#include "Item.generated.h"

class ABrunnhildeCharacter;
class UStaticMeshComponent;

/**
 * 
 */

USTRUCT( BlueprintType )
struct FItemSetting
{
	GENERATED_BODY()
public:
	FCharcaterAttributes& GetCharacterAttibutes() { return CharacterAttributes; }
	inline void operator=( FItemSetting Data )
	{
		UseActionText   = Data.UseActionText;
		PickupMesh      = Data.PickupMesh;
		DroppedMesh     = Data.DroppedMesh;
		Thumnail        = Data.Thumnail;
		ItemDisplayName = Data.ItemDisplayName;
		Weight          = Data.Weight;
		RarityType      = Data.RarityType;
		ItemType        = Data.ItemType;
		EquipedSocket   = Data.EquipedSocket;
		HoldSocket		= Data.HoldSocket;
		CharacterAttributes = Data.CharacterAttributes;
	};
public:
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Profile | Setting" )
	FText UseActionText;
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Profile | Setting" )
	class UStaticMesh* PickupMesh;
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Profile | Setting " )
	class UStaticMesh* DroppedMesh;
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Profile | Setting" )
	class UTexture2D* Thumnail;
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Profile | Setting" )
	FText ItemDisplayName;
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Profile | Setting", meta=( MultiLine=true ) )
	FText ItemDiscription;
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Profile | Setting", meta=( Clamp=0.0 ) )
	float Weight;
	UPROPERTY( EditAnyWhere, BlueprintReadWrite, Category="Profile | Setting" )
	EItemRarityTypes RarityType = EItemRarityTypes::EIRT_Common;
	UPROPERTY( EditAnyWhere, BlueprintReadWrite, Category="Profile | Setting" )
	EItemTypes ItemType = EItemTypes::EIT_PROP;
	UPROPERTY( EditAnyWhere, BlueprintReadWrite, Category="Profile | Setting" )
	FString EquipedSocket;
	UPROPERTY( EditAnyWhere, BlueprintReadWrite, Category="Profile | Setting" )
	FString HoldSocket;

	UPROPERTY( EditAnyWhere, Category="Profile | Setting" )
	FCharcaterAttributes CharacterAttributes;
};

UCLASS( BlueprintType, Blueprintable, DefaultToInstanced )
class BRUNNHILDE_API AItem : public AActor
{
	GENERATED_BODY()

public:
	AItem();
	AItem( AItem* Item );
	UFUNCTION( BlueprintCallable, Category="Item | UFUNCTION" )
	virtual AItem* DeepCopy();
	UFUNCTION( BlueprintCallable, Category="Item | UFUNCTION" )
	virtual void DeepCopyTo( AItem* CopyItem );

	UFUNCTION( BlueprintCallable, BlueprintPure, Category="Item | UFUNCTION" )
	UStaticMeshComponent* GetMeshComponent() { return MeshCmp; }
	UFUNCTION( BlueprintCallable, BlueprintPure, Category="Item | UFUNCTION" )
	FItemSetting& GetItemSetting() { return ItemSetting; }
	UFUNCTION( BlueprintCallable, Category="Item | UFUNCTION" )
	void SetItemSetting( FItemSetting Setting ) { ItemSetting = Setting; }

	void SetupPickMesh();
	void SetupDroppedMesh();

	// 物件被使用或裝備...時要做的事
	virtual void OnUse( ABrunnhildeCharacter* Character ) PURE_VIRTUAL( AItem, );
	virtual void OnEquiped( ABrunnhildeCharacter* Character )  PURE_VIRTUAL( AItem, );
	virtual void OnUnEquiped( ABrunnhildeCharacter* Character )  PURE_VIRTUAL( AItem, );
	virtual void OnDrawn( ABrunnhildeCharacter* Character )  PURE_VIRTUAL( AItem, );
	virtual void OnSheath( ABrunnhildeCharacter* Character )  PURE_VIRTUAL( AItem, );

	virtual void PostEditChangeProperty( struct FPropertyChangedEvent& e ) override;

public: 
	UPROPERTY( EditDefaultsOnly, Category="Profile | ItemSetting" )
	FItemSetting ItemSetting;

	//Component
	UPROPERTY()
	class UInventoryComponent* OwningInventory;
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="Profile | Component", meta=( AllowPrivateAccess="true" ) )
	class USceneComponent* RootCmp = nullptr;
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="Profile | Component", meta=( AllowPrivateAccess="true" ) )
	class UArrowComponent* ArrowCmp = nullptr;
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="Profile | Component", meta=( AllowPrivateAccess="true" ) )
	class UStaticMeshComponent* MeshCmp = nullptr;
};
