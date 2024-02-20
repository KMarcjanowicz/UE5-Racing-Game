// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIWheeledVehicleController.generated.h"

/**
 *
 */
UCLASS()
class VEHICLETEMPLATE_API AAIWheeledVehicleController : public AAIController
{
	GENERATED_BODY()
public:

	//A Cached vehicle movement component
	class UWheeledVehicleMovementComponent* VehicleMovementComp;

	//a cached BT component
	class UBehaviorTreeComponent* BehaviorTreeComp;

	//a cached BlackBoard component
	class UBlackboardComponent* BlackboardComp;

public:

	AAIWheeledVehicleController();

	//override possess to handle additional setup
	virtual void OnPossess(APawn* InPawn) override;

	//override Tick to add some autonomus functions
	virtual void Tick(float DeltaTime) override;

};