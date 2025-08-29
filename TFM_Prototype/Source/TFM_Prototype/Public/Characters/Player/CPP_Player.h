#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"


#include "CPP_Player.generated.h"



class UCPP_DA_GridSettings;
class UCPP_DA_GameSettings;
class UCPP_DA_CameraSettings;
class USpringArmComponent;
class UCameraComponent;



UCLASS()
class TFM_PROTOTYPE_API ACPP_Player : public APawn
{
	GENERATED_BODY()

public:	
	ACPP_Player();


public:/*Properties*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	const UCPP_DA_CameraSettings* CameraSettings{ nullptr };


public:/*Functions*/

	UFUNCTION(BlueprintCallable)
	FVector2f GetAxialLocation() const;

	UFUNCTION(BlueprintCallable)
	void SetAxialLocation(FVector2f NewAxialLocation);

	UFUNCTION(BlueprintCallable)
	FVector2D GetRelativeLocation() const;

	UFUNCTION(BlueprintCallable)
	void SetZoomDirection(int ZoomDirection);

	UFUNCTION(BlueprintCallable)
	void SetPANDirection(FVector2f PANDirection);


protected:/*Properties*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector2f AxialLocation{ FVector2f(0, 0) };

	UPROPERTY()
	FVector2D RelativeLocation{ FVector2D(0, 0) };

	UPROPERTY()
	const UCPP_DA_GridSettings* GridSettings { nullptr };

	UPROPERTY()
	const UCPP_DA_GameSettings* GameSettings { nullptr };

	UPROPERTY()
	USpringArmComponent* CameraSpringArm;

	UPROPERTY()
	UCameraComponent* PlayerCamera;



	float CurrentZoom{ 0.0f };
	float CurrentZoom2{ 0.0f };
	int Zoom{ 0 };
	float LerpAlpha{ 0.0f };
	FVector LastPlayerLocation{ FVector::Zero()};
	FVector2f PANMovement{ FVector2f(0, 0) };
	FVector LocationChange{ FVector::Zero() };


protected:/*Functions*/



	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void InitPlayer();
	void InitCamera();
	void UpdateCamera(float DeltaTime);
	bool IsPlayerMoving();
	

};
