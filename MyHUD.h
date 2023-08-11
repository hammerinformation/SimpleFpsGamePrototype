// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyUserWidget.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"


UCLASS()
class FPSGAME_API AMyHUD : public AHUD
{
	GENERATED_BODY()
protected:

	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> InteractionWidget;


	UMyUserWidget* MyUserWidget;
};
