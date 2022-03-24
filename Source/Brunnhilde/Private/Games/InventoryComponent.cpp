// Fill out your copyright notice in the Description page of Project Settings.


#include "Games/InventoryComponent.h"
#include "Games/BrunnhildeDef.h"
#include "Armours/Armour.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Init
	m_kEquipedArmours.Reserve( 4 );
	m_kBrunnhildeDef = NewObject< UBrunnhildeDef >();
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
	if ( m_kEquipedArmours.Contains( strArmourType ) )
	{
		return m_kEquipedArmours[ strArmourType ];
	}
	return nullptr;
}

void UInventoryComponent::GetAllEquipmentCompetency( TMap< FString, int >& kEquipmentQualityMap )
{
	auto ResetMap = [&]( TMap< FString, int >& kEquipmentQualityMap )
	{
		for ( FString& strCompetencyType : m_kBrunnhildeDef->CompetencyTypes )
		{
			if ( kEquipmentQualityMap.Contains( strCompetencyType ) )
			{
				kEquipmentQualityMap[ strCompetencyType ] = 0;
			}
			else
			{
				kEquipmentQualityMap.Add( strCompetencyType, 0 );
			}
		}
	};

	auto AddValueToMap = [&]( AArmour* pArmour, TMap< FString, int >& kEquipmentQualityMap )
	{
		if ( !IsValid( pArmour ) )
		{
			return;
		}

		for ( FString& strType : m_kBrunnhildeDef->CompetencyTypes )
		{
			int Value = pArmour->GetCompetencyValueByType( strType );
			if ( kEquipmentQualityMap.Contains( strType ) )
			{
				kEquipmentQualityMap[ strType ] += Value;
			}
			else
			{
				kEquipmentQualityMap.Add( strType, Value );

			}
		}
	};

	ResetMap( kEquipmentQualityMap );
	for ( auto& kArmourItem : m_kEquipedArmours )
	{
		AArmour* pArmour = Cast< AArmour >( kArmourItem.Value );
		AddValueToMap( pArmour, kEquipmentQualityMap );
	}
}

