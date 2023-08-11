// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAttackAnimNotifyState.h"

#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "MyCharacter.h"

void UEnemyAttackAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                              float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);


	if (AEnemy* const Enemy = Cast<AEnemy>(MeshComp->GetOwner()))
	{
		AMyCharacter* const Player = Enemy->Player;


		Player->TakeDamage(FMath::RandRange(Enemy->DamageRange.Get<0>(), Enemy->DamageRange.Get<1>()));
	}
}

void UEnemyAttackAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
}
