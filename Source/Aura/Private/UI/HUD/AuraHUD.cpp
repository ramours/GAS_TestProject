


#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"

#include "Blueprint/UserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"


UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
	}
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAuraAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class Uninitialized, please fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class Uninitialized, please fill out BP_AuraHUD"));
	
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);

	OverlayWidget = Cast<UAuraUserWidget>(Widget);
	const FWidgetControllerParams WCParams(PC, PS, ASC, AS);
	OverlayWidget->SetWidgetController(GetOverlayWidgetController(WCParams));

	OverlayWidgetController->BindCallbacksToDependencies();
	OverlayWidgetController->BroadcastInitialValues();
	
	Widget->AddToViewport();
}
