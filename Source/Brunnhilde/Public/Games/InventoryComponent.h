// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

UENUM()
enum class EArmourType : int8
{
	Head = 0,
	Chest,
	Hand,
	Feet
};

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
	void GetAllEquipmentCompetency( TMap< FString, int > kEquipmentQualityMap );

public:
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category="Inventory | CompetencyTypes", DisplayName="Competency Types" )
	TArray< FString > m_kCompetencyTypes = { "Constitution", "Mentality", "Endurance", "Strength",
											"Dexterity", "Intelligence", "Wisdom" };

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category="Inventory | ArmourTypes", DisplayName="Armour Types" )
	TArray< FString > m_kArmourTypes = { "Head", "Chest", "Hand", "Feet" };

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Inventory | Inventory", DisplayName="Armour Iventory" )
	TArray< AActor* > m_kArmourIventory;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Inventory | Equiped", DisplayName="Equiped Armours" )
	TMap< FString, AActor* > m_kEquipedArmours;		
};
