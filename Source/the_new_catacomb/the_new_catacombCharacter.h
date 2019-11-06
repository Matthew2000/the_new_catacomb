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

	/*
	All stat related values are intended to be precentages so they are clamped between 0 and 100
	*/
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Character")
		void GameOver();

	UFUNCTION()
		void CheckForGameOver(const float Stamina, const float Sanity);

	UFUNCTION(BlueprintSetter)
		void SetSanity(float newSanity);

	UPROPERTY()
		bool GameOverTriggered = false;		//if this bool does not exist, then the game over event will repeat itself on tick
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats, meta = (ClampMin = "0.0", ClampMax = "100.0"))
		float Stamina = 20.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter=SetSanity, Category = Stats, meta = (ClampMin = "0.0"))
		float Sanity = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats, meta = (ClampMin = "0.0"))
		float MaxSanity = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats, meta = (ClampMin = "0.0", ClampMax = "100.0"))
		float OilLevel = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats, meta = (ClampMin = "0.0"))
		int32 Food = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats, meta = (ClampMin = "0.0"))
		int32 Water = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats, meta = (ClampMin = "0.0"))
		int32 Matches = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats, meta = (ClampMin = "0.0"))
		int32 Keys = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats, meta = (ClampMin = "0.0", ClampMax = "100.0"))
		float SanityDecrement = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats, meta = (ClampMin = "0.0", ClampMax = "100.0"))
		float StaminaDecrement = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats, meta = (ClampMin = "0.0", ClampMax = "100.0"))
		float SanityIncrement = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		bool InLight = false;


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};