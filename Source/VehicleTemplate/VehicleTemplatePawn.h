// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehicle.h"
#include "VehicleTemplatePawn.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UTextRenderComponent;
class UInputComponent;

UCLASS(config=Game)
class AVehicleTemplatePawn : public AWheeledVehicle
{
	GENERATED_BODY()

	/** Spring arm that will offset the camera */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	/** Camera component that will be our viewpoint */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	/** SCene component for the In-Car view origin */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* InternalCameraBase;

	/** Camera component for the In-Car view */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* InternalCamera;

	/** Text component for the In-Car speed */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* InCarSpeed;

	/** Text component for the In-Car gear */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* InCarGear;

	
public:
	AVehicleTemplatePawn();

	/** The current speed as a string eg 10 km/h */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly)
	FText SpeedDisplayString;

	/** The current gear as a string (R,N, 1,2 etc) */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly)
	FText GearDisplayString;

	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly)
	/** The color of the incar gear text in forward gears */
	FColor	GearDisplayColor;

	/** The color of the incar gear text when in reverse */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly)
	FColor	GearDisplayReverseColor;

	/** Are we using incar camera */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly)
	bool bInCarCameraActive;

	/** Are we in reverse gear */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly)
	bool bInReverseGear;

	/** Initial offset of incar camera */
	FVector InternalCameraOrigin;
	// Begin Pawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End Pawn interface

	// Begin Actor interface
	virtual void Tick(float Delta) override;
protected:
	virtual void BeginPlay() override;

public:
	// End Actor interface

	/** Handle pressing forwards */
	void MoveForward(float Val);
	/** Setup the strings used on the hud */
	void SetupInCarHUD();

	/** Update the physics material used by the vehicle mesh */
	void UpdatePhysicsMaterial();
	/** Handle pressing right */
	void MoveRight(float Val);
	/** Handle handbrake pressed */
	void OnHandbrakePressed();
	/** Handle handbrake released */
	void OnHandbrakeReleased();
	/** Switch between cameras */
	void OnToggleCamera();
	/** Handle reset VR device */
	void OnResetVR();

	static const FName LookUpBinding;
	static const FName LookRightBinding;

private:
	/** 
	 * Activate In-Car camera. Enable camera and sets visibility of incar hud display
	 *
	 * @param	bState true will enable in car view and set visibility of various if its doesnt match new state
	 * @param	bForce true will force to always change state
	 */
	void EnableIncarView( const bool bState, const bool bForce = false );

	/** Update the gear and speed strings */
	void UpdateHUDStrings();

	/* Are we on a 'slippery' surface */
	bool bIsLowFriction;


public:
	/** Returns SpringArm subobject **/
	FORCEINLINE USpringArmComponent* GetSpringArm() const { return SpringArm; }
	/** Returns Camera subobject **/
	FORCEINLINE UCameraComponent* GetCamera() const { return Camera; }
	/** Returns InternalCamera subobject **/
	FORCEINLINE UCameraComponent* GetInternalCamera() const { return InternalCamera; }
	/** Returns InCarSpeed subobject **/
	FORCEINLINE UTextRenderComponent* GetInCarSpeed() const { return InCarSpeed; }
	/** Returns InCarGear subobject **/
	FORCEINLINE UTextRenderComponent* GetInCarGear() const { return InCarGear; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CheckOnTrack", meta = (ToolTip = "Check if player is on track"))
		bool bIsOnTrack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CheckOnTrack", meta = (ToolTip = "Total penalty seconds added to lap, cleans after lap"))
		float PenaltySecTotal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CheckOnTrack", meta = (ToolTip = "Curreent Penalty points, to be added to total seconds"))
		float PenaltySecCurrent;

public:
	UFUNCTION()
		void SetIsOnTrack(bool IsOnTrack);
	UFUNCTION()
		bool GetIsOnTrack();

	UFUNCTION()
		bool CheckIfStuck();

	UFUNCTION()
		void AllowToRespawn();

	UFUNCTION()
		void DoubleCheckIfStuck();

	UFUNCTION()
		void OnStartGame();

public:

	//list of lap times
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<float> LapTimes;

	//number of the next checkpoint needed to clear!
	UPROPERTY(EditAnywhere)
		int NextCheckpoint;

	UPROPERTY(EditAnywhere)
		int MaxLaps;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int CurrentLap;

	UPROPERTY(EditAnywhere, Category="Respawn")
		FVector RespawnLocation;

	UPROPERTY(EditAnywhere, Category = "Respawn")
		FRotator RespawnRotation;

	UPROPERTY(EditAnywhere)
		int CurrentPosition;

	UPROPERTY(EditAnywhere)
		int MaxPosition;

	UPROPERTY(EditAnywhere)
		bool bIsStuck;
	UPROPERTY(EditAnywhere)
		bool bIsFlipped;
public:

	//Elements to display in HUD or on screen

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Display)
		FText CurrentLapText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Display)
		FText MaxLapsText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Display)
		FText CurrentPositionText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Display)
		TArray<FText> LapTimeStampsText;

	//for timing the amount of seconds after the player can respawn
	FTimerHandle UnusedHandle;

public:
	//behaviour tree for AI
	UPROPERTY(EditAnywhere, Category = "AI")
		class UBehaviorTree* BehaviorTree;

	//game overseer that needs to betalked to
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AGameOverseer* GameOverseer;
};