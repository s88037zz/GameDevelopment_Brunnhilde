// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Actions/DropingTreasureAbility.h"
#include "Characters/BrunnhildeCharacter.h"
#include "Math/UnrealMathUtility.h"
#include "Item/Item.h"
#include "Games/HealthComponent.h"


UDropingTreasureAbility::UDropingTreasureAbility(): UAbility2()
{

}

bool UDropingTreasureAbility::BeginAbility()
{
    return true;
}


void UDropingTreasureAbility::Initialize( ABrunnhildeCharacter* Character )
{
    SetControlCharacter( Character );
    Character->HealthCmp->OnDied.AddDynamic( this, &UDropingTreasureAbility::OnDiead );
    Character->AddInstanceComponent( this );
    RegisterComponent();
}

void UDropingTreasureAbility::OnDiead()
{
    if ( Treasures.Num() <= 0 )
    {
        return;
    }


    ABrunnhildeCharacter* Character = GetControlCharacter();
    int i = FMath::RandRange( 0, Treasures.Num() - 1 );
    AItem* Item = Treasures[ i ]->DeepCopy();
    Item->SetupDroppedMesh();
    Item->SetActorTransform( Character->GetTransform() );
}