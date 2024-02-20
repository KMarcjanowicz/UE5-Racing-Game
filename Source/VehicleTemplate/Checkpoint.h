  // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VehicleTemplatePawn.h"
#include "Checkpoint.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerCheckpointClear, int, CheckpointNumber, AVehicleTemplatePawn*, Player);


UCLASS()
class VEHICLETEMPLATE_API ACheckpoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckpoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	//order number of the checkpoint
	UPROPERTY(EditAnywhere)
		int CheckpointNumber;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	//root replacement
	UPROPERTY(EditAnywhere)
		class USceneComponent* Root;

	//arrow to display the direction of the chackpoint
	UPROPERTY(EditAnywhere)
		class UArrowComponent* Arrow;

	//collision for checkpoint
	UPROPERTY(EditAnywhere)
		class UBoxComponent* CollisionBox;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
		FOnPlayerCheckpointClear ClearCheckpoint;

public:
	UFUNCTION()
		int GetCheckpointNumber();

	UFUNCTION()
		void SetCheckpointNumber(int x);

	UFUNCTION()
		void CheckpointClear(UPrimitiveComponent * OverlappedActor, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);


};
