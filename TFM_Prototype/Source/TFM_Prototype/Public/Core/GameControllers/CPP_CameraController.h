#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"


#include "CPP_CameraController.generated.h"



class UCPP_DA_CameraSettings;
class ACPP_Player;




UCLASS()
class TFM_PROTOTYPE_API ACPP_CameraController : public APlayerCameraManager
{
	GENERATED_BODY()


public:


public:/*Properties*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCPP_DA_CameraSettings* CameraSettings{ nullptr };

	UPROPERTY()
	ACPP_Player* Player{ nullptr };


public:/*Functions*/

	UFUNCTION(BlueprintCallable)
	void SetZoomDirection(int ZoomDirection);



protected:/*Properties*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int CameraZoom{ 0 };



protected:/*Functions*/

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void UpdateViewTargetInternal(FTViewTarget& OutVT, float DeltaTime) override;


};
