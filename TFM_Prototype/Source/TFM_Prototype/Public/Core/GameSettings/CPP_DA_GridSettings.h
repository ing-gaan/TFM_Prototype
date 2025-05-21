#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"



#include "CPP_DA_GridSettings.generated.h"




UCLASS()
class TFM_PROTOTYPE_API UCPP_DA_GridSettings : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General settings")
	int InitGridElementsNum{ 10 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General settings")
	int NewExtraGridElementsNum{ 10 };



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map|Locations")
	float DistanceBetweenNeighbours{ 105 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map|Locations")
	FVector2f FirstAxialLocation{ FVector2f(0) };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map|Locations")
	TArray<FVector2f> InitAxialLocations;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes settings")
	TArray<double> DefaultDataValues;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes settings")
	TArray<double> CursorOverDataValues;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes settings")
	TArray<double> ClickDataValues;

	
};
