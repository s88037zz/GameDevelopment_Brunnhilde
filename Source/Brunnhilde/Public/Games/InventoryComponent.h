// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UBrunnhildeDef;

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
	void AddArmour( AActor* pArmour );

	UFUNCTION( BlueprintCallable )
	void RemoveArmour( AActor* pArmour );

	UFUNCTION( BlueprintCallable )
	void EquipArmour( AActor* pArmour, FString strArmourType );

	UFUNCTION( BlueprintCallable )
	void UnEquipArmour( FString strArmourType );

	UFUNCTION( BlueprintCallable )
	AActor* GetEquipmentByType( FString strArmourType );
	
	UFUNCTION( BlueprintCallable )
	void GetAllEquipmentCompetency( TMap< FString, int >& kEquipmentQualityMap );

public:
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Inventory | Inventory", DisplayName="Armour Iventory" )
	TArray< AActor* > m_kArmourIventory;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Inventory | Equiped", DisplayName="Equiped Armours" )
	TMap< FString, AActor* > m_kEquipedArmours;		

private:
	UBrunnhildeDef* m_kBrunnhildeDef = nullptr;
	
};
