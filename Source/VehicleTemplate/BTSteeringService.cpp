// Fill out your copyright notice in the Description page of Project Settings.

#include "BTSteeringService.h"
#include <EngineUtils.h>
#include <BehaviorTree/BlackboardComponent.h>
#include "VehicleTemplatePawn.h"
#include "AIWheeledVehicleController.h"
#include "GameOverseer.h"

void UBTSteeringService::OnGameplayTaskActivated(UGameplayTask & task)
{
	//nothing here
	//This method must be overridden from the inherited interface
	//Otherwise, the linker will fail.
}

void UBTSteeringService::OnGameplayTaskDeactivated(UGameplayTask & task)
{
	//nothing here
	//This method must be overridden from the inherited interface
	//Otherwise, the linker will fail.
}

void UBTSteeringService::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	UWorld* world = OwnerComp.GetWorld();

	TActorIterator<AVehicleTemplatePawn> PlayerPawnIter(world);
	//Not particularly robust, but at least here we are dealing with only one player
	if (&PlayerPawn != NULL)
	{
		PlayerPawn = *PlayerPawnIter;
	}

	if (PlayerPawn)
	{
		//get the owner pawn to this pointer
		APawn* OwnerPawn; // =OwnerPawn.GetOwner();
		AAIWheeledVehicleController* AIVehicle = Cast<AAIWheeledVehicleController>(OwnerComp.GetAIOwner());
		OwnerPawn = AIVehicle->GetPawn();
		AVehicleTemplatePawn* VehiclePawn = Cast<AVehicleTemplatePawn>(OwnerPawn);

		int NextCheckpointNumber = VehiclePawn->NextCheckpoint;
		FVector CheckpointLocation = VehiclePawn->GameOverseer->CheckpointArray[NextCheckpointNumber - 1]->GetActorLocation();

		FVector ForwardVector = OwnerPawn->GetActorForwardVector();
		FVector RightVector = OwnerPawn->GetActorRightVector();
		FVector TargetDirection = CheckpointLocation - OwnerPawn->GetActorLocation();

		float Distance = FVector::DistSquared(CheckpointLocation, OwnerPawn->GetActorLocation());
		float Throttle = FMath::Clamp<float>(0.0f, 1.0f, Distance / 4000.0f);

		TargetDirection.Normalize();

		float AngleValue = FVector::DotProduct(ForwardVector, TargetDirection);
		float SteerValue = FVector::DotProduct(RightVector, TargetDirection) < 0.0f ? -(1.0f - AngleValue) : (AngleValue - 1.0f);

		AIVehicle->BlackboardComp->SetValueAsVector("PlayerLocation", OwnerPawn->GetActorLocation());
		AIVehicle->BlackboardComp->SetValueAsFloat("SteeringValue", SteerValue);
		AIVehicle->BlackboardComp->SetValueAsFloat("ThrottleValue", AngleValue < 0.0f ? -1.0f : Throttle);

	}
}
