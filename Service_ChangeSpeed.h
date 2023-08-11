// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "Service_ChangeSpeed.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API UService_ChangeSpeed : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UService_ChangeSpeed();
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	UPROPERTY(EditAnywhere)
	float MaxWalkSpeed = 1024.0f;
	UPROPERTY(EditAnywhere)
	float MaxAcceleration = 512.0f;
};
