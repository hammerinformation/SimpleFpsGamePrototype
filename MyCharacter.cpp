#include "MyCharacter.h"

#include "Collectable.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "MyHUD.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"

static AMyHUD* MyHud{nullptr};

AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	CameraSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArmComponent"));
	CameraSpringArmComponent->SetRelativeLocation(FVector(0, 0, 60));
	CameraSpringArmComponent->SetupAttachment(GetCapsuleComponent());
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachToComponent(CameraSpringArmComponent, FAttachmentTransformRules::KeepRelativeTransform);
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->AttachToComponent(Camera, FAttachmentTransformRules::KeepRelativeTransform);
	Trigger=CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	Trigger->SetupAttachment(RootComponent);
}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	Health = 100.f;
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacter::OnComponentBeginOverlap);

	FTimerHandle TimerHandle;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]
	{
		MyHud = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	}), 1.5f, false);
}

void AMyCharacter::TakeDamage(const float&Damage)
{
	Health -= Damage;
	if (MyHud)
	{
		MyHud->MyUserWidget->UpdatePlayerHealthProgressBar(Health);
	}
}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindKey(EKeys::SpaceBar, IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindKey(EKeys::LeftShift, IE_Pressed, this, &AMyCharacter::StartRun);
	PlayerInputComponent->BindKey(EKeys::LeftShift, IE_Released, this, &AMyCharacter::StopRun);
	PlayerInputComponent->BindAxis("Horizontal", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Vertical", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Mouse_X", this, &AMyCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Mouse_Y", this, &AMyCharacter::LookUpAtRate);
}

void AMyCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void AMyCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void AMyCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate);
}

void AMyCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate);
}

void AMyCharacter::UpdateKilledEnemyText() const
{
	if (MyHud)
	{
		MyHud->MyUserWidget->UpdateKilledEnemyText(KilledEnemyCount);
	}
}

void AMyCharacter::StartRun()
{
	TempMaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	GetCharacterMovement()->MaxWalkSpeed = TempMaxWalkSpeed + (TempMaxWalkSpeed / 100 * 30);
}

void AMyCharacter::StopRun()
{
	GetCharacterMovement()->MaxWalkSpeed = TempMaxWalkSpeed;
}

void AMyCharacter::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{if(ICollectable* const Collectable = Cast<ICollectable>(OtherActor))
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue,
											 FString::Printf(
												 TEXT("OtherActor: %s"), *OtherActor->GetName()));

	Collectable->Collect();
}
}
