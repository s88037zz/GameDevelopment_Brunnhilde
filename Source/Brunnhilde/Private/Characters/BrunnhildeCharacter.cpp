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

#include "Components/SkeletalMeshComponent.h"
#include "Animation\AnimNode_StateMachine.h"
#include "HealthComponent.h"
#include "EnduranceComponent.h"
#include "Animation/AnimInstance.h"
#include "InventoryComponent.h"
#include "Weapon.h"
#include "Item.h"
#include "Armour.h"
#include "ItemData/ArmourData.h"

# define BlockingAttack "BlockingAttack_Start"
# define ActiveMotionSlot "ActiveMotionSlot"



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
	HealthCmp->OnDied.AddDynamic( this, &ABrunnhildeCharacter::Dead );

	//* Endurance Component Setting*/
	EnduranceCmp = CreateDefaultSubobject< UEnduranceComponent >( TEXT( "Endurance") );
	EnduranceCmp->MaxEndurance = Endurance * 5;

    ObjectDroppedLocation = CreateDefaultSubobject<USceneComponent>( TEXT( "ObjectDroppedLocation" ) );
	ObjectDroppedLocation->AttachToComponent( GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform );

	NormalAttackAbility = CreateDefaultSubobject< UNormalAttackAbility >( TEXT( "NormalAttackAbility" ) );
	NormalAttackAbility->Initialize( this );
		 
	MeleeAttackAbility = CreateDefaultSubobject< UMeleeAttackAbility >( TEXT( "MeleeAttackAbility" ) );
	MeleeAttackAbility->Initialize( this );

	FlinchAbility = CreateDefaultSubobject< UFlinchAbility2 >( TEXT( "FlinchAbility" ) );
	FlinchAbility->SetControlCharacter( this );
	OnTakeAnyDamage.AddDynamic( FlinchAbility, &UFlinchAbility2::OnTakeDamaged );

	SprintAbility = CreateDefaultSubobject< USprintAbility2 >( TEXT( "SprintAblity" ) );
	SprintAbility->SetControlCharacter( this );

	PickUpItemAbility = CreateDefaultSubobject< UPickUpItemAbility >( TEXT( "PickUpItemAbility" ) );
	PickUpItemAbility->SetControlCharacter( this );

	DrawnNSheathAbility = CreateDefaultSubobject< UDrawnNSheathAbility >( TEXT( "DrawnNSheathAbility" ) );
	DrawnNSheathAbility->SetControlCharacter( this );

	Inventory = CreateDefaultSubobject< UInventoryComponent >( TEXT( "Inventory" ) );
	Inventory->Capacity = 15.f;
	Inventory->OnEquipmentUpdated.AddDynamic( this, &ABrunnhildeCharacter::HandleEquipmentUpdated );

	EquippedWeapon = nullptr;
	bReadyToAttack = false;
	bAttacking = false;
	bSaveAttack = false;
	bFlinching =false;
}


//////////////////////////////////////////////////////////////////////////
void ABrunnhildeCharacter::PickupWeapon()
{
	if ( IsValid( PickUpItemAbility ) )
	{
		PickUpItemAbility->PickUp();
	}
}

void ABrunnhildeCharacter::DrawnWeapon()
{
	if ( IsValid( DrawnNSheathAbility ) )
	{
		DrawnNSheathAbility->Drawn();
	}
}

void ABrunnhildeCharacter::SheathWeapon()
{
	if ( IsValid( DrawnNSheathAbility ) )
	{
		DrawnNSheathAbility->Sheath();
	}
}

void ABrunnhildeCharacter::LightAttack()
{	
	if ( !IsDrwanWeapon() && 
		 !GetCharacterMovement()->IsFalling() )
	{
		DrawnWeapon();
		return;
	}

	if ( bReadyToAttack && IsValid( NormalAttackAbility ) )
	{
		DrawnNSheathAbility->ResetIdle2SheathCounter();
		NormalAttackAbility->HandleAttackInput02();
	}
}

void ABrunnhildeCharacter::MeleeAttack()
{
	if ( !IsDrwanWeapon() &&
		 !GetCharacterMovement()->IsFalling() )
	{
		DrawnWeapon();
		return;
	}

	if ( bReadyToAttack & IsValid( MeleeAttackAbility ) )
	{
		DrawnNSheathAbility->ResetIdle2SheathCounter();
		MeleeAttackAbility->HandleAttackInput02();
	}
}

void ABrunnhildeCharacter::BlockAttack()
{
}

void ABrunnhildeCharacter::LockEnemy()
{
	if( LockEnemyAbility )
	{
		LockEnemyAbility->Lock();
	}
}


void ABrunnhildeCharacter::Dead()
{
    if ( !DeadMontage )
    {
        return;
    }
	if ( HealthCmp->GetCurrentHealth() <= 0 )
	{
		GetCharacterMovement()->DisableMovement();
        float duration = PlayAnimMontage( DeadMontage );

	}
}

void ABrunnhildeCharacter::StartSprint()
{
	SprintAbility->StartSprint();
}

void ABrunnhildeCharacter::StopSprint()
{
	SprintAbility->StopSprint();
}

void ABrunnhildeCharacter::UseItem( AItem* Item )
{
	if ( Item )
	{
		Item->Use( this );
		Item->OnUse( this );
	}
}

void ABrunnhildeCharacter::HandleDrawnWeapon_Notification()
{
	if ( !IsValid( DrawnNSheathAbility ) )
	{
		return;
	}
	if ( EquippedWeapon )
	{	
		EquippedWeapon->AttachToComponent( GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, HoldWeaponSocket );
		DrawnNSheathAbility->bWeaponDrawn = true;
	}
}

void ABrunnhildeCharacter::HandleSheathWeapon_Notification()
{
	if ( !IsValid( DrawnNSheathAbility ) )
	{
		return;
	}

	if ( EquippedWeapon )
	{
		EquippedWeapon->AttachToComponent( GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, BackWeaponSocket );
		DrawnNSheathAbility->bWeaponDrawn = false;
	}
}


//////////////////////////////////////////////////////////////////////////
// Input

void ABrunnhildeCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
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
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ABrunnhildeCharacter::OnResetVR);
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

	if( IsValid( LockEnemyClass ) )
	{
		LockEnemyAbility = NewObject<ULockEnemyAbility>( this, LockEnemyClass );
		check( LockEnemyAbility );

		LockEnemyAbility->Initialize( this );
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


//Getter 

bool ABrunnhildeCharacter::IsDrwanWeapon()
{
	if ( IsValid( DrawnNSheathAbility ) )
	{
		return DrawnNSheathAbility->bWeaponDrawn;
	}
	return false;
}

bool ABrunnhildeCharacter::IsReadyToAttack()
{
	return bReadyToAttack;
}

bool ABrunnhildeCharacter::IsAttacking()
{
	return bAttacking;
}

bool ABrunnhildeCharacter::IsSaveAttack()
{
	return bSaveAttack;
}

bool ABrunnhildeCharacter::IsFlinching()
{
	return bFlinching;
}

bool ABrunnhildeCharacter::IsLockedEnemy()
{
	return bIsLockedEnemy;
}

AWeapon* ABrunnhildeCharacter::GetEquippedWeapon()
{
	return EquippedWeapon;
}

// Setter
AWeapon* ABrunnhildeCharacter::SetEquippedWeapon( AWeapon* NewWeapon )
{
	if ( Cast< AWeapon >( NewWeapon ) && NewWeapon != EquippedWeapon )
	{
		AWeapon* Weapon = Cast< AWeapon >( NewWeapon );

		if ( EquippedWeapon )
		{
			EquippedWeapon->HandleDrop();
		}

		UMeshComponent* WeaponMesh = Weapon->GetMeshComponent();
		if ( WeaponMesh->IsSimulatingPhysics() )
		{
			Weapon = Weapon->HandlePickupByCopy();
		}
		else
		{
			Weapon->HandlePickup(this);
		}

		EquippedWeapon = Weapon;

		if ( !WeaponInventory.Contains( Weapon ) )
		{
			WeaponInventory.Add( Weapon );
		}

	}
    return EquippedWeapon;
}

void ABrunnhildeCharacter::SetAttacking( bool bAttack )
{
	bAttacking = bAttack;
}

void ABrunnhildeCharacter::SetReadyToAttack( bool bStatus )
{
	bReadyToAttack = bStatus;
}

void ABrunnhildeCharacter::SetSaveAttack( bool bInputAttack )
{
	bSaveAttack = bInputAttack;
}

void ABrunnhildeCharacter::SetIsFlinching( bool bFlinch )
{
	bFlinching = bFlinch;
}

void ABrunnhildeCharacter::SetActiveAbility( UAbility2* ActiveAbility )
{
	CurrentActiveAbility = ActiveAbility;
}

void ABrunnhildeCharacter::SetLockedEnemy( bool Locked )
{
	bIsLockedEnemy = Locked;
}

void ABrunnhildeCharacter::HandleEquipmentUpdated()
{
	ResetStatsToDefault();

	for ( auto& Equpiment : Inventory->GetEquipment() )
	{	
		AArmour* Armour = Cast< AArmour >( Equpiment.Value );
		if (  IsValid( Armour ) )
		{
			Constitution += Armour->ArmourData->Constitution;
			Mentality += Armour->ArmourData->Mentality;
			Endurance += Armour->ArmourData->Endurance;
			Strength += Armour->ArmourData->Strength;
			Dexterity += Armour->ArmourData->Dexterity;
			Intelligence += Armour->ArmourData->Intelligence;
			Wisdom += Armour->ArmourData->Wisdom;
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
