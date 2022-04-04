// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UItem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnInventoryUpdated );
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BRUNNHILDE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION( BlueprintCallable )
	bool AddItem( UItem* Item );

	UFUNCTION( BlueprintCallable )
	bool RemoveItem( UItem* Item );

	UFUNCTION( BlueprintCallable )
	bool EquipItem( UItem* Item );
	
	UFUNCTION( BlueprintCallable )
	bool UnEquipItem( EArmourTypes ArmourType );
	
public:
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Inventory" )
	int32 Capacity;

	UPROPERTY( BlueprintAssignable, Category="Invetory" )
	FOnInventoryUpdated OnInventoryUpdated;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="Inventory" )
	TArray< UItem* > Items;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Instanced, Category="Inventory" )
	TArray< UItem* > DefaultItems;
	
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="Inventory" )
	TMap< uint8, UItem* > EquipedItems;
	
	
};
