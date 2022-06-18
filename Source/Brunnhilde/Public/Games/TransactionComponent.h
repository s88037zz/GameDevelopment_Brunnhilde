// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TransactionComponent.generated.h"

class AItem;
class ABrunnhildeCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BRUNNHILDE_API UTransactionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTransactionComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION( BlueprintCallable )
	bool AddProductToOwner( AItem* Product );
	UFUNCTION( BlueprintCallable )
	bool RemoveProductFromOwner( AItem* Product );
	UFUNCTION( BlueprintCallable )
	bool Buy( AItem* Product, ABrunnhildeCharacter* ProductOwner );
	UFUNCTION( BlueprintCallable )
	bool IsEnoughToBuy( AItem* Product );

public:
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | Members" )
	int CurCoin = 100;

private:
	bool IsProductBelongTo( ABrunnhildeCharacter* Character, AItem* Product );
};
