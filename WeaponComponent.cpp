// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"

#include "Enemy.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

UWeaponComponent::UWeaponComponent()
{
	
	PrimaryComponentTick.bCanEverTick = true;

}


void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AMyCharacter* const Player = Cast<AMyCharacter>(GetOwner()))
	{
		FpsCharacter = Player;
		WeaponMesh = Player->WeaponMesh;
		UInputComponent* PlayerInputComponent = Player->InputComponent;
		PlayerInputComponent->BindKey(EKeys::LeftMouseButton, IE_Pressed, this, &UWeaponComponent::StartFire);
		PlayerInputComponent->BindKey(EKeys::LeftMouseButton, IE_Repeat, this, &UWeaponComponent::OnFire);
		PlayerInputComponent->BindKey(EKeys::LeftMouseButton, IE_Released, this, &UWeaponComponent::StopFire);
	}
}


void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UWeaponComponent::StartFire()
{
	
	OnFire();
}

void UWeaponComponent::OnFire()
{
	if (const APlayerCameraManager* const PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0))
	{
		if (UAnimInstance* AnimInstance = WeaponMesh->GetAnimInstance())
		{
			if (FireAnimMontage)
			{
				AnimInstance->Montage_Play(FireAnimMontage);
				
			}
		}
		FHitResult OutHit;
		FVector Start = PlayerCameraManager->GetCameraLocation();
		FVector ForwardVector = PlayerCameraManager->GetCameraLocation().ForwardVector.GetSafeNormal();
		ForwardVector = PlayerCameraManager->GetCameraRotation().Vector();
		FVector End = ((ForwardVector * 100000.f) + Start);
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(GetOwner());
		if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Camera, CollisionParams))
		{
			if (OutHit.bBlockingHit)
			{
				if (AEnemy* const Enemy = Cast<AEnemy>(OutHit.GetActor()))
				{
					Enemy->TakeDamage();
				}
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red,
				                                 FString::Printf(
					                                 TEXT("You are hitting: %s"), *OutHit.GetActor()->GetName()));
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Purple,
				                                 FString::Printf(
					                                 TEXT("Impact Point: %s"), *OutHit.ImpactPoint.ToString()));
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue,
				                                 FString::Printf(
					                                 TEXT("Normal Point: %s"), *OutHit.ImpactNormal.ToString()));

				DrawDebugSphere(GetWorld(), OutHit.ImpactPoint, 5, 60, FColor::Red, false, 2.0f);
			}
		}
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.f);
	}
}

void UWeaponComponent::StopFire()
{
}
