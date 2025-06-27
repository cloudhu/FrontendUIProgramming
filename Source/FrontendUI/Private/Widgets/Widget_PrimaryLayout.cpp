// CloudHu:604746493@qq.com All Rights Reserved


#include "Widgets/Widget_PrimaryLayout.h"

UCommonActivatableWidgetContainerBase* UWidget_PrimaryLayout::FindWidgetStack(const FGameplayTag& InStackTag) const
{
	checkf(RegisteredWidgetStackMap.Contains(InStackTag), TEXT("Cannot find widget stack with tag %s"), *InStackTag.ToString());
	return RegisteredWidgetStackMap.FindRef(InStackTag);
}

void UWidget_PrimaryLayout::RegisterWidgetStack(UPARAM(meta=(Categories="Frontend.WidgetStack"))
                                                FGameplayTag InStackTag, UCommonActivatableWidgetContainerBase* InStack)
{
	if (!IsDesignTime())
	{
		if (!RegisteredWidgetStackMap.Contains(InStackTag))
		{
			RegisteredWidgetStackMap.Add(InStackTag, InStack);
		}
	}
}
