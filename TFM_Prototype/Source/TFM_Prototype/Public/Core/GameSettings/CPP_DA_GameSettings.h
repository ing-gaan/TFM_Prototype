#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"



#include "CPP_DA_GameSettings.generated.h"



class ACPP_Cell;
class UCPP_DA_GridSettings;
class UCPP_DA_CellType;



UCLASS()
class TFM_PROTOTYPE_API UCPP_DA_GameSettings : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid|Settings")
	const UCPP_DA_GridSettings* GridSettings{ nullptr };
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid|Locations")
	float GridDefaultHeightFromGround{ 10 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid|Locations")
	float HiddenHeightFromGround{ -100 };




	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General|Timers", 
		meta = (ToolTip = "", ClampMin = 0, ForceUnits = "Seconds"))
	float StartCellsManagerAfter{ 1 };



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cells|Locations")
	float CellsDefaultHeightFromGround{ 10 };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Cells|Types")
	TSubclassOf<ACPP_Cell> FirstCellBPClass{ nullptr };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Cells|Types")
	const UCPP_DA_CellType* FirstCellType{ nullptr };


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cells|Properties|Multipliers")
	float MaxCellsBornTimeMultiplier{ 1 };
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cells|Properties|Multipliers")
	float MaxCellsYouthTimeMultiplier{ 1 };
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cells|Properties|Multipliers")
	float MaxCellsOldAgeTimeMultiplier{ 1 };
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cells|Properties|Multipliers")
	float MaxCellsDyingTimeMultiplier{ 1 };
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cells|Properties|Multipliers")
	float MaxCellsDeadTimeMultiplier{ 1 };
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cells|Properties|Multipliers")
	float MaxCellsEnergyMultiplier{ 1 };



	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Cells|Properties|Life",
		meta = (ToolTip = "", ClampMin = 0, ForceUnits = "Seconds"))
	int LifeStateTimeStep{ 1 };



	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Cells|Properties|Life",
		meta = (ToolTip = "", ClampMin = 0, ForceUnits = "Seconds"))
	int EnergyTimeStep{ 1 };



	
};
