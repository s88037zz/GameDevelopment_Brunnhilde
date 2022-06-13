// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Games/BrunnhildeDef.h"
#include "ColorChannel.generated.h"

class ABrunnhildeCharacter;
class UTexture2D;
class UCapsuleComponent;

UENUM( BlueprintType )
enum class EChannelControlState : uint8
{
	ChooseStartLocation,
	SetupStartLocation,
	ChooseEndLocation,
	SetupEndLocation,
	SetupSurface,
	DrawSurface,
	Completed
};

UCLASS( Blueprintable )
class BRUNNHILDE_API AColorChannel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AColorChannel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick( float DeltaTime ) override;

	UFUNCTION( BlueprintCallable )
	bool OnUse();
	UFUNCTION( BlueprintCallable )
	void ChangeToState( EChannelControlState State );
	UFUNCTION( BlueprintCallable )
	bool ResetChanneLocation();

	UFUNCTION( BlueprintCallable )
	int ComputeDefendersQuantity();
	UFUNCTION( BlueprintCallable )
	const EChannelControlState GetState() const { return CurState; }
	UFUNCTION( BlueprintCallable )
	FVector GetPlayerForwardGoundLocation();
public:	
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | Points" )
	/*Setting PointPreviewMesh spawned position*/
	FVector2D PointOffset = FVector2D( 20, 20 );
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | Defenders" )
	/*Interval of two Defender */
	int DefenderInterval = 100;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | Surface" )
	/* Width of Surface( Local Y )*/
	float SurfaceWidth = 1.0f;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | Surface" )
	/* Height of Surface( Local Z )*/
	float SurfaceHeight = 1.0f;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | Surface" )
	/* Time of Surface Spawned */
	float SurfaceScaleTime = 1.0;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | Surface" )
	UMaterial* SurfaceMaterial;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | Surface" )
	UStaticMesh* SurfaceMesh;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | Points" )
	UStaticMesh* PointPreviewMesh;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Profile | Defenders" )
	TSubclassOf< ABrunnhildeCharacter > DefenderBase;
	UPROPERTY( VisibleAnyWhere, BlueprintReadWrite, Category="Profile | Points" )
	UStaticMeshComponent* StartPointCmp;
	UPROPERTY( VisibleAnyWhere, BlueprintReadWrite, Category="Profile | Points" )
	UStaticMeshComponent* EndPointCmp;
	UPROPERTY( VisibleAnyWhere, BlueprintReadWrite, Category="Profile | Surface" )
	UStaticMeshComponent* SurfaceMeshCmp;
	UPROPERTY( VisibleAnyWhere, BlueprintReadWrite, Category="Profile | Others" )
	FVector BoundingVector;
	UPROPERTY( VisibleAnyWhere, BlueprintReadWrite, Category="Profile | Defenders" )
	/* Defender focus point after spawnd in viewport.*/
	AActor* DefenderFocusActor;
	UPROPERTY( VisibleAnyWhere, BlueprintReadWrite, Category="Profile | Defenders" )
	UCapsuleComponent* SpawnedDefenderRefCmp;
private:
	UFUNCTION()
	bool SetupPreviewDefenders();
	UFUNCTION()
	bool SetupPreviewDefender();
	UFUNCTION()
	bool ShiftPreviewToReal();
	UFUNCTION()
	bool SetupSurface( UStaticMeshComponent*& SurfaceCmp );
	UFUNCTION()
	bool SetupStartPoint();
	UFUNCTION()
	bool SetupEndPoint();

	UFUNCTION()
	ABrunnhildeCharacter* GetPlayer();
	UFUNCTION()
	bool UpdateSurfaceScale( float deltaTime );
	UFUNCTION()
	bool UpdatePreviewDefenders();
	UFUNCTION()
	bool ComputeDefenderLocation( uint32 Index, FVector& Location );
	UFUNCTION()
	bool InitailizePoint( UStaticMeshComponent*& ControlPoint );
	UFUNCTION()
	bool SetupDefenderBounds();
private:
	TArray< ABrunnhildeCharacter* > RealDefenders;
	TArray< ABrunnhildeCharacter* > PreviewDefenders;
	EChannelControlState CurState = EChannelControlState::ChooseStartLocation;
	FVector SurfaceTargetScale = FVector::OneVector;
};
