#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CPP_DA_CellType.generated.h"



class UCPP_AC_Cell_Base;



UCLASS()
class TFM_PROTOTYPE_API UCPP_DA_CellType : public UPrimaryDataAsset
{
	GENERATED_BODY()


public:/*Properties*/


	/**************************************** CELL COLORS ****************************************/

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Basics")
	UStaticMesh* CellStaticMesh{ nullptr };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Colors")
	FLinearColor NormalColor { FLinearColor::White };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Colors")
	FLinearColor CursorOverColor{ FLinearColor::White };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Colors")
	FLinearColor ClickedColor{ FLinearColor::White };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Colors")
	FLinearColor NotInteractiveColor{ FLinearColor::White };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Colors")
	FLinearColor ShiftingColor{ FLinearColor::White };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Materials")
	UMaterial* CellNormalMaterial { nullptr };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Materials")
	FName MaterialColorParameterName { };





	/**************************************** CELL COMPONENTS ****************************************/

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Properties|Necessary actor components")
	TSet<TSubclassOf<UCPP_AC_Cell_Base>> NecessaryCellComponents;





	/**************************************** CELL SHIF PROPERTIES ****************************************/

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Shifting location costs")
	bool bCanShiftLocation{ true };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Shifting location costs",
		meta = (EditCondition = "bCanShiftLocation"))
	int ShiftLocationCost{ 10 };
	




	/**************************************** CELL LIFE PROPERTIES ****************************************/

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Properties|Life",
		meta = (ToolTip = "", ClampMin = 0, ForceUnits = "Seconds"))
	int MaxBornTime{ 10 };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Properties|Life",
		meta = (ToolTip = "", ClampMin = 0, ForceUnits = "Seconds"))
	int MaxYouthTime{ 80 };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Properties|Life",
		meta = (ToolTip = "", ClampMin = 0, ForceUnits = "Seconds"))
	int MaxOldAgeTime{ 20 };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Properties|Life",
		meta = (ToolTip = "", ClampMin = 0, ForceUnits = "Seconds"))
	int MaxDyingTime{ 10 };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Properties|Life",
		meta = (ToolTip = "", ClampMin = 0, ForceUnits = "Seconds"))
	int MaxDeadTime{ 10 };
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Properties|Life",
		meta = (ToolTip = "Amount of decrease for each time step", ClampMin = 0))
	int LifeStateTimeDecreaseRate{ 1 };





	/**************************************** CELL ENERGY ****************************************/

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Properties|Energy",
		meta = (ToolTip = "", ClampMin = 0, Units = "Percent"))
	int MaxEnergy{ 100 };
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Properties|Energy",
		meta = (ToolTip = "Amount of decrease for each time step", ClampMin = 0))
	int EnergyDecreaseRate{ 1 };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Properties|Energy")
	bool bCanTransferEnergy{ false };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Properties|Energy",
		meta = (EditCondition = "bCanTransferEnergy", ClampMin = 0, ClampMax = 100, Units = "Percent"))
	int EnergyTransferCapacity{ 100 };










	
};
