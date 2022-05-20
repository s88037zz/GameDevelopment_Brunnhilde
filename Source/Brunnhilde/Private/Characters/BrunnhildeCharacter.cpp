// Copyright Epic Games, Inc. All Rights Reserved.

#include "BrunnhildeCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Components/SkeletalMeshComponent.h"
#include "Animation\AnimNode_StateMachine.h"
#include "HealthComponent.h"
#include "EnduranceComponent.h"
#include "Animation/AnimInstance.h"
#include "InventoryComponent.h"
#include "Item/Weapon.h"
#include "Item/Armour.h"
#include "Characters/State/StateMachine.h"

//////////////////////////////////////////////////////////////////////////
// ABrunnhildeCharacter

ABrunnhildeCharacter::ABrunnhildeCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
	 
	//* Health Component Setting*/
	HealthCmp = CreateDefaultSubobject< UHealthComponent >( TEXT( "Health" ) );
	HealthCmp->MaxHealth = Constitution * 5;

	//* Endurance Component Setting*/
	EnduranceCmp = CreateDefaultSubobject< UEnduranceComponent >( TEXT( "Endurance") );
	EnduranceCmp->MaxEndurance = Endurance * 5;

    ObjectDroppedLocation = CreateDefaultSubobject<USceneComponent>( TEXT( "ObjectDroppedLocation" ) );
	ObjectDroppedLocation->AttachToComponent( GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform );

	Inventory = CreateDefaultSubobject< UInventoryComponent >( TEXT( "Inventory" ) );
	Inventory->Capacity = 15.f;
	Inventory->OnEquipmentUpdated.AddDynamic( this, &ABrunnhildeCharacter::HandleEquipmentUpdated );

}

//////////////////////////////////////////////////////////////////////////

void ABrunnhildeCharacter::Attack()
{
	if( IsValid( StateMachine ) )
	{
		StateMachine->AttackAction();
	}
}

void ABrunnhildeCharacter::PickItem()
{
	if ( IsValid( StateMachine ) )
	{
		StateMachine->PickItemAction();
	}
}

void ABrunnhildeCharacter::Sprint()
{
	if ( IsValid( StateMachine ) )
	{
		StateMachine->SprintAction();
	}
}

void ABrunnhildeCharacter::LockEnemy()
{
	if ( IsValid( StateMachine ) )
	{
		StateMachine->LockEnemyAction();
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void ABrunnhildeCharacter::SetupPlayerInputComponent( class UInputComponent* PlayerInputComponent )
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABrunnhildeCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABrunnhildeCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ABrunnhildeCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ABrunnhildeCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ABrunnhildeCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ABrunnhildeCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction( "ResetVR", IE_Pressed, this, &ABrunnhildeCharacter::OnResetVR);

	PlayerInputComponent->BindAction( "NormalAttack", IE_Pressed,  this, &ABrunnhildeCharacter::Attack );
	PlayerInputComponent->BindAction( "Pickup",       IE_Pressed,  this, &ABrunnhildeCharacter::PickItem );
	PlayerInputComponent->BindAction( "Sprint",       IE_Pressed,  this, &ABrunnhildeCharacter::Sprint );
	PlayerInputComponent->BindAction( "Sprint",       IE_Released, this, &ABrunnhildeCharacter::Sprint );
	PlayerInputComponent->BindAction( "LockEnemy",    IE_Released, this, &ABrunnhildeCharacter::LockEnemy );


}

AWeapon* ABrunnhildeCharacter::GetEquipedWeapon()
{
	return Inventory->IsWeaponEquiped() ? Inventory->GetEquipedWeapon() : nullptr;
}

UStateMachine* ABrunnhildeCharacter::GetStateMachine()
{
	return StateMachine;
}


void ABrunnhildeCharacter::SetMovementTimerHandle( double Duration, bool bEnableMovement = true )
{
	if ( bEnableMovement )
	{
		GetWorld()->GetTimerManager().SetTimer( TimeHandle, [this]()
		{
			GetCharacterMovement()->SetMovementMode( MOVE_Walking );
		}, Duration, false );
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer( TimeHandle, [this]()
		{
			GetCharacterMovement()->DisableMovement();
		}, Duration, false );
	}
}

void ABrunnhildeCharacter::SetRequiredNextMontage( bool Required )
{
	RequiredNextMontage = Required;
}

double ABrunnhildeCharacter::GetMontageLeftTime( UAnimMontage* Montage, USkeletalMeshComponent* OwnerMesh )
{	
	if ( !Montage->IsValidLowLevelFast() )
	{
		return 0;
	}

	if ( !OwnerMesh->IsValidLowLevelFast() )
	{
		return 0;
	}

	if ( OwnerMesh->GetAnimInstance() )
	{
        double Pos = OwnerMesh->GetAnimInstance()->Montage_GetPosition( Montage );
        double Length = Montage->GetSectionLength( 0 );
        double LeftTime = Montage->GetSectionTimeLeftFromPos( Pos );
		return LeftTime;
	}
	return 0;
}

void ABrunnhildeCharacter::BeginPlay()
{
	Super::BeginPlay();
	if ( IsValid( StateMachineClass ) )
	{
		StateMachine = NewObject< UStateMachine >( this, StateMachineClass, "StateMachine" );
		if ( StateMachine )
		{
			StateMachine->RegisterComponent();
			StateMachine->Initialize( this );
			this->AddInstanceComponent( StateMachine );
		}
	} 
}

void ABrunnhildeCharacter::Tick( float DeltaSeconds )
{
	Super::Tick( DeltaSeconds );
}

void ABrunnhildeCharacter::OnResetVR()
{
	// If Brunnhilde is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in Brunnhilde.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ABrunnhildeCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void ABrunnhildeCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void ABrunnhildeCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABrunnhildeCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ABrunnhildeCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);

	}
}

void ABrunnhildeCharacter::MoveRight(float Value)
{	

	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);

	}
}

void ABrunnhildeCharacter::HandleEquipmentUpdated()
{
	ResetStatsToDefault();

	for ( auto& EqupimentPair : Inventory->GetEquipments() )
	{	
		AItem* Equpiment = Cast< AItem >( EqupimentPair.Value );
		if (  IsValid( Equpiment ) )
		{
			Constitution += Equpiment->GetItemSetting().GetCharacterAttibutes().Constitution;
			Mentality += Equpiment->GetItemSetting().GetCharacterAttibutes().Mentality;
			Endurance += Equpiment->GetItemSetting().GetCharacterAttibutes().Endurance;
			Strength += Equpiment->GetItemSetting().GetCharacterAttibutes().Strength;
			Dexterity += Equpiment->GetItemSetting().GetCharacterAttibutes().Dexterity;
			Intelligence += Equpiment->GetItemSetting().GetCharacterAttibutes().Intelligence;
			Wisdom += Equpiment->GetItemSetting().GetCharacterAttibutes().Wisdom;
		}
	}
}

void ABrunnhildeCharacter::ResetStatsToDefault()
{
	Constitution = DefaultConstitution;
	Mentality = DefaultMentality;
	Endurance = DefaultEndurance;
	Strength = DefaultStrength;
	Dexterity = DefaultDexterity;
	Intelligence = DefaultIntelligence;
	Wisdom = DefaultWisdom;
}
