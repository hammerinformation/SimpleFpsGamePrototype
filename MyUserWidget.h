
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "MyUserWidget.generated.h"


UCLASS()
class FPSGAME_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
	UProgressBar* HealthProgressBar{};
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
	UTextBlock* KilledEnemyText{};
	void UpdatePlayerHealthProgressBar(const float& Value) const;

	void UpdateKilledEnemyText(const int& Num);
};
