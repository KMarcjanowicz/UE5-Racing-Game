// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverseer.h"
#include "Components/BillboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "Components/TimelineComponent.h"
#include "StopWatch.h"
#include "Checkpoint.h"

// Sets default values
AGameOverseer::AGameOverseer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Billboard = CreateOptionalDefaultSubobject<UBillboardComponent>(TEXT("Visual Representation"));

	Billboard->SetupAttachment(RootComponent);

	StopWatch = CreateDefaultSubobject<UStopWatch>(TEXT("Stop Watch"));

	bGameStart = false;

	DoOnce = true;
}

// Called when the game starts or when spawned
void AGameOverseer::BeginPlay()
{
	Super::BeginPlay();
	
	TotalCheckpoints = CheckpointArray.Num();

	ApplyCheckpointNumbers();

	ApplyUserSettings();

	StartSequence();
}

// Called every frame
void AGameOverseer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bGameStart && DoOnce) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, TEXT("Game should Start!"));
		StopWatch->Start_Timer(true, 1.0f);
		DoOnce = false;
	}
	
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, StopWatch->TimeStamp);
	/*
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Red, TEXT("Using game overseer"));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Number of cars:  %d"), PlayerArray.Num()));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Number of Checkpoints:  %d"), CheckpointArray.Num()));
	}
	*/
}

//does not work
void AGameOverseer::BubbleSortActors(TArray<AActor*> ArrayToSort)
{
	int i, j;
	for (i = 0; i < ArrayToSort.Num() - 1; i++)
	{
		// Last i elements are already in place  
		for (j = 0; j < ArrayToSort.Num() - i - 1; j++)
		{
			ACheckpoint* Checkpoint1 = Cast<ACheckpoint>(ArrayToSort[j]);

			if (IsValid(Checkpoint1))
			{
				ACheckpoint* Checkpoint2 = Cast<ACheckpoint>(ArrayToSort[j + 1]);

				if (IsValid(Checkpoint2)) {
					if (Checkpoint1->GetCheckpointNumber() > Checkpoint2->GetCheckpointNumber())
					{
						Swap(ArrayToSort[j], ArrayToSort[j + 1]);
					}
				}

			}
		}
	}
}

//does not workw
void AGameOverseer::Swap(AActor * xp, AActor * yp)
{
	AActor* temp = xp;
	xp = yp;
	yp = temp;
}

int AGameOverseer::GetMaxLaps()
{
	return MaxLaps;
}

int AGameOverseer::GetTotalCheckpoints()
{
	return TotalCheckpoints;
}

void AGameOverseer::ApplyUserSettings()
{
	MaxLapsText = FText::AsNumber(MaxLaps);
	MaxPlayersText = FText::AsNumber(PlayerArray.Num());

	for (int i = 0; i < PlayerArray.Num(); i++)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Red, TEXT("Working on vehicle"));
		for (int j = 0; j < MaxLaps; j++)
		{
			PlayerArray[i]->LapTimes.Add(0.0f);
			PlayerArray[i]->LapTimeStampsText.Add(FText::AsCultureInvariant("--:--:--"));
		}
		PlayerArray[i]->NextCheckpoint = 1;
		PlayerArray[i]->CurrentLap = 1;
		PlayerArray[i]->CurrentPosition = i;

		PlayerArray[i]->CurrentLapText = FText::AsNumber(1);
		PlayerArray[i]->CurrentPositionText = FText::AsNumber(i);
	}
}

void AGameOverseer::StartSequence()
{
	for (int32 ActorIndex = 0; ActorIndex < CheckpointArray.Num(); ActorIndex++)
	{
		CheckpointArray[ActorIndex]->ClearCheckpoint.AddDynamic(this, &AGameOverseer::WhenCheckpointClear);
	}
}

void AGameOverseer::UpdateLap(AVehicleTemplatePawn * PlayerToUpdate)
{
	PlayerToUpdate->CurrentLap += 1;
	PlayerToUpdate->CurrentLapText = FText::AsNumber(PlayerToUpdate->CurrentLap);
	
}

void AGameOverseer::WhenCheckpointClear(int CheckpointNumber, AVehicleTemplatePawn * Player)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("I saw a Vehilce clear checkpoint with number:  %d"), CheckpointNumber));
	if (Player->NextCheckpoint == CheckpointNumber) {
		if (CheckpointNumber < TotalCheckpoints) {
			Player->NextCheckpoint += 1;
		}
		else {
			Player->LapTimes[Player->CurrentLap - 1] = StopWatch->GetTime();
			Player->LapTimeStampsText[Player->CurrentLap - 1] = FText::AsCultureInvariant(StopWatch->TimeStamp);
			/* else finish the race and end racing event */
			if (Player->CurrentLap == MaxLaps) {
				if (Player->ActorHasTag("Player")) {
					bGameEnd = true;
				}
			}
			else {
				if ((Player->CurrentLap + 1) <= MaxLaps) {
					//add lap time
					Player->CurrentLap += 1;
					Player->CurrentLapText = FText::AsNumber(Player->CurrentLap);
					Player->NextCheckpoint = 1;
				}
			}
			
		}

		for(int32 ActorIndex = 0; ActorIndex < CheckpointArray.Num(); ActorIndex++)
		{
			if (CheckpointNumber == CheckpointArray[ActorIndex]->GetCheckpointNumber())
			{
				Player->RespawnLocation = CheckpointArray[ActorIndex]->GetActorLocation();
				Player->RespawnRotation = CheckpointArray[ActorIndex]->GetActorRotation();
			}
		}
	}
}

void AGameOverseer::ApplyCheckpointNumbers()
{
	for (int i = 0; i < CheckpointArray.Num(); i++)
	{
		CheckpointArray[i]->SetCheckpointNumber(i + 1);
	}
}

