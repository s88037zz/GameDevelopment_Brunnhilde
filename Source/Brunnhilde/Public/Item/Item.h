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
UCLASS( Abstract, BlueprintType, Blueprintable, DefaultToInstanced )
class BRUNNHILDE_API AItem : public AActor
{
	GENERATED_BODY()

public:
	AItem();

	UFUNCTION( BlueprintCallable, Category="Item | UFUNCTION" )
	UStaticMeshComponent* GetMeshComponent() { return MeshCmp; }

	// 物件被使用或裝備...時要做的事
	virtual void OnUse( ABrunnhildeCharacter* Character ) PURE_VIRTUAL( AItem, );
	virtual void OnEquiped( ABrunnhildeCharacter* Character )  PURE_VIRTUAL( AItem, );
	virtual void OnUnEquiped( ABrunnhildeCharacter* Character )  PURE_VIRTUAL( AItem, );
	virtual void OnDrawn( ABrunnhildeCharacter* Character )  PURE_VIRTUAL( AItem, );
	virtual void OnSheath( ABrunnhildeCharacter* Character )  PURE_VIRTUAL( AItem, );

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
	FString AttachSocket;

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
