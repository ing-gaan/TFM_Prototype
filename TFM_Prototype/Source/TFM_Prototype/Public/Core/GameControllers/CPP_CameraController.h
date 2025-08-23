#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"


#include "CPP_CameraController.generated.h"




class UCPP_DA_GameSettings;
class UCPP_DA_CameraSettings;
class ACPP_Player;




UCLASS()
class TFM_PROTOTYPE_API ACPP_CameraController : public APlayerCameraManager
{
	GENERATED_BODY()


public:


public:/*Properties*/

	UPROPERTY()
	const UCPP_DA_GameSettings* GameSettings { nullptr };


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	const UCPP_DA_CameraSettings* CameraSettings{ nullptr };

	UPROPERTY()
	ACPP_Player* Player{ nullptr };


public:/*Functions*/

	UFUNCTION(BlueprintCallable)
	void SetZoomDirection(int ZoomDirection);

	UFUNCTION(BlueprintCallable)
	void SetPANDirection(FVector2f PANDirection);



protected:/*Properties*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int OrthoWidth{ 0 };

	bool bIsInitialized{ false };

	FVector2f LastPlayerLocation{ FVector2f(0, 0) };
	FVector2f PANMovement{ FVector2f(0, 0) };

	float LerpAlpha{ 0.0f };

	float CurrentOrthoWidth{ 0.0f };
	float CurrentOrthoWidth2{ 0.0f };

protected:/*Functions*/

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void InitCameraController();
	virtual void UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime) override;

	bool IsPlayerMoving();

};
