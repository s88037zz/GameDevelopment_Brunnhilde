// Fill out your copyright notice in the Description page of Project Settings.


#include "Armour.h"
#include "..\..\Public\Armours\Armour.h"

// Sets default values
AArmour::AArmour()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AArmour::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArmour::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int AArmour::GetCompetencyValueByType( FString strCompetencyType )
{
	return 0;
}

