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
	FVector2D OffsetFromPlayer{ FVector2D(0, 0) };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General|Properties")
	int ZoomStep{ 100 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General|Properties")
	int ZeroZoom{ 2000 };
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General|Properties")
	int MinZoom{ 500 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General|Properties")
	int MaxZoom{ 5000 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General|Properties")
	FRotator CameraRotation{ FRotator(0, -90, 0)};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General|Properties")
	float RotationInterpSpeed{ 0 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General|Properties")
	float MovementInterpSpeed{ 0 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General|Properties")
	float FOV{ 90 };

	






};
