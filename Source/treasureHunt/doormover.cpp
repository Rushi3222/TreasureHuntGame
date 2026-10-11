// Fill out your copyright notice in the Description page of Project Settings.


#include "doormover.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
Udoormover::Udoormover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void Udoormover::BeginPlay()
{
	Super::BeginPlay();

	// ...
	StartLocation = GetOwner()->GetActorLocation();
	targetlocation = StartLocation + moveoffset;
	UE_LOG(LogTemp, Display, TEXT("%s is at location %s"), *GetOwner()->GetActorNameOrLabel(), *StartLocation.ToCompactString());
	

}


// Called every frame
void Udoormover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (shouldmove)
	{
		targetlocation = StartLocation + moveoffset;

	}
	else {
		targetlocation = StartLocation;
	}

	FVector CurrentLocation = GetOwner()->GetActorLocation();

	reachedtarget = CurrentLocation.Equals(targetlocation);

	if (reachedtarget==false)
	{
		float speed = moveoffset.Length() / movetime;

		FVector newlocation = FMath::VInterpConstantTo(CurrentLocation, targetlocation, DeltaTime, speed);

		GetOwner()->SetActorLocation(newlocation);
	}

	

	
	
	// ...
}

