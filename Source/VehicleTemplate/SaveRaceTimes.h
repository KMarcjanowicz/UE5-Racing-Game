// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveRaceTimes.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLETEMPLATE_API USaveRaceTimes : public USaveGame
{
	GENERATED_BODY()


public:
	// Sets default values for this actor's properties
	USaveRaceTimes();

	UPROPERTY(BlueprintReadWrite)
		float BestRaceTime;

	UPROPERTY(BlueprintReadWrite)
		float BestLapTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AGameOverseer* GameOverseer;
};
