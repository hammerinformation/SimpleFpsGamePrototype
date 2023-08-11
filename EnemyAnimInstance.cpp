

#include "EnemyAnimInstance.h"

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (TryGetPawnOwner())
	{
		Speed = TryGetPawnOwner()->GetVelocity().Size();

	}
}
