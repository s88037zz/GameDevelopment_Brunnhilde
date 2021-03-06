// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Games/BrunnhildeDef.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnInventoryUpdated );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnEquipmentUpdated );

class UItemData;
class ABrunnhildeCharacter;
class AActor;

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
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION( BlueprintCallable )
	TMap< EItemTypes, UItemData* > GetEquipments() { return EquipedEquipments; }
	
	UFUNCTION( BlueprintCallable )
	bool AddItem( UItemData* Item );
	UFUNCTION( BlueprintCallable )
	bool RemoveItem( UItemData* Item );
	UFUNCTION( BlueprintCallable )
	bool UseItem( UItemData* Item );

	UFUNCTION( BlueprintCallable )
	bool EquipItem( UItemData* Item );
	UFUNCTION( BlueprintCallable )
	bool UnEquipItem( EItemTypes EquipmentType );
	UFUNCTION( BlueprintCallable )
	bool IsWeaponEquiped();

	UFUNCTION( BlueprintCallable )
	UItemData* GetEquipedWeapon( EItemTypes WeaponType = EItemTypes::EIT_WEAPON );

public:
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Inventory" )
	int32 Capacity = 20;

	UPROPERTY( BlueprintAssignable, Category="Invetory" )
	FOnInventoryUpdated OnInventoryUpdated;

	UPROPERTY( BlueprintAssignable, Category="Inventory" )
	FOnEquipmentUpdated OnEquipmentUpdated;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="Inventory" )
	TArray< UItemData* > Items;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Instanced, Category="Inventory" )
	TArray< UItemData* > DefaultItems;
	
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="Inventory" )
	TMap< EItemTypes, UItemData* > EquipedEquipments;
};
