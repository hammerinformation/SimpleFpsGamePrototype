

#include "PickUpComponent.h"

#include "Collectable.h"
#include "MyCharacter.h"
#include "Components/CapsuleComponent.h"

UPickUpComponent::UPickUpComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	
}


void UPickUpComponent::BeginPlay()
{
	Super::BeginPlay();
	

	
}



