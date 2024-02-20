// Fill out your copyright notice in the Description page of Project Settings.

#include "PhysicsTriggerActor.h"
#include <Components/StaticMeshComponent.h>
#include <WheeledVehicle.h>
#include <WheeledVehicleMovementComponent.h>
#include "VehicleTemplatePawn.h"

// Sets default values
APhysicsTriggerActor::APhysicsTriggerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Comp"));
	MeshComponent->SetupAttachment(RootComponent);

	//Register OnBeginOverlap function as an OnActorBeginOverlap delegate
	OnActorBeginOverlap.AddDynamic(this, &APhysicsTriggerActor::OnBeginOverlap);
	//Register OnEndOverlap function as an OnActorEndOverlap delegate
	OnActorEndOverlap.AddDynamic(this, &APhysicsTriggerActor::OnEndOverlap);
	//Register OnHit function as an OnActorHitOverlap delegate
	OnActorHit.AddDynamic(this, &APhysicsTriggerActor::OnHit);

}

// Called when the game starts or when spawned
void APhysicsTriggerActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APhysicsTriggerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APhysicsTriggerActor::OnBeginOverlap(AActor * OverlappedActor, AActor * OtherActor)
{
	AVehicleTemplatePawn* Vehicle = Cast<AVehicleTemplatePawn>(OtherActor);

	if (!Vehicle || OtherActor == this) return;
	
	GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, TEXT("Begin Overlap with Mesh"));

	if (this->ActorHasTag("Track")) {
		Vehicle->SetIsOnTrack(true);
	}
	else if (this->ActorHasTag("Ground")) {
		Vehicle->SetIsOnTrack(false);
	}

	/**
	UWheeledVehicleMovementComponent* MoveComp = Vehicle->GetVehicleMovement();

	float ImpulseMagnitude = FMath::RandRange(-1500, 1500);
	FVector Impulse = Vehicle->GetActorForwardVector()*ImpulseMagnitude;
	
	Vehicle->GetMesh()->AddImpulse(Impulse, TEXT("Vehicle_Base"), true);
	Vehicle->UpdateAllReplicatedComponents(); **/
}

void APhysicsTriggerActor::OnEndOverlap(AActor * OverlappedActor, AActor * OtherActor)
{
	AVehicleTemplatePawn* Vehicle = Cast<AVehicleTemplatePawn>(OtherActor);

	if (!Vehicle || OtherActor == this) return;

	GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, TEXT("End Overlap"));

	Vehicle->SetIsOnTrack(true);
}

void APhysicsTriggerActor::OnHit(AActor * SelfActor, AActor * OtherActor, FVector NormalImpulse, const FHitResult & Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, TEXT("A hit event"));
}

