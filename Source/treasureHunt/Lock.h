// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include"TriggerButton.h"
#include"Components/StaticMeshComponent.h"
#include "Lock.generated.h"

UCLASS()
class TREASUREHUNT_API ALock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleANywhere)
	USceneComponent* RootComp;


	UPROPERTY(VisibleANywhere)
	UTriggerButton* TriggerComp;


	UPROPERTY(VisibleANywhere)
	UStaticMeshComponent* KeyItemMesh;

	UPROPERTY(EditAnywhere)
	FString KeyItemName;

	void SetIsKeyPlaced(bool NewIsKeyPlaced);
	bool GetIsKeyPlaced();

private:
	UPROPERTY(VisibleAnywhere)
	bool IsKeyPlaced = false;

};
