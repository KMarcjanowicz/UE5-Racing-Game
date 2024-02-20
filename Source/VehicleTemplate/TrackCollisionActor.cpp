// Fill out your copyright notice in the Description page of Project Settings.


#include "TrackCollisionActor.h"

// Sets default values
ATrackCollisionActor::ATrackCollisionActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Comp"));
	MeshComponent->SetupAttachment(RootComponent);

	this->Tags.Add("GroundCollision");
}

// Called when the game starts or when spawned
void ATrackCollisionActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrackCollisionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

