#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
//#include "Utils/Enums/CPPE_MoleculeType.h"


#include "CPP_DA_CellType.generated.h"



class UCPP_AC_Cell_Base;
enum class ECPPE_MoleculeType : uint8;




UCLASS()
class TFM_PROTOTYPE_API UCPP_DA_CellType : public UPrimaryDataAsset
{
	GENERATED_BODY()


public:/*Properties*/

	/**************************************** CELL DATA ****************************************/

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Data")
	FText CellTypeName;


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
		meta = (ToolTip = "", ClampMin = 0))
	float MaxEnergy{ 100 };

	/// Amount of energy consumption for each time step. Time step is in GameSettings/Cells/Properties/Life/LifeStateTimeStep
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Properties|Energy",
		meta = (ToolTip = "Amount of energy consumption for each time step. Time step is in GameSettings/Cells/Properties/Life/LifeStateTimeStep", 
			ClampMin = 0))
	float EnergyConsumptionRate{ 1 };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Properties|Energy")
	bool bCanAccumulateEnergy{ false };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Properties|Energy",
		meta = (EditCondition = "bCanAccumulateEnergy"))
	float AccumulationCapacity{ 0.0 };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Properties|Energy")
	bool bCanTransferEnergyByItSelf{ false };

	/// Energy for subsistence. Cannot be transferred.
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Properties|Energy",
		meta = (EditCondition = "bCanTransferEnergyByItSelf", ToolTip = "Energy for subsistence. Cannot be transferred."))
	float SubsistenceEnergy{ 10 };

	/// Maximum distance at which it can transfer (e.g. 1 the 6 neighbors that surround it)
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Properties|Energy",
		meta = (EditCondition = "bCanTransferEnergyByItSelf", ToolTip = "Maximum distance at which it can transfer (e.g. 1 the 6 neighbors that surround it)"))
	int TransferRange{ 3 };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Properties|Energy",
		meta = (EditCondition = "bCanTransferEnergyByItSelf", ForceUnits = "Seconds"))
	float TransferEnergyTimeInterval{ 2 };



	
	/**************************************** CELL MOVEMENT ****************************************/

	/// This value is averaged with the others
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Properties|Movement",
		meta = (ToolTip = "This value is averaged with the speeds of the others"))
	float MovementSpeedMultiplier{ 1 };

	/// This value is averaged with the others
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Properties|Movement",
		meta = (ToolTip = "This value is averaged with the speeds of the others"))
	float RotationSpeedMultiplier{ 1 };




	/**************************************** CELL DIGESTION ****************************************/

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Properties|Digestion")
	bool bCanDigestByItSelf{ false };

	/*/// The maximum size of molecule that it can digest
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Properties|Energy",
		meta = (EditCondition = "bCanDigestByItSelf", ToolTip = "The maximum size of molecule that it can digest"))
	float DigestionCapacity{ 10 };*/

	/// Types of molecules that it can digest
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Properties|Digestion",
		meta = (ToolTip = "Types of molecules that it can digest"))
	TSet<ECPPE_MoleculeType> MoleculesCanBeDigested;

	
};
