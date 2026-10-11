// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerButton.h"
#include "doormover.h"

UTriggerButton::UTriggerButton()
{
	PrimaryComponentTick.bCanEverTick =  true;
	UE_LOG(LogTemp, Warning, TEXT("trigger button is constructing"));
	
	
}

void UTriggerButton::BeginPlay()
{
	Super::BeginPlay();

	if (MoverActor )
	{
		mover = MoverActor->FindComponentByClass<Udoormover>();
		if (mover )
		{
			
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("failed to find actor"));
		}

	} 
	else
	{
		UE_LOG(LogTemp, Display, TEXT("doormover actor is nullptr"));
	}

	OnComponentBeginOverlap.AddDynamic(this, &UTriggerButton::OnOverlapBegin);

	OnComponentEndOverlap.AddDynamic(this, &UTriggerButton::OnOverlapEnd);

}

void UTriggerButton::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

void UTriggerButton::Trigger(bool NewTriggerValue)
{
	IsTriggered = NewTriggerValue;
	if (mover)
	{
		mover->shouldmove = IsTriggered;
	}
	else
	{
		UE_LOG(LogTemp ,Display ,TEXT("%s DOESN'T have a mover"), *GetOwner()->GetActorNameOrLabel());
	}
}


void UTriggerButton::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{ 
	if (OtherActor && OtherActor->IsA(RequiredItemClass))
	{  

		ActivatorCount++;
		if (!IsTriggered)
		{
			Trigger(true);
		}
		
	}
	
}

void UTriggerButton::OnOverlapEnd(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->IsA(RequiredItemClass))
	
		
	{  
		ActivatorCount--;
		if (IsTriggered&& ActivatorCount==0) 
		{
			Trigger(false);
		}
		
	}
}