#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"

#include "TriggerButton.generated.h"

class Udoormover;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TREASUREHUNT_API UTriggerButton : public UBoxComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTriggerButton();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(
		float DeltaTime,
		ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction
	) override;

	void Trigger(bool NewTriggerValue);

	UPROPERTY(EditAnywhere)
	AActor* MoverActor = nullptr;

	Udoormover* mover = nullptr;

	UPROPERTY(VisibleAnywhere)
	bool IsTriggered = false;

	UPROPERTY(VisibleAnywhere)
	int ActivatorCount = 0;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> RequiredItemClass;

	

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION()
	void OnOverlapEnd(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);
};
