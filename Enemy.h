// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAnimInstance.h"
#include "MyCharacter.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class FPSGAME_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemy();

protected:
	virtual void BeginPlay() override;

public:	

	void StartAttack();
	void StopAttack();
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* WeaponMesh{};
	void TakeDamage();
	AMyCharacter* Player{};
	TPair<float,float> DamageRange={3.f,5.f};
private:
	bool bDied{false};
	float Health{100.0f};
	void Die();


	UPROPERTY(EditAnywhere)
	UAnimMontage* HitReaction{};
UPROPERTY(EditAnywhere)
	UAnimMontage* AttackAnimMontage{};
	UEnemyAnimInstance* EnemyAnimInstance{};

	


};
