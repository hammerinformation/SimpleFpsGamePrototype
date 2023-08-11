

#include "Task_MoveToPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"

UTask_MoveToPlayer::UTask_MoveToPlayer()
{
	NodeName="MoveToPlayer";
	bCreateNodeInstance=true;
	bNotifyTick=true;
}

EBTNodeResult::Type UTask_MoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::InProgress;
}

void UTask_MoveToPlayer::OnInstanceCreated(UBehaviorTreeComponent& OwnerComp)
{
	Super::OnInstanceCreated(OwnerComp);
	EnemyAIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());

}

void UTask_MoveToPlayer::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if(EnemyAIController)
	{
		FVector Target=EnemyAIController->GetBlackboardComponent()->GetValueAsVector("LastSeenPlayerLocation");
		EnemyAIController->MoveToLocation(Target);

		if(FVector::Distance(EnemyAIController->GetPawn()->GetActorLocation(),Target)<Distance)
		{
			FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
		}
	}
}