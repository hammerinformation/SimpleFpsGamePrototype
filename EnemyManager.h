#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyManager.generated.h"

UCLASS()
class FPSGAME_API AEnemyManager : public AActor
{
	GENERATED_BODY()

public:
	AEnemyManager();

protected:
	virtual void BeginPlay() override;

private:
	inline static AEnemyManager* Instance{};

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> Enemy{};

	UPROPERTY(EditAnywhere)
	TArray<FVector> SpawnPoints{};

	UPROPERTY(EditAnywhere)
	float SpawnTime{5.0f};
	void SpawnEnemy(const float& Val);

public:
	static AEnemyManager& GetInstance();
	void SpawnEnemy();
};
