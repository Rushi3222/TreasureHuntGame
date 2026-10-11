// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "doormover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TREASUREHUNT_API Udoormover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	Udoormover();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    

	UPROPERTY(EditAnywhere)
	FVector moveoffset=FVector(0,0,100);

	UPROPERTY(EditAnywhere)
	float movetime = 4.0f;

	UPROPERTY(EditAnywhere)
	bool shouldmove = false;

	UPROPERTY(VisibleAnywhere)
	bool reachedtarget = false;

	FVector targetlocation;

	FVector StartLocation;
		
};
