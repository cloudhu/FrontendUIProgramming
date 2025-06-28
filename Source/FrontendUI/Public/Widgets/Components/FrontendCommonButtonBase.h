// CloudHu:604746493@qq.com All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "FrontendCommonButtonBase.generated.h"

class UCommonTextBlock;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta=(DisableNativeTick))
class FRONTENDUI_API UFrontendCommonButtonBase : public UCommonButtonBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetButtonText(FText InButtonText);
	
protected:
#pragma region OverrideFunctions

	virtual void NativePreConstruct() override;
	virtual void NativeOnCurrentTextStyleChanged() override;
#pragma endregion

private:
#pragma region Bound Widgets

	UPROPERTY(meta=(BindWidgetOptional))
	UCommonTextBlock* CommonTextBlock_ButtonText;

#pragma endregion

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Frontend Button", meta=(AllowPrivateAccess=true))
	FText ButtonDisplayText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Frontend Button", meta=(AllowPrivateAccess=true))
	bool bUseUpperCaseForButtonText = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Frontend Button", meta=(AllowPrivateAccess=true))
	FText ButtonDescriptionText;
};
