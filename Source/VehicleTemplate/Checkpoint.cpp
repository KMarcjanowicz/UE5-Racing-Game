// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoint.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include <WheeledVehicle.h>


// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateOptionalDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Root);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Mesh Comp"));
	CollisionBox->SetHiddenInGame(false);
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::CheckpointClear);
	CollisionBox->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int ACheckpoint::GetCheckpointNumber()
{
	return CheckpointNumber;
}

void ACheckpoint::SetCheckpointNumber(int x)
{
	CheckpointNumber = x;
}

void ACheckpoint::CheckpointClear(UPrimitiveComponent * OverlappedActor, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Yellow, TEXT("Checkpoint collision happened!"));
	AWheeledVehicle* Vehicle = Cast<AWheeledVehicle>(OtherActor);

	if (!Vehicle || OtherActor == this) return;

	FRotator ArrowRotation = Arrow->GetComponentRotation();
	FVector ArrowVector = ArrowRotation.Vector();
	FVector ActorVelocity = Vehicle->GetVelocity();
	float AngleValue = FVector::DotProduct(ArrowVector, ActorVelocity);
	if (AngleValue > 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Yellow, TEXT("Correct clear!"));
		AVehicleTemplatePawn* PlayerVehicle = Cast<AVehicleTemplatePawn>(OtherActor);

		if (PlayerVehicle->IsValidLowLevel()) {
			ClearCheckpoint.Broadcast(CheckpointNumber, PlayerVehicle);
		}
		
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Yellow, TEXT("Bad direction!"));
	}
	


}

