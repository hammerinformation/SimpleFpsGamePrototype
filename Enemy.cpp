#include "Enemy.h"

#include "BrainComponent.h"
#include "EnemyAIController.h"
#include "EnemyManager.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	WeaponMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "RightHandSocket");
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	Health = 100.f;
	Player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	EnemyAnimInstance = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());
}




void AEnemy::TakeDamage()
{
	if (bDied) { return; }
	Health -= FMath::RandRange(10.f, 90.f);

	if (Health <= 0)
	{
		Health = 0;
		Die();
		return;
	}

	if (EnemyAnimInstance && HitReaction)
	{
		EnemyAnimInstance->Montage_Play(HitReaction);
	}
}


void AEnemy::StartAttack()
{
	if (EnemyAnimInstance)
	{
		EnemyAnimInstance->bCanAttack = true;
	}
}

void AEnemy::StopAttack()
{
	if (EnemyAnimInstance)
	{
		EnemyAnimInstance->bCanAttack = false;
	}
}

void AEnemy::Die()
{
	bDied = true;
	WeaponMesh->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	WeaponMesh->SetSimulatePhysics(true);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);


	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	GetMesh()->SetSimulatePhysics(true);

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetCapsuleComponent()->SetSimulatePhysics(true);
	if (Player)
	{
		Player->KilledEnemyCount+=1;
		Player->UpdateKilledEnemyText();
		GetMesh()->AddForce(
			Player->GetActorForwardVector() * FMath::RandRange(7'000, 500'000) + (FVector::UpVector * 1'500));
	}
	GetCharacterMovement()->MaxWalkSpeed = 0.f;
	GetMesh()->bPauseAnims = true;
	if (const AEnemyAIController* const EnemyAIController = Cast<AEnemyAIController>(GetController()))
	{
		EnemyAIController->GetBrainComponent()->DestroyComponent();
	}


	AEnemyManager::GetInstance().SpawnEnemy();
	
	SetLifeSpan(4.f);
}
