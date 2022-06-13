// Fill out your copyright notice in the Description page of Project Settings.


#include "Games/TransactionComponent.h"
#include "Games/InventoryComponent.h"
#include "Item/Item.h"
#include "Characters/BrunnhildeCharacter.h"

// Sets default values for this component's properties
UTransactionComponent::UTransactionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTransactionComponent::BeginPlay()
{
	UActorComponent::BeginPlay();

}


// Called every frame
void UTransactionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	UActorComponent::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UTransactionComponent::AddProductToOwner( AItem* Product )
{
	ABrunnhildeCharacter* OwnCharacter = Cast< ABrunnhildeCharacter >( GetOwner() );
	CheckPtrIsValid( OwnCharacter );

	if ( IsProductBelongTo( OwnCharacter, Product ) )
	{
		return FAIL;
	}
	OwnCharacter->GetInventoryCmp()->AddItem( Product );
	Product->SetOwner( GetOwner() );
	return OK;
}

bool UTransactionComponent::RemoveProductFromOwner( AItem* Product )
{
	ABrunnhildeCharacter* OwnCharacter = Cast< ABrunnhildeCharacter >( GetOwner() );
	CheckPtrIsValid( OwnCharacter );

	if ( IsProductBelongTo( OwnCharacter, Product ) )
	{
		Product->SetOwner( nullptr );
		OwnCharacter->GetInventoryCmp()->RemoveItem( Product );
	}
	return OK;
}

bool UTransactionComponent::Buy( AItem* Product )
{
	CheckPtrIsValid( Product );

	ABrunnhildeCharacter* OwnCharacter = Cast< ABrunnhildeCharacter >( GetOwner() );
	CheckPtrIsValid( OwnCharacter );

	if( !IsProductBelongTo( Trader, Product ) || IsProductBelongTo( OwnCharacter, Product ) )
	{
		return FAIL;
	}

	if ( CurCoin >= Product->GetItemSetting().Price )
	{
		Trader->GetTransactionCmp()->CurCoin += Product->GetItemSetting().Price;
		Trader->GetTransactionCmp()->RemoveProductFromOwner( Product );

		CurCoin -= Product->GetItemSetting().Price;
		AddProductToOwner( Product );
		return OK;
	}
	
	return FAIL;
}

bool UTransactionComponent::IsProductBelongTo( ABrunnhildeCharacter* Character, AItem* Product )
{
	CheckPtrIsValid( Character );
	CheckPtrIsValid( Product );

	if ( Character->GetInventoryCmp() )
	{
		return Character->GetInventoryCmp()->Items.Contains( Product );
	}
	return false;
}

