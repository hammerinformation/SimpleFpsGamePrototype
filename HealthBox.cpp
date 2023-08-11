#include "HealthBox.h"

#include "HealthBoxManager.h"
#include "MyCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

AHealthBox::AHealthBox()
{
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComponent;
}

void AHealthBox::Collect()
{
	if (AMyCharacter* const Player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		Player->Health += 75.f;
		if (Player->Health >= 100.f) { Player->Health = 100.f ;}
		AHealthBoxManager::GetInstance().SpawnHealthBox();
		Destroy();
	}
}

void AHealthBox::BeginPlay()
{
	Super::BeginPlay();
	

}
