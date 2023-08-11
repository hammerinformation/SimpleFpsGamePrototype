#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class FPSGAME_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyCharacter();

protected:
	virtual void BeginPlay() override;

public:
	void TakeDamage(const float&Damage);
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveRight(float Value);
	void MoveForward(float Value);


	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* WeaponMesh;
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* CameraSpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	float Health{100.f};
void UpdateKilledEnemyText()const;
	int KilledEnemyCount{0};

	

private:
	float TempMaxWalkSpeed{};
	void StartRun();
	void StopRun();



public:	
	UPROPERTY(EditAnywhere)
	UBoxComponent* Trigger;


	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);
		
};
