// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "AITypes.h"
#include "MyCharacter.h"
#include "Navigation/PathFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "EnemyAIController.generated.h"


UCLASS()
class FPSGAME_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

private:
	virtual void BeginPlay()override;

	AEnemyAIController();
	UPROPERTY(EditAnywhere)
	UAIPerceptionComponent* PerceptionComp = nullptr;

	UPROPERTY(EditAnywhere)
	UAISenseConfig_Sight* SightConfig;
	UPROPERTY(EditAnywhere)

	UAISenseConfig_Hearing* HearingConfig;
	UFUNCTION()
		void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);


	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

	AMyCharacter* FpsCharacter;


	virtual FRotator GetControlRotation() const override;


	virtual void Tick(float DeltaSeconds) override;
	
	UFUNCTION()
		void	OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);




};
