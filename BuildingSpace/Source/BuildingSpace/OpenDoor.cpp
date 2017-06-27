// Copyright Guillermo Bernal 2017

#include "OpenDoor.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UOpenDoor::OpenDoor()
{
	//Set The door Rotation
	Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}
void UOpenDoor::CloseDoor()
{
	//Set The door Rotation
	Owner->SetActorRotation(FRotator(0.f, 0.f, 0.f));
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	//FInd the owner actor
	Owner = GetOwner();


}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the trigger Volume

	if (GetTotalMassOfActorOnPlate() > 50.f) {//TODO function

	
	}

	//Check if it is time to close the Door
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime >= DoorCloseDelay)
	{
		CloseDoor();
		//LastDoorOpenTime = 0.f;
	}
}
float UOpenDoor:: GetTotalMassOfActorOnPlate()
{
	return 60.f;

}
