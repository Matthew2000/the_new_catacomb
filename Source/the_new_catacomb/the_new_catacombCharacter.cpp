// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "the_new_catacombCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"

// defines macros for printing text to the screen
#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(text), fstring))

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// Athe_new_catacombCharacter

Athe_new_catacombCharacter::Athe_new_catacombCharacter()
{

	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
}

void Athe_new_catacombCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

void Athe_new_catacombCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	Stamina -= StaminaDecrement * DeltaSeconds;
	if (!InLight) {
		Sanity -= SanityDecrement * DeltaSeconds;
	}
	if (InLight) {
		Sanity += SanityIncrement * DeltaSeconds;
	}
	CheckForGameOver(Stamina, Sanity);
}

void Athe_new_catacombCharacter::CheckForGameOver(const float Stamina, const float Sanity) {
	if ((Sanity <= 0.0 || Stamina <= 0.0) && GameOverTriggered == false) {
		GameOverTriggered = true;
		GameOver();
	}
}


//////////////////////////////////////////////////////////////////////////
// Input

void Athe_new_catacombCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &Athe_new_catacombCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &Athe_new_catacombCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &Athe_new_catacombCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &Athe_new_catacombCharacter::LookUpAtRate);
}

void Athe_new_catacombCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void Athe_new_catacombCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void Athe_new_catacombCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void Athe_new_catacombCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void Athe_new_catacombCharacter::SetSanity(float newSanity)
{
	Sanity = FMath::Clamp(newSanity, 0.f, MaxSanity);
}

