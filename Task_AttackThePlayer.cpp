#include "Task_AttackThePlayer.h"

#include "Kismet/GameplayStatics.h"

UTask_AttackThePlayer::UTask_AttackThePlayer()
{
	NodeName = "AttackThePlayer";
	bNotifyTick = true;
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UTask_AttackThePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (bStartAttack)
	{
		Pawn->StartAttack();
	}
	if (bStartAttack == false)
	{
		Pawn->StopAttack();
	}

	return EBTNodeResult::Succeeded;
}

void UTask_AttackThePlayer::OnInstanceCreated(UBehaviorTreeComponent& OwnerComp)
{
	Super::OnInstanceCreated(OwnerComp);
	EnemyAIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	Pawn = Cast<AEnemy>(EnemyAIController->GetPawn());
	Player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void UTask_AttackThePlayer::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}
