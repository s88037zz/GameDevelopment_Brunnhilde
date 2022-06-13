// Fill out your copyright notice in the Description page of Project Settings.


#include "Games/ColorChannel.h"
#include "Characters/BrunnhildeCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AColorChannel::AColorChannel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//RootCmp = CreateDefaultSubobject< USceneComponent >( TEXT( "Root" ) );
	RootComponent = CreateDefaultSubobject< USceneComponent >( TEXT( "Root" ) );

	SpawnedDefenderRefCmp = CreateDefaultSubobject< UCapsuleComponent >( TEXT( "SpawnedDefenderRef" ) );
	SpawnedDefenderRefCmp->AttachToComponent( GetRootComponent(),
											  FAttachmentTransformRules::KeepRelativeTransform, NAME_None );
}

// Called when the game starts or when spawned
void AColorChannel::BeginPlay()
{
	AActor::BeginPlay();
	AttachToComponent( GetPlayer()->GetRootComponent(),
					   FAttachmentTransformRules::SnapToTargetNotIncludingScale, NAME_None );

}

// Called every frame
void AColorChannel::Tick( float DeltaTime )
{
	AActor::Tick(DeltaTime);
	if ( CurState == EChannelControlState::SetupEndLocation )
	{
		SetupPreviewDefenders();
	}
	if( CurState == EChannelControlState::SetupSurface )
	{
		SetupSurface( SurfaceMeshCmp );
		ChangeToState( EChannelControlState::DrawSurface );
	}

	if ( CurState == EChannelControlState::DrawSurface )
	{
		UpdateSurfaceScale( DeltaTime );
	}

}

bool AColorChannel::OnUse()
{
	switch ( CurState )
	{
		case EChannelControlState::ChooseStartLocation:
			verify( InitailizePoint( StartPointCmp ) );

			ChangeToState( EChannelControlState::SetupStartLocation );
			break;
		case EChannelControlState::SetupStartLocation:
			verify( SetupStartPoint() );

			ChangeToState( EChannelControlState::ChooseEndLocation );
			break;
		case EChannelControlState::ChooseEndLocation:
			verify( InitailizePoint( EndPointCmp ) );
			verify( SetupDefenderBounds() );
			ChangeToState( EChannelControlState::SetupEndLocation );
			break;
		case EChannelControlState::SetupEndLocation:
			verify( SetupEndPoint() );
			verify( ShiftPreviewToReal() );

			ChangeToState( EChannelControlState::SetupSurface );
			break;
		default:
			return FAIL;
			break;
	}
	return OK;
}

bool AColorChannel::SetupPreviewDefenders()
{
	//Let root face to 
	FVector StartLocation = StartPointCmp->GetComponentLocation();
	FVector EndLocation   = EndPointCmp->GetComponentLocation();

	float Dist = FVector::Dist2D( StartLocation, EndLocation );
	FVector UnitVector = ( EndLocation - StartLocation ) / Dist;
	int Quantity = ComputeDefendersQuantity();

	if ( Quantity > PreviewDefenders.Num() )
	{
		for( size_t i = 0; i < Quantity-PreviewDefenders.Num(); ++i )
		{
			SetupPreviewDefender();
		}
	}
	else if ( PreviewDefenders.Num() > Quantity )
	{
		for ( int i = PreviewDefenders.Num() - 1; i+1 > Quantity; --i )
		{
			if ( PreviewDefenders.IsValidIndex( i ) )
			{
				GetWorld()->DestroyActor( PreviewDefenders[ i ] );
				PreviewDefenders.RemoveAt( i );
			}
		}
	}

	for ( int i = 0; i < PreviewDefenders.Num(); ++i )
	{
		FVector Location;
		ComputeDefenderLocation( i, Location );
		PreviewDefenders[ i ]->SetActorLocation( Location );
		if ( DefenderFocusActor )
		{
			FRotator Rotator = UKismetMathLibrary::FindLookAtRotation( Location, DefenderFocusActor->GetActorLocation() );
			PreviewDefenders[ i ]->SetActorRotation( Rotator );
		}
	}

	return OK;
}

bool AColorChannel::SetupPreviewDefender()
{
	FRotator Rotator = FRotator::MakeFromEuler( FVector( 0 , 0, 90 ) );
	FActorSpawnParameters Params;
	ABrunnhildeCharacter* Defender = GetWorld()->SpawnActor< ABrunnhildeCharacter >( DefenderBase,
																					 SpawnedDefenderRefCmp->GetComponentLocation(),
																					 GetRootComponent()->GetComponentRotation(),
																					 Params );
	CheckPtrIsValid( Defender );
	PreviewDefenders.Add( Defender );
	return OK;
}

bool AColorChannel::SetupSurface( UStaticMeshComponent*& SurfaceCmp )
{
	CheckPtrIsValid( StartPointCmp );
	CheckPtrIsValid( EndPointCmp );
	CheckPtrIsValid( SurfaceMesh );
	CheckPtrIsValid( SurfaceMaterial );

	SurfaceCmp = NewObject< UStaticMeshComponent >( this );
	SurfaceCmp->RegisterComponent();
	SurfaceCmp->SetStaticMesh( SurfaceMesh );
	
	for ( const auto& MaterailName : SurfaceCmp->GetMaterialSlotNames() )
	{
		SurfaceCmp->SetMaterialByName( MaterailName, SurfaceMaterial );
	}
	/*
	for ( size_t i = 0; i < SurfaceCmp->GetNumMaterials(); ++i )
	{
		SurfaceCmp->GetStaticMesh()->SetMaterial( i, SurfaceMaterial );
	}
	*/
	//setup1. setup scale value
	FVector NewScale;
	FBoxSphereBounds bsBounds = SurfaceCmp->GetStaticMesh()->GetBounds();
	
	FVector MeshSize = bsBounds.BoxExtent - bsBounds.Origin;
	FVector StartLocation = StartPointCmp->GetComponentLocation();
	FVector EndLocation = EndPointCmp->GetComponentLocation();
	
	NewScale.X = SurfaceWidth / MeshSize.X;
	NewScale.Y = SurfaceWidth / MeshSize.Y;
	NewScale.Z = SurfaceHeight / MeshSize.Z;
	SurfaceTargetScale = NewScale;
	SurfaceTargetScale.X = MeshSize.X > 0 ? FMath::Abs( FVector::Dist2D( StartLocation, EndLocation ) ) / ( MeshSize.X * 2 ) : 1;
	
	SurfaceCmp->SetWorldScale3D( NewScale );

	//steop2. face to end point
	
	FRotator Rotate = UKismetMathLibrary::FindLookAtRotation( StartPointCmp->GetComponentLocation(),
															  EndPointCmp->GetComponentLocation() );
	SurfaceCmp->SetWorldRotation( Rotate );
	
	//step3. move to center
	FVector CenterLocatoin = ( StartLocation + EndLocation ) / 2;
	
	
	SurfaceCmp->AttachToComponent( StartPointCmp,
								   FAttachmentTransformRules::KeepWorldTransform, NAME_None );
	
	SurfaceCmp->SetWorldLocation( CenterLocatoin );
	SurfaceCmp->SetHiddenInGame( false );

	return OK;
}

bool AColorChannel::SetupStartPoint()
{
	if ( nullptr == StartPointCmp )
	{ 
		return FAIL;
	}
	StartPointCmp->DetachFromParent( true, false );
	return OK;
}

bool AColorChannel::SetupEndPoint()
{
	if ( nullptr == EndPointCmp )
	{
		return FAIL;
	}
	EndPointCmp->DetachFromParent( true, false );
	return OK;
}

bool AColorChannel::ShiftPreviewToReal()
{
	RealDefenders = PreviewDefenders;
	PreviewDefenders.Empty();
	return OK;
}

bool AColorChannel::ResetChanneLocation()
{
	CheckPtrIsValid( StartPointCmp );
	CheckPtrIsValid( EndPointCmp );
	StartPointCmp->SetWorldLocation( FVector::ZeroVector );
	EndPointCmp->SetWorldLocation( FVector::ZeroVector );
	SurfaceTargetScale = FVector::OneVector;
	StartPointCmp->SetHiddenInGame( true );
	EndPointCmp->SetHiddenInGame( true );
	
	auto CleanDefenders = [&]( TArray< ABrunnhildeCharacter* > Defenders ) -> bool
	{
		for ( auto& Defender : Defenders )
		{
			if ( !IsValid( Defender ) )
			{
				return FAIL;
			}
			GetWorld()->DestroyActor( Defender );
		}
		Defenders.Empty();
		return OK;
	};
	verify( CleanDefenders( RealDefenders ) );
	verify( CleanDefenders( PreviewDefenders ) );

	return OK;
}

void AColorChannel::ChangeToState( EChannelControlState State )
{
	CurState = State;
}

int AColorChannel::ComputeDefendersQuantity()
{
	// Distance of Channel
	float ChannelDistance = FVector::Dist2D( StartPointCmp->GetComponentLocation(),
											 EndPointCmp->GetComponentLocation());

	/*
	FRotator BoundToRigthAngle = UKismetMathLibrary::FindLookAtRotation( ChannelDirection, 
																		 ActorBounds.BoxExtent - ActorBounds.Origin );
	
	float BoundRightLength = FMath::Abs( BoundLength2D * FMath::Cos( BoundToRigthAngle.Yaw ) );
	int Quantity = ChannelDistance / ( BoundRightLength + DefenderInterval );
	*/
	int Quantity = ChannelDistance / ( BoundingVector.X * 2 + DefenderInterval );
	return Quantity;
}

FVector AColorChannel::GetPlayerForwardGoundLocation()
{
	ACharacter* Actor = UGameplayStatics::GetPlayerCharacter( GetWorld(), 0 );
	check( Actor != nullptr );

	ABrunnhildeCharacter* Character = Cast< ABrunnhildeCharacter >( Actor );
	check( Character != nullptr );
	//FVector Location = Character->GetActorLocation() + GetActorForwardVector() * PointOffset;
	FVector Location = Character->GetStandLocation() + \
		Character->GetActorForwardVector() * PointOffset.Y + \
		Character->GetActorRightVector() * PointOffset.X;
	return Location;
}

ABrunnhildeCharacter* AColorChannel::GetPlayer()
{
	ACharacter* Actor = UGameplayStatics::GetPlayerCharacter( GetWorld(), 0 );
	check( Actor != nullptr );

	ABrunnhildeCharacter* Character = Cast< ABrunnhildeCharacter >( Actor );
	return Character == nullptr ? nullptr : Character;
}

bool AColorChannel::UpdateSurfaceScale( float deltaTime )
{
	FVector NewScale = SurfaceMeshCmp->GetComponentScale();
	if ( SurfaceTargetScale.X - NewScale.X <= 0.5 )
	{
		ChangeToState( EChannelControlState::Completed );
	}
	NewScale.X += ( deltaTime / SurfaceScaleTime ) * SurfaceTargetScale.X;
	SurfaceMeshCmp->SetWorldScale3D( NewScale );
	
	return OK;
}

bool AColorChannel::UpdatePreviewDefenders()
{
	for ( size_t i = 0; i < PreviewDefenders.Num(); ++i )
	{
		FVector NewLocation;
		verify( ComputeDefenderLocation( i, NewLocation ) );
		PreviewDefenders[ i ]->SetActorLocation( NewLocation );
	}
	return OK;
}

bool AColorChannel::ComputeDefenderLocation( uint32 Index, FVector& Location )
{
	CheckPtrIsValid( StartPointCmp );
	CheckPtrIsValid( EndPointCmp );

	FVector StartLocation = StartPointCmp->GetComponentLocation();
	FVector EndLocation = EndPointCmp->GetComponentLocation();
	int Quantity = ComputeDefendersQuantity();
	Location = StartLocation\
		+ ( EndLocation - StartLocation ) * Index / Quantity \
		+ ( EndLocation - StartLocation ) * 0.5 / Quantity;// Offset to center
	Location.Z = SpawnedDefenderRefCmp->GetComponentLocation().Z;
	return OK;
}

bool AColorChannel::InitailizePoint( UStaticMeshComponent*& ControlPoint )
{
	if ( IsValid( ControlPoint ) )
	{
		return OK;
	}

	ControlPoint = NewObject< UStaticMeshComponent >( this );
	ControlPoint->RegisterComponent();
	ControlPoint->SetWorldLocation( GetPlayerForwardGoundLocation() );
	ControlPoint->AttachToComponent( GetPlayer()->GetRootComponent(),
									 FAttachmentTransformRules::KeepWorldTransform, NAME_None );
	if ( PointPreviewMesh )
	{
		ControlPoint->SetStaticMesh( PointPreviewMesh );
		ControlPoint->SetHiddenInGame( false );
	}
	return OK;
}

bool AColorChannel::SetupDefenderBounds()
{
	FActorSpawnParameters Params;
	ABrunnhildeCharacter* pReferenceDefender = GetWorld()->SpawnActor< ABrunnhildeCharacter >( DefenderBase,
																							   SpawnedDefenderRefCmp->GetComponentLocation(),
																							   FRotator::ZeroRotator,
																							   Params );
	CheckPtrIsValid( pReferenceDefender );

	FVector ActorBoundLegnth;
	CheckPtrIsValid( pReferenceDefender->GetMesh() );
	FBoxSphereBounds ActorBounds = pReferenceDefender->GetMesh()->SkeletalMesh->GetBounds();
	BoundingVector = ActorBounds.BoxExtent - ActorBounds.Origin;

	SpawnedDefenderRefCmp->SetWorldLocation( pReferenceDefender->GetCapsuleComponent()->GetComponentLocation() );
	GetWorld()->DestroyActor( pReferenceDefender );

	return OK;
}
