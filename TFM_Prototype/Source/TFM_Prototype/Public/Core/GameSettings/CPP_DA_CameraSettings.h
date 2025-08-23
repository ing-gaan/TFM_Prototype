#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"


#include "CPP_DA_CameraSettings.generated.h"




UCLASS()
class TFM_PROTOTYPE_API UCPP_DA_CameraSettings : public UPrimaryDataAsset
{
	GENERATED_BODY()


public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General|Properties")
	bool bIsOrthographic{ true };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General|Properties")
	float AspectRatio{ 1.777778 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General|Properties")
	float FOV{ 90 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General|Properties")
	FVector2D OffsetFromPlayer{ FVector2D(0, 0) };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General|Properties")
	int OrthoWidthChangeStep{ 100 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General|Properties")
	int OrthoWidthChangeStepSpeed{ 2 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General|Properties")
	int MinOrthoWidth{ 1000 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General|Properties")
	int DefaultOrthoWidth{ 3000 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General|Properties")
	int MaxOrthoWidth{ 10000 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General|Properties")
	FRotator CameraRotation{ FRotator(0, -90, 0)};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General|Properties")
	float RotationInterpSpeed{ 0 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General|Properties")
	float MovementInterpSpeed{ 0 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General|Properties")
	int PANMovementMultiplier{ 200 };

	

	






};
