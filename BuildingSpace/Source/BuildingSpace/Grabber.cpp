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
	FindPhysicsHandleComponent();
	SetInputComponent();	
}
/// Look for the attached physics handle 
void UGrabber::FindPhysicsHandleComponent() {
	
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle==nullptr)
	{
		//everything is ok.
		UE_LOG(LogTemp, Error, TEXT("%s physics handle component is missing"), *GetOwner()->GetName());
	}
}

void UGrabber::SetInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		//Bind input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s Input component is missing"), *GetOwner()->GetName());
	}
<<<<<<< Updated upstream

=======
    
    /// Look for the attached Input component
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if (InputComponent)
    {
        //everything is ok.
        UE_LOG(LogTemp, Warning, TEXT("%s input component found"), *GetOwner()->GetName());

    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("%s input component is missing"), *GetOwner()->GetName());
    }
    
>>>>>>> Stashed changes
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//If the physics is attached
	if(PhysicsHandle->GrabbedComponent)
	{
		// move the object that we are holding each frame
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}
}
void UGrabber::Grab()
{
	// LINE TRACE and see if we reach any actor with physics body collision set
	auto HitResult= GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto HitActor = HitResult.GetActor();
	//If we hit something then attached a physics handle 
	if (HitActor) {
		PhysicsHandle->GrabComponent(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true);//allow rotation
	}
}

void UGrabber::Release()
{	
	PhysicsHandle->ReleaseComponent();
}
const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	///Line-trace (AKA Ray-Cast) out to reach distance
	FHitResult HitResult;
	///Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);
	/// See what we hit
	AActor* ActorHit = HitResult.GetActor();
	if (ActorHit) {
		UE_LOG(LogTemp, Warning, TEXT(" Collition with item: %s "), *(ActorHit->GetName()));
	}
	return HitResult;
}

FVector UGrabber::GetReachLineStart()
{
	// Get the player view point this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	return PlayerViewPointLocation;
}
FVector UGrabber::GetReachLineEnd()
{
	// Get the player view point this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	return PlayerViewPointLocation +PlayerViewPointRotation.Vector()* Reach;
}