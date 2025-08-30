#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"


#include "CPP_PlayerCamera.generated.h"




class UCPP_DA_GridSettings;
class UCPP_DA_GameSettings;
class UCPP_DA_CameraSettings;
class USpringArmComponent;
class UCameraComponent;
class ACPP_Player;




UCLASS()
class TFM_PROTOTYPE_API ACPP_PlayerCamera : public ACameraActor
{
	GENERATED_BODY()


public:
	ACPP_PlayerCamera();



public:/*Properties*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	const UCPP_DA_CameraSettings* CameraSettings {nullptr};


public:/*Functions*/

	UFUNCTION(BlueprintCallable)
	void SetZoomDirection(int ZoomDirection);

	UFUNCTION(BlueprintCallable)
	void SetPANDirection(FVector2f PANDirection);


protected:/*Properties*/

	UPROPERTY()
	const UCPP_DA_GameSettings* GameSettings {nullptr};

	UPROPERTY()
	USpringArmComponent* CameraSpringArm;

	UPROPERTY()
	UCameraComponent* PlayerCamera;

	UPROPERTY()
	APawn* PlayerPawn;


	float CurrentZoom{ 0.0f };
	float CurrentZoom2{ 0.0f };
	int Zoom{ 0 };
	float LerpAlpha{ 0.0f };
	FVector2f LastPlayerLocation{ FVector2f::Zero() };
	FVector2f PANMovement{ FVector2f(0, 0) };
	FVector LocationChange{ FVector::Zero() };


protected:/*Functions*/



	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void InitActor();
	void InitCamera();
	void UpdateCamera(float DeltaTime);
	bool IsPlayerMoving();

	
};
