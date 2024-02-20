// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTaskThrottle.h"
#include <BehaviorTree/BTTaskNode.h>
#include <BehaviorTree/BlackboardComponent.h>
#include <BehaviorTree/BehaviorTreeTypes.h>
#include "AIWheeledVehicleController.h"
#include "WheeledVehicleMovementComponent4W.h"

EBTNodeResult::Type UBTTaskThrottle::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AAIWheeledVehicleController* AIController = Cast<AAIWheeledVehicleController>(OwnerComp.GetAIOwner());

	if (AIController)
	{
		UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
		float Throttle;

		if (Blackboard->HasValidAsset())
		{
			Throttle = Blackboard->GetValueAsFloat("ThrottleValue");
		}
		else
		{
			//Use RandRange from FMath to  generate  a random  steering  angle
			Throttle = FMath::RandRange(-1.0f, 1.0f);
		}
		

		AIController->VehicleMovementComp->SetThrottleInput(Throttle);

		//Inform BT Tree that the task has succeeded
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

void UBTTaskThrottle::OnGameplayTaskActivated(UGameplayTask & task)
{
	//This method must be overridden
	//Otherwise, the linker will fail.
}


