// Fill out your copyright notice in the Description page of Project Settings.


#include "Games/EnduranceComponent.h"

// Sets default values for this component's properties
UEnduranceComponent::UEnduranceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	CurrentEndurance = MaxEndurance;

}


// Called when the game starts
void UEnduranceComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	GetWorld()->GetTimerManager().SetTimer( RecoveringTimer, [this]()
	{
		float RecoverValue = MaxEndurance * RecoverPercent / 100;
		Recover( RecoverValue );
	}, 0.05, true );
}


// Called every frame
void UEnduranceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UEnduranceComponent::Reduce( float Value )
{
	StopRecover();

	if ( CurrentEndurance - Value < 0 )
	{
		CurrentEndurance = 0;
	}
	else
	{
		CurrentEndurance -= Value;
	}
	
	GetWorld()->GetTimerManager().SetTimer( WaitToRecoveryTimer, [ this ]()
	{
		StartRecover();
	}, WaitToRecoverTime, false );



	OnEnduranceChanged.Broadcast( CurrentEndurance );
	
	return CurrentEndurance;
}

float UEnduranceComponent::Recover( float Value )
{
	if ( CurrentEndurance + Value > MaxEndurance )
	{
		CurrentEndurance = MaxEndurance;
	}
	else
	{
		CurrentEndurance += Value;
	}

	OnEnduranceChanged.Broadcast( CurrentEndurance );

	return CurrentEndurance;
}

float UEnduranceComponent::GetCurrentEndurance()
{
	return CurrentEndurance;
}

void UEnduranceComponent::StartRecover()
{

	GetWorld()->GetTimerManager().SetTimer( RecoveringTimer, [this]()
	{
		float RecoverValue = MaxEndurance * RecoverPercent / 100;
		Recover( RecoverValue );
	}, 0.05, true );

}

void UEnduranceComponent::StopRecover()
{
	GetWorld()->GetTimerManager().ClearTimer( RecoveringTimer );
}

bool UEnduranceComponent::IsTired()
{
	return CurrentEndurance <= 0;
}

