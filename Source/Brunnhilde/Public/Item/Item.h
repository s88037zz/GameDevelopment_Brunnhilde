// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Actor.h"
#include "ItemData/ItemData.h"
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

	virtual void Use( ABrunnhildeCharacter* Character ) PURE_VIRTUAL( AItem, );
	virtual void Equip( ABrunnhildeCharacter* Character, FString AttachSocket ) PURE_VIRTUAL( AItem, );
	virtual void UnEquip() PURE_VIRTUAL( AItem, );

	UFUNCTION( BlueprintImplementableEvent, Category="Weapon | UFUNCTION" )
	void OnEquiped();
	UFUNCTION( BlueprintImplementableEvent, Category="Weapon | UFUNCTION" )
	void OnUnEquiped();

public: 
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Item | UPROPERTY" )
	FText UseActionText;

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Item | UPROPERTY" )
	class UStaticMesh* PickupMesh;

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Item | UPROPERTY" )
	class UTexture2D* Thumnail;

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Item | UPROPERTY" )
	FText ItemDisplayName;

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Item | UPROPERTY", meta=( MultiLine=true ) )
	FText ItemDiscription;

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Item | UPROPERTY", meta=( Clamp=0.0 ) )
	float Weight;

	UPROPERTY()
	class UInventoryComponent* OwningInventory;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="Item | UPROPERTY", meta=( AllowPrivateAccess="true" ) )
	class USceneComponent* RootCmp = nullptr;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="Item | UPROPERTY", meta=( AllowPrivateAccess="true" ) )
	class UArrowComponent* ArrowCmp = nullptr;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="Item | UPROPERTY", meta=( AllowPrivateAccess="true" ) )
	class UStaticMeshComponent* MeshCmp = nullptr;
};
