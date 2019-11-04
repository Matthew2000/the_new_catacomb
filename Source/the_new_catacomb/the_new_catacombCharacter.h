// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CableComponent.h"
#include "the_new_catacombCharacter.generated.h"

class UInputComponent;

UCLASS(config = Game)
class Athe_new_catacombCharacter : public ACharacter
{
	GENERATED_BODY()

		/** First person camera */
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere)
		class UCableComponent* TheseusString;

public:
	Athe_new_catacombCharacter();

	void AttachRope();

protected:
	virtual void BeginPlay();

	virtual void Tick(float DeltaSeconds);

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

protected:

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats, meta = (ClampMin = "0.0", ClampMax = "100.0"))
		float Stamina = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats, meta = (ClampMin = "0.0", ClampMax = "100.0"))
		float Sanity = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats, meta = (ClampMin = "0.0", ClampMax = "100.0"))
		float SanityDecrement = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats, meta = (ClampMin = "0.0", ClampMax = "100.0"))
		float StaminaDecrement = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats, meta = (ClampMin = "0.0", ClampMax = "100.0"))
		float SanityIncrement = 1.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stats, meta = (ClampMin = "0.0", ClampMax = "100.0"))
		float CurrentLightLevel = 0.f;

	// The level of light for when the player's sanity will start to increase
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats, meta = (ClampMin = "0.0", ClampMax = "100.0"))
		float PositiveLightLevel = 60.f;

	// The level of light for when the player's sanity will start to decrease
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats, meta = (ClampMin = "0.0", ClampMax = "100.0"))
		float NegativeLightLevel = 40.f;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};