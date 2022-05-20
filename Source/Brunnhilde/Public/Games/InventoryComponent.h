// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Games/BrunnhildeDef.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnInventoryUpdated );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnEquipmentUpdated );

class AItem;
class AWeapon;
class ABrunnhildeCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BRUNNHILDE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent() = default;
	// Sets default values for this component's properties
	UInventoryComponent( ABrunnhildeCharacter* Owner );


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UFUNCTION( BlueprintCallable )
	TMap< EItemTypes, AItem* > GetEquipments() { return EquipedEquipments; }
	
	UFUNCTION( BlueprintCallable )
	bool AddItem( AItem* Item );
	UFUNCTION( BlueprintCallable )
	bool RemoveItem( AItem* Item );
	UFUNCTION( BlueprintCallable )
	bool UseItem( AItem* Item );

	UFUNCTION( BlueprintCallable )
	bool EquipItem( AItem* Item );
	UFUNCTION( BlueprintCallable )
	bool UnEquipItem( EItemTypes EquipmentType );
	UFUNCTION( BlueprintCallable )
	bool IsWeaponEquiped();

	UFUNCTION( BlueprintCallable )
	AWeapon* GetEquipedWeapon( EItemTypes eWeaponType = EItemTypes::EIT_WEAPON );
	UFUNCTION( BlueprintCallable )
	AItem* GetEquipmentByType( EItemTypes eType );

public:
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Inventory" )
	int32 Capacity = 20;

	UPROPERTY( BlueprintAssignable, Category="Invetory" )
	FOnInventoryUpdated OnInventoryUpdated;

	UPROPERTY( BlueprintAssignable, Category="Inventory" )
	FOnEquipmentUpdated OnEquipmentUpdated;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="Inventory" )
	TArray< AItem* > Items;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Instanced, Category="Inventory" )
	TArray< AItem* > DefaultItems;
	
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="Inventory" )
	TMap< EItemTypes, AItem* > EquipedEquipments;
};
