#include "EnemyManager.h"

AEnemyManager::AEnemyManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();

	Instance = this;


	for (int i = 0; i < 5; ++i)
	{
		SpawnEnemy(FMath::RandRange(4.f, 6.f));
	}
}


AEnemyManager& AEnemyManager::GetInstance()
{
	return *Instance;
}

void AEnemyManager::SpawnEnemy(const float& Val)
{
	if (GetWorld() && Enemy)
	{
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]
		{
			GetWorld()->SpawnActor<AActor>(Enemy, SpawnPoints[FMath::RandRange(0, SpawnPoints.Num() - 1)],
			                               FRotator::ZeroRotator);
		}), Val, false);
	}
}

void AEnemyManager::SpawnEnemy()
{
	if (GetWorld() && Enemy)
	{
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]
		{
			GetWorld()->SpawnActor<AActor>(Enemy, SpawnPoints[FMath::RandRange(0, SpawnPoints.Num() - 1)],
			                               FRotator::ZeroRotator);
		}), SpawnTime, false);
	}
}
