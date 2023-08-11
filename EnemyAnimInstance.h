
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"


UCLASS()
class FPSGAME_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Speed{};
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bCanAttack{};
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
