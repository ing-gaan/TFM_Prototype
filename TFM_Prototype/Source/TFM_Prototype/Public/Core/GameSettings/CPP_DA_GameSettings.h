#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"



#include "CPP_DA_GameSettings.generated.h"



class ACPP_Cell;
class UCPP_DA_GridSettings;
class UCPP_DA_CameraSettings;
class UCPP_DA_CellType;



UCLASS()
class TFM_PROTOTYPE_API UCPP_DA_GameSettings : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Main|Settings|Grid")
	const UCPP_DA_GridSettings* GridSettings{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Main|Settings|Camera")
	const UCPP_DA_CameraSettings* CameraSettings { nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Main|Settings|Texts")
	const UStringTable* GameTextsStringTable;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General|Timers",
		meta = (ToolTip = "", ClampMin = 0, ForceUnits = "Seconds"))
	float StartCellsManagerAfter{ 1 };


	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "BeginPlay|Defaults|Cells",
		meta = (ToolTip = "", ClampMin = 0, ForceUnits = "cm/s"))
	float BaseOrganismMoveSpeed{ 500 };
	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "BeginPlay|Defaults|Cells",
		meta = (ToolTip = "", ClampMin = 0, ForceUnits = "dg/s"))
	float BaseRotationSpeed{ 1 };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "BeginPlay|Defaults|Cells",
		meta = (ToolTip = "", ClampMin = 0, Units = "Percent"))
	int FirstCellInitEnergy{ 50 };



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cells|Locations")
	float CellsDefaultHeightFromGround{ 10 };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Cells|Types")
	TSoftClassPtr<ACPP_Cell> FirstCellBPClass{ nullptr };
	
	

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Cells|Types")
	TSoftObjectPtr<const UCPP_DA_CellType> FirstCellType{ nullptr };



	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Cells|Properties|Life",
		meta = (ToolTip = "", ClampMin = 0, ForceUnits = "Seconds"))
	int LifeStateTimeStep{ 1 };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Cells|Properties|Life",
		meta = (ToolTip = "", ClampMin = 0, ForceUnits = "Seconds"))
	int EnergyTimeStep{ 1 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cells|Properties|Life")
	int InitHayflickLimit{ 3 };



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cells|Properties|Multipliers|Age")
	float MaxCellsBornTimeMultiplier{ 1 };
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cells|Properties|Multipliers|Age")
	float MaxCellsYouthTimeMultiplier{ 1 };
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cells|Properties|Multipliers|Age")
	float MaxCellsOldAgeTimeMultiplier{ 1 };
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cells|Properties|Multipliers|Age")
	float MaxCellsDyingTimeMultiplier{ 1 };
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cells|Properties|Multipliers|Age")
	float MaxCellsDeadTimeMultiplier{ 1 };
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cells|Properties|Multipliers|Age")
	float MaxCellsEnergyMultiplier{ 1 };


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cells|Properties|Multipliers|Energy")
	float StoppedEnergyConsumptionMultiplier{ 1 };
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cells|Properties|Multipliers|Energy")
	float MovingEnergyConsumptionMultiplier{ 1.1 };
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cells|Properties|Multipliers|Energy")
	float DivisionEnergyMultiplier{ 0.5 };
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cells|Properties|Multipliers|Energy")
	float DifferentiationEnergyMultiplier{ 0.5 };



	


	
};
