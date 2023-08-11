
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Collectable.generated.h"

UINTERFACE(MinimalAPI)
class UCollectable : public UInterface
{
	GENERATED_BODY()

};

class FPSGAME_API ICollectable
{
	GENERATED_BODY()
public:
	virtual void Collect()=0;

};
