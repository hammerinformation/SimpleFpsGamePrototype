// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "EnemyAIController.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Task_AttackThePlayer.generated.h"

UCLASS()
class FPSGAME_API UTask_AttackThePlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UTask_AttackThePlayer();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual  void OnInstanceCreated(UBehaviorTreeComponent& OwnerComp) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	
private:
	AEnemyAIController* EnemyAIController{};
	AEnemy* Pawn{};
	AMyCharacter* Player{};

	UPROPERTY(EditAnywhere)
	bool bStartAttack{true};
	
};
