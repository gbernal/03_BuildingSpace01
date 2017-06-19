// Fill out your copyright notice in the Description page of Project Settings.

#include "PosReport.h"
#include "Gameframework/Actor.h"

// Sets default values for this component's properties
UPosReport::UPosReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UPosReport::BeginPlay()
{
	Super::BeginPlay();
    //Find the owning actor
	FString ObjectOwner = GetOwner()->GetName();
    FString ObjectPos = GetOwner()->GetTransform().GetLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT(" %s is at %s "), *ObjectOwner, *ObjectPos);

	
}


// Called every frame
void UPosReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

