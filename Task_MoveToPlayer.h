
#pragma once

#include "CoreMinimal.h"
#include "EnemyAIController.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Task_MoveToPlayer.generated.h"


UCLASS()
class FPSGAME_API UTask_MoveToPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UTask_MoveToPlayer();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual  void OnInstanceCreated(UBehaviorTreeComponent& OwnerComp) override;

	UPROPERTY(EditAnywhere)
	float Distance{2500.f};
	


	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
private:
	AEnemyAIController* EnemyAIController{};
};
