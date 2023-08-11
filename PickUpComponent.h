
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "PickUpComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSGAME_API UPickUpComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPickUpComponent();

protected:
	virtual void BeginPlay() override;

};
