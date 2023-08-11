

#include "MyUserWidget.h"

void UMyUserWidget::UpdatePlayerHealthProgressBar(const float& Value) const
{
	HealthProgressBar->SetPercent(Value/100.f);
}

void UMyUserWidget::UpdateKilledEnemyText(const int& Num)
{
	KilledEnemyText->SetText(FText::FromString(FString::Printf(TEXT("Killed Enemy: %d"), Num)));

}
