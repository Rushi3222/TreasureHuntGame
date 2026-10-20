// Copyright Epic Games, Inc. All Rights Reserved.

#include "treasureHuntCharacter.h"
#include "treasureHuntProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AtreasureHuntCharacter

AtreasureHuntCharacter::AtreasureHuntCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	//flashlight code


	// Create flashlight
	FlashLight = CreateDefaultSubobject<USpotLightComponent>(
		TEXT("FlashLight"));

	// Attach to the player's camera
	FlashLight->SetupAttachment(FirstPersonCameraComponent);

	// Position and direction
	FlashLight->SetRelativeLocation(FVector(20.f, 0.f, 0.f));
	FlashLight->SetRelativeRotation(FRotator::ZeroRotator);

	// Light settings
	FlashLight->SetIntensity(5000.0f);
	FlashLight->SetAttenuationRadius(1500.0f);
	FlashLight->SetInnerConeAngle(20.0f);
	FlashLight->SetOuterConeAngle(35.0f);

	// Start OFF
	bFlashLightOn = false;
	FlashLight->SetVisibility(false);

}

void AtreasureHuntCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

//////////////////////////////////////////////////////////////////////////// Input

void AtreasureHuntCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AtreasureHuntCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AtreasureHuntCharacter::Look);

		//intreact
		EnhancedInputComponent->BindAction(IntreactAction, ETriggerEvent::Started, this, &AtreasureHuntCharacter::Intreact);
		
		EnhancedInputComponent->BindAction(
			FlashlightAction,
			ETriggerEvent::Started,
			this,
			&AtreasureHuntCharacter::ToggleFlashLight
		);
		
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}

	
}

void AtreasureHuntCharacter::ToggleFlashLight()
{
	if (FlashLight == nullptr)
	{
		return;
	}

	bFlashLightOn = !bFlashLightOn;

	FlashLight->SetVisibility(bFlashLightOn);

	UE_LOG(
		LogTemp,
		Display,
		TEXT("Flashlight is %s"),
		bFlashLightOn ? TEXT("ON") : TEXT("OFF")
	);
}



void AtreasureHuntCharacter::Intreact()
{
	UE_LOG(LogTemp, Display, TEXT("This is Intreacting"));

	FVector Start = FirstPersonCameraComponent->GetComponentLocation();

	FVector End = Start + (FirstPersonCameraComponent->GetForwardVector() * MaxInteractionDistance);

	DrawDebugLine(GetWorld(), Start, End, FColor::Yellow, false, 5.f);
}


void AtreasureHuntCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AtreasureHuntCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
