// Copyright Guillermo Bernal 2017

#include "Grabber.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT(" Grabber reporting for duty! "));

	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get the player view point this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	//TODO Log out to test
    /*
	FString PVLocation = PlayerViewPointLocation.ToString();
	FString PVRotation = PlayerViewPointRotation.ToString();
	UE_LOG(LogTemp, Warning, TEXT(" Player's Location %s,  Rotation %s "), *PVLocation, *PVRotation);
     */
    FVector LineTraceDirection = PlayerViewPointRotation.Vector() ;
    FVector LineTraceEnd = PlayerViewPointLocation + LineTraceDirection * Reach ;
    
    //Draw a red trace in the world
    DrawDebugLine(
                  GetWorld(),
                  PlayerViewPointLocation,
                  LineTraceEnd,
                  FColor(255,0,0),
                  false,
                  0.f,
                  0.f,
                  10.f
                  );
	// Ray-Cast out to reach distance
	
    // See what we hit

}

