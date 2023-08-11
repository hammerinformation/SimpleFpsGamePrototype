

#include "HealthBoxManager.h"

AHealthBoxManager::AHealthBoxManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AHealthBoxManager::BeginPlay()
{
	Super::BeginPlay();
	Instance=this;
	SpawnHealthBox();
	
}

AHealthBoxManager& AHealthBoxManager::GetInstance()
{
	return  *Instance;
}

void AHealthBoxManager::SpawnHealthBox()
{
	if (GetWorld() && HealthBox)
	{
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]
		{
			GetWorld()->SpawnActor<AActor>(HealthBox, SpawnPoints[FMath::RandRange(0, SpawnPoints.Num() - 1)],
										   FRotator::ZeroRotator);
		}), 5.f, false);
	}
}

