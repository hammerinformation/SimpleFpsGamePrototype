#pragma once

#include "CoreMinimal.h"
#include "Collectable.h"
#include "GameFramework/Actor.h"
#include "HealthBox.generated.h"

UCLASS()
class FPSGAME_API AHealthBox : public AActor, public ICollectable
{
	GENERATED_BODY()

public:
	AHealthBox();

	virtual void Collect() override;
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent{};
};
