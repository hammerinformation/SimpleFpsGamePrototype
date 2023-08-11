// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

#include "Enemy.h"
#include "Engine/Engine.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"
#include "MyCharacter.h"

#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"

#define STOP_FUNC return;
AEnemyAIController::AEnemyAIController()
{
	PrimaryActorTick.bCanEverTick = true;


	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
	SetPerceptionComponent(*PerceptionComp);
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));
	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
	GetPerceptionComponent()->ConfigureSense(*HearingConfig);
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(0.1f);
	FpsCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	ReceiveMoveCompleted.AddDynamic(this, &AEnemyAIController::OnMoveCompleted);
	


	GetPerceptionComponent()->OnTargetPerceptionUpdated.
	                          AddDynamic(this, &AEnemyAIController::OnTargetPerceptionUpdated);

	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnPerceptionUpdated);
}



void AEnemyAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	
}

void AEnemyAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	
}

void AEnemyAIController::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	if (Result == EPathFollowingResult::Invalid)
	{
	}
}



FRotator AEnemyAIController::GetControlRotation() const
{
	if (GetPawn() == nullptr)
	{
		return FRotator();
	}

	return FRotator(0.0f, GetPawn()->GetActorRotation().Yaw, 0.0f);
}

void AEnemyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(FpsCharacter&&GetBlackboardComponent())
	{
		
		GetBlackboardComponent()->SetValueAsBool("HasLineOfSight",LineOfSightTo(FpsCharacter,GetPawn()->GetActorLocation()));
	}
	
	


	if (GetBlackboardComponent() && GetBlackboardComponent()->GetValueAsBool("HasLineOfSight") && FpsCharacter)
	{
		GetBlackboardComponent()->SetValueAsVector("LastSeenPlayerLocation", FpsCharacter->GetActorLocation());
		GetBlackboardComponent()->SetValueAsFloat(
			"Distance", FVector::Distance(GetPawn()->GetActorLocation(), FpsCharacter->GetActorLocation()));
	}
}
