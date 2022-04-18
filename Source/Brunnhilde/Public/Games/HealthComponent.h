// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class AActor;
class AController;
class UDamageType;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnHealthChanged, int, Health );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnDied );

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BRUNNHILDE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();
	
	UPROPERTY( EditAnyWhere, BlueprintReadWrite, Category="Abilities")
	int MaxHealth = 100;

    UPROPERTY( EditAnyWhere, BlueprintReadWrite, Category="Abilities" )
    int StartingHealth = 100;

    UPROPERTY( BlueprintAssignable, Category="Abilities" )
	FOnHealthChanged OnHealthChanged;

    UPROPERTY( BlueprintAssignable, Category="Abilities" )
	FOnDied OnDied;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION( BlueprintPure, Category="Abilities" )
    int GetCurrentHealth();

	UFUNCTION( BlueprintPure, Category="Abilities" )
	bool GetIsDead();

	UFUNCTION()
    void OnOwnerTakeDamage( AActor* DamagedActor,
                            float Damage,
                            const class UDamageType* DamageType,
                            AController* InstigatedBy,
                            AActor* DamageCauser );
private:
    int CurrentHealth;

};
