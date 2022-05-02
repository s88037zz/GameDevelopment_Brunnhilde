// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Armour.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Characters/BrunnhildeCharacter.h"

// Sets default values
AArmour::AArmour()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	RootComponent = CreateDefaultSubobject<USceneComponent>( TEXT( "Root" ) );
	
	ArrowCmp = CreateDefaultSubobject< UArrowComponent >( TEXT( "Arrow " ) );
	ArrowCmp->SetArrowColor( FLinearColor::Blue );
	ArrowCmp->AttachToComponent( RootCmp, FAttachmentTransformRules::KeepRelativeTransform );

	MeshCmp = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "WeaponMesh" ) );
	MeshCmp->AttachToComponent( RootCmp, FAttachmentTransformRules::KeepRelativeTransform );
	MeshCmp->SetCollisionEnabled( ECollisionEnabled::NoCollision );
}

void AArmour::OnUse( ABrunnhildeCharacter* Character )
{
	if ( Character )
	{
	}
}

void AArmour::OnEquiped( ABrunnhildeCharacter* Character )
{
	if ( Character )
	{
		MeshCmp->AttachToComponent( Character->GetMesh(),
									 FAttachmentTransformRules::SnapToTargetIncludingScale, 
									 FName( *AttachSocket ) );
		SetOwner( Character );
	}
}

void AArmour::OnUnEquiped( ABrunnhildeCharacter* Character )
{
	FDetachmentTransformRules Rule = FDetachmentTransformRules::KeepWorldTransform;
	DetachFromActor( Rule );
	SetOwner( nullptr );
}