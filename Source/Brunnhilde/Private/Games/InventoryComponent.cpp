// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/InventoryComponent.h"
#include "Weapons/AArmour.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Init
	m_kEquipedArmours.Reserve( 4 );
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// ...
}

void UInventoryComponent::AddArmour( AActor* pArmour )
{
	m_kArmourIventory.Add( pArmour );
}

void UInventoryComponent::RemoveArmour( AActor* pArmour )
{
	int32 iIndex = -1;
	if ( m_kArmourIventory.Find( pArmour )  >= 0 )
	{
		m_kArmourIventory.RemoveAt( iIndex );
	}
}

void UInventoryComponent::EquipArmour( AActor* pArmour, FString strArmourType )
{
	if ( m_kEquipedArmours.FindChecked( strArmourType ) )
	{
		m_kEquipedArmours[ strArmourType ] = pArmour;
	}
	else
	{
		m_kEquipedArmours.Add( strArmourType, pArmour );
	}
}

void UInventoryComponent::UnEquipArmour( FString strArmourType )
{
	if ( m_kEquipedArmours.FindChecked( strArmourType ) )
	{
		m_kEquipedArmours[ strArmourType ] = nullptr;
	}
}

AActor* UInventoryComponent::GetEquipmentByType( FString strArmourType )
{
	return m_kEquipedArmours[ strArmourType ];
}

void UInventoryComponent::GetAllEquipmentCompetency( TMap< FString, int > kEquipmentQualityMap )
{
	auto AddValueToMap = [&]()
	{
		for ( const FString& strCompetencyName : m_kCompetencyTypes )
		{

		}
	};

	for ( const FString& strArmourType : m_kArmourTypes )
	{

	}
}

