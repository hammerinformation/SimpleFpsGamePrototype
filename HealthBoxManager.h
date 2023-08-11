// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthBoxManager.generated.h"

UCLASS()
class FPSGAME_API AHealthBoxManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthBoxManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	inline static AHealthBoxManager* Instance{};

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> HealthBox{};

	UPROPERTY(EditAnywhere)
	TArray<FVector> SpawnPoints{};

	UPROPERTY(EditAnywhere)
	float SpawnTime{5.0f};

public:
	static AHealthBoxManager& GetInstance();
	void SpawnHealthBox();

};
