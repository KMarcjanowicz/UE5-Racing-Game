// Fill out your copyright notice in the Description page of Project Settings.


#include "AIWheeledVehicleController.h"
#include "VehicleTemplatePawn.h"
#include "WheeledVehicleMovementComponent4W.h"
#include <BehaviorTree/BlackboardComponent.h>
#include <BehaviorTree/Blackboardcomponent.h>
#include <BehaviorTree/BehaviorTree.h>

AAIWheeledVehicleController::AAIWheeledVehicleController()
{
	VehicleMovementComp = NULL;
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("AIVehicleBehaviorComponent"));
	BlackboardComp = CreateAbstractDefaultSubobject<UBlackboardComponent>(TEXT("AIVehicleBlackboardComponent"));
}

void AAIWheeledVehicleController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);

	AVehicleTemplatePawn* AIVehicle = Cast<AVehicleTemplatePawn>(InPawn);

	if (AIVehicle) {
		VehicleMovementComp = AIVehicle->GetVehicleMovementComponent();

		if (AIVehicle->BehaviorTree && AIVehicle->BehaviorTree->BlackboardAsset)
		{
			// cache and initialize the blackboard component if there is one
			BlackboardComp->InitializeBlackboard(*(AIVehicle->BehaviorTree->BlackboardAsset));
		}

		if (AIVehicle->BehaviorTree)
		{
			BehaviorTreeComp->StartTree(*AIVehicle->BehaviorTree);
		}
	}

}

void AAIWheeledVehicleController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AVehicleTemplatePawn* AIVehicle = Cast<AVehicleTemplatePawn>(GetPawn());

	if (AIVehicle && !AIVehicle->BehaviorTree)
	{
		VehicleMovementComp->SetThrottleInput(1.0f);
		VehicleMovementComp->SetSteeringInput(-1.0f);
	}

}
