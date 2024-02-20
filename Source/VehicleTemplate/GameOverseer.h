// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Checkpoint.h"
#include "VehicleTemplatePawn.h"
#include "EngineUtils.h"
#include "Components/TimelineComponent.h"
#include "GameOverseer.generated.h"

UCLASS()
class VEHICLETEMPLATE_API AGameOverseer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameOverseer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "For Start Splash Screen, True if player can steer car"))
		bool bGameStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "For End Splash Screen, True if player can steer car"))
		bool bGameEnd;

	// when I need to do something once in Tick function
	bool DoOnce;

	//user defined maximum laps
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MaxLaps;

	//number of all checkpoints in the level
	UPROPERTY(EditAnywhere)
		int TotalCheckpoints;

	//times for medals
	UPROPERTY(EditAnywhere, meta = (ToolTip = "Gold Time"))
		float GoldTime;

	UPROPERTY(EditAnywhere, meta = (ToolTip = "Silver Time"))
		float SilverTime;

	UPROPERTY(EditAnywhere, meta = (ToolTip = "Bronze Time"))
		float BronzeTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "Gold Time Text"))
		FText GoldTimeText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "Silver Time Text"))
		FText SilverTimeText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "Bronze Time Text"))
		FText BronzeTimeText;

	//level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "Name of this track"))
		FText LevelName;

	//user defined maximum laps text for HUD
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText MaxLapsText;

	//user defined maximum players for HUD
	UPROPERTY(EditAnywhere)
		FText MaxPlayersText;

	UPROPERTY(EditAnywhere)
		FString SaveGameName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RacingLogic, meta = (ToolTip = "Assing the checkpoints to this array"))
		TArray<ACheckpoint*> CheckpointArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RacingLogic, meta = (ToolTip = "Assing the players(cars) to this array"))
		TArray<AVehicleTemplatePawn*> PlayerArray;

public:

	UFUNCTION()
		void BubbleSortActors(TArray<AActor*> ArrayToSort);

	UFUNCTION()
		void Swap(AActor *xp, AActor *yp);

	UFUNCTION()
		void ApplyUserSettings();

	UFUNCTION()
		void StartSequence();

	UFUNCTION()
		void UpdateLap(AVehicleTemplatePawn* PlayerToUpdate);

	UFUNCTION()
		void WhenCheckpointClear(int CheckpointNumber, AVehicleTemplatePawn* Player);

	UFUNCTION()
		void ApplyCheckpointNumbers();

	UFUNCTION()
		int GetMaxLaps();

	UFUNCTION()
		int GetTotalCheckpoints();

public:
	/** StopWatch Class for time management*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Timer, meta = (ToolTip = "Stopwatch Timer"))
		class UStopWatch* StopWatch;

	//visual representation of the overseer
	UPROPERTY(EditAnywhere)
		class UBillboardComponent* Billboard;


};
