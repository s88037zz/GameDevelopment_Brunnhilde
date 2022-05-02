// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Actions/DropingTruesureAbility.h"
#include "Characters/BrunnhildeCharacter.h"
#include "Math/UnrealMathUtility.h"
#include "Item/Item.h"
#include "Games/HealthComponent.h"

bool UDropingTruesureAbility::BeginAbility()
{
    return true;
}


void UDropingTruesureAbility::Initialize( ABrunnhildeCharacter* Character )
{
    SetControlCharacter( Character );
    Character->HealthCmp->OnDied.AddDynamic( this, &UDropingTruesureAbility::OnDiead );
}

void UDropingTruesureAbility::OnDiead()
{
    /*
    int i = FMath::RandRange( 0, Treasures.Num()-1 );
    ItemData* Data = Treasures[ i ];

    AItem* Item = GetWorld()->SpawnActor< AItem>( GetControlCharacter()->GetTransform().GetLocation(), 
                                                  GetControlCharacter()->GetTransform().GetRotation().Rotator() );
    */
}