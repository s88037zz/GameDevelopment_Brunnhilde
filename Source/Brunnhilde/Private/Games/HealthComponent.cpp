// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "BrunnhildeCharacter.h"
#
// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bAutoActivate = true;
	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	StartingHealth = StartingHealth == 0 ? MaxHealth : StartingHealth;
	CurrentHealth = StartingHealth;
	if ( GetOwner() )
	{
		GetOwner()->OnTakeAnyDamage.AddDynamic( this, &UHealthComponent::OnOwnerTakeDamage );
	}
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int UHealthComponent::GetCurrentHealth()
{
	return CurrentHealth;
}

bool UHealthComponent::GetIsDead()
{
	return CurrentHealth <= 0;
}


void UHealthComponent::OnOwnerTakeDamage( AActor* DamagedActor,
						float Damage,
						const class UDamageType* DamageType,
						AController* InstigatedBy,
						AActor* DamageCauser )
{
	CurrentHealth = CurrentHealth - (int)Damage;
	CurrentHealth = FMath::Clamp<int>( CurrentHealth, 0, MaxHealth );
	
	OnHealthChanged.Broadcast( CurrentHealth );
	
	if( GetIsDead() )
	{
		OnDied.Broadcast();
	}
}