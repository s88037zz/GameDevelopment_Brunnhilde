// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnduranceComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnEnduranceChanged, int, Endurance );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnTired );

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BRUNNHILDE_API UEnduranceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnduranceComponent();

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Abilities" )
	float MaxEndurance = 100.f;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Abilities" )
	float RecoverPercent = 2.f;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Abilities" )
	float WaitToRecoverTime = 1.5f;

	UPROPERTY( BlueprintAssignable, Category="Abilities" )
	FOnEnduranceChanged OnEnduranceChanged; 

	UPROPERTY( BlueprintAssignable, Category="Abilities" )
	FOnTired OnTired;

public:
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
	
	UFUNCTION( BlueprintCallable, Category="Abilities" )
	float Reduce( float Value );

	UFUNCTION( BlueprintCallable, Category="Abilities" )
	float Recover( float Value );

	UFUNCTION( BlueprintPure, Category="Abilities" )
	float GetCurrentEndurance();

	UFUNCTION( BlueprintCallable, Category="Abiliites" )
	void StartRecover();
	
	UFUNCTION( BlueprintCallable, Category="Abilities" )
	void StopRecover();

	UFUNCTION( BlueprintPure, Category="Abilities" )
	bool IsTired();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float CurrentEndurance;
	
	FTimerHandle WaitToRecoveryTimer;
	FTimerHandle RecoveringTimer;
};
