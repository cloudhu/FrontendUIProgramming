// CloudHu:604746493@qq.com All Rights Reserved


#include "Subsystems/FrontendUISubsystem.h"

#include "Engine/AssetManager.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "Widgets/Widget_ActivatableBase.h"
#include "Widgets/Widget_PrimaryLayout.h"

UFrontendUISubsystem* UFrontendUISubsystem::Get(const UObject* WorldContextObject)
{
	if (GEngine)
	{
		if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert))
		{
			return UGameInstance::GetSubsystem<UFrontendUISubsystem>(World->GetGameInstance());
		}
	}
	UE_LOG(LogTemp, Error, TEXT("Can not Found Subsystem<UFrontendUISubsystem>"));
	return nullptr;
}

bool UFrontendUISubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	//Make sure there's only one instance of UFrontendUISubsystem
	if (!CastChecked<UGameInstance>(Outer)->IsDedicatedServerInstance())
	{
		TArray<UClass*> FoundClasses;
		GetDerivedClasses(GetClass(), FoundClasses);

		return FoundClasses.IsEmpty();
	}
	return false;
}

void UFrontendUISubsystem::RegisterCreatedPrimaryLayout(UWidget_PrimaryLayout* InCreatedWidgetLayout)
{
	check(InCreatedWidgetLayout);
	CreatedPrimaryLayout = InCreatedWidgetLayout;
}

void UFrontendUISubsystem::PushSoftWidgetToStackAsync(const FGameplayTag& InWidgetStackTag, TSoftClassPtr<UWidget_ActivatableBase> InSoftWidgetClass,
                                                      TFunction<void(EAsyncPushWidgetState, UWidget_ActivatableBase*)> AsyncPushStateCallback) const
{
	check(!InSoftWidgetClass.IsNull())

	UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
		InSoftWidgetClass.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this,InSoftWidgetClass,InWidgetStackTag,AsyncPushStateCallback]()
			{
				UClass* LoadedWidgetClass = InSoftWidgetClass.Get();
				check(LoadedWidgetClass && CreatedPrimaryLayout);
				UCommonActivatableWidgetContainerBase* FoundWidgetStack = CreatedPrimaryLayout->FindWidgetStack(InWidgetStackTag);
				UWidget_ActivatableBase* CreatedWidget = FoundWidgetStack->AddWidget<UWidget_ActivatableBase>(
					LoadedWidgetClass,
					[AsyncPushStateCallback](UWidget_ActivatableBase& CreatedWidgetInstance)
					{
						AsyncPushStateCallback(EAsyncPushWidgetState::OnCreatedBeforePush, &CreatedWidgetInstance);
					}
				);

				AsyncPushStateCallback(EAsyncPushWidgetState::AfterPush, CreatedWidget);
			}
		)
	);
}
