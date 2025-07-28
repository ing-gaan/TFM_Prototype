#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"



#include "CPP_DA_GridSettings.generated.h"




UCLASS()
class TFM_PROTOTYPE_API UCPP_DA_GridSettings : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General|Settings")
	int InitGridElementsNum{ 10 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General|Settings")
	int NewExtraGridElementsNum{ 10 };



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map|Locations")
	float DistanceBetweenNeighbours{ 105 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map|Locations")
	FVector2f FirstAxialLocation{ FVector2f(0) };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map|Locations")
	TArray<FVector2f> InitAxialLocations;



	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeshInstances|Settings")
	TArray<double> DefaultDataValues;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeshInstances|Settings")
	TArray<double> CursorOverDataValues;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeshInstances|Settings")
	TArray<double> ClickDataValues;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeshInstances|Material data values")
	int MaterialDataValuesNumber{ 4 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeshInstances|Material data values")
	FLinearColor DefaultColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeshInstances|Material data values")
	FLinearColor CursorOverColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeshInstances|Material data values")
	FLinearColor ClickedColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeshInstances|Material data values")
	FLinearColor NotInteractiveColor;



	/*UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "AuxiliaryElement|Materials")
	UMaterial* AuxElemMaterial{ nullptr };*/

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "AuxiliaryElement|Materials")
	FName AuxElemMaterialColorParamName{ };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "AuxiliaryElement|Colors")
	FLinearColor AuxElemNormalColor{ FLinearColor::White };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "AuxiliaryElement|Colors")
	FLinearColor AuxElemCursorOverColor{ FLinearColor::White };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "AuxiliaryElement|Colors")
	FLinearColor AuxElemClickedColor{ FLinearColor::White };
};
