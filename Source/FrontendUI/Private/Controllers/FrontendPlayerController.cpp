// CloudHu:604746493@qq.com All Rights Reserved


#include "Controllers/FrontendPlayerController.h"

#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"

void AFrontendPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	TArray<AActor*> FoundCameras;
	//Find default camera component
	UGameplayStatics::GetAllActorsOfClassWithTag(this, ACameraActor::StaticClass(), FName("DefaultCamera"), FoundCameras);
	if (FoundCameras.Num() > 0)
	{
		SetViewTarget(FoundCameras[0]);
	}
}
