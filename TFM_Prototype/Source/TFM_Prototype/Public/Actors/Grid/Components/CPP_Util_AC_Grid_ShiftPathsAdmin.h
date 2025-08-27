#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Utils/Enums/CPPE_CellShiftState.h"


#include "CPP_Util_AC_Grid_ShiftPathsAdmin.generated.h"




class ACPP_Cell;
class UCPP_SS_LocalGameManager;
class UCPP_SS_CellsManager;
class ACPP_Grid;
enum class ECPPE_NeighbourShortName : uint8;
enum class ECPPE_CellShiftState : uint8;
class UCPP_DA_GameSettings;
class UCPP_DA_GridSettings;





USTRUCT()
struct FPathAndCost
{
	GENERATED_USTRUCT_BODY()

	int Cost{ 0 };
	TArray<ECPPE_NeighbourShortName> Path;
};


USTRUCT()
struct FShiftPathsState
{
	GENERATED_USTRUCT_BODY()

	/*Properties*/
	UPROPERTY()
	TArray<FPathAndCost> PathsAndCosts;
	UPROPERTY()
	TArray<FVector2f> CurrentPath;

	ECPPE_CellShiftState ShiftingTo{ ECPPE_CellShiftState::None };


	/*Fucntions*/
	/// Increase the index and returns the new value.
	int NextPathCostIndex();


private:/*Properties*/
	int CurrentPathCostIndex{ -1 };

};





UCLASS()
class TFM_PROTOTYPE_API UCPP_Util_AC_Grid_ShiftPathsAdmin : public UObject
{
	GENERATED_BODY()


public:/*Properties*/

	UPROPERTY()
	TMap<const ACPP_Cell*, FShiftPathsState> NeighboursShiftPathsStates;

	


public:/*Fucntions*/
	
	void Initialize(const UCPP_DA_GameSettings* GameSettings, const UCPP_SS_CellsManager* TheCellsManager, const ACPP_Grid* TheGrid);
	void Update(const ACPP_Cell* CellToDivide);
	int ChangeCellsLocations(const ACPP_Cell* FirstCellToShift);
	void ReturnAllCellsToLocations();

	void Enable();
	void Disable();
	bool IsEnable() const;

	/*
	* The first location is the neighbour´s axial location of the ClickedCell.
	* The last location is a free location,so doesn´t exists in the Playercontroller CellsMap
	*/
	FVector2f GetAxialLocOfCellsInCurrentPath(TArray<FVector2f>& OutCurrentAxialLocationsPath);




private:/*Properties*/

	/*UPROPERTY()
	const UCPP_SS_LocalGameManager* GameManager{ nullptr };*/

	UPROPERTY()
	const UCPP_SS_CellsManager* CellsManager{ nullptr };

	UPROPERTY()
	const ACPP_Grid* Grid;

	UPROPERTY()
	const ACPP_Cell* BaseCell { nullptr };

	UPROPERTY()
	const ACPP_Cell* CurrentStartCell { nullptr };

	UPROPERTY()
	const UCPP_DA_GridSettings* GridSettings { nullptr };


	bool bIsEnable{ false };
	bool bIsInitialized{ false };



private:/*Fucntions*/

	void UpdateBaseCellNeighbours();
	void GetOrdererPathsCosts(const ACPP_Cell* StartCell, TArray<FPathAndCost>& OutPathsCosts);
	void CalculatePath(const ACPP_Cell* StartCell, FVector2f EndLocation, TArray<FPathAndCost>& OutPathsCosts);
	void TurnVectorsPathInShortNamesPath(TArray<FVector2f>& VectorsPath, TArray<ECPPE_NeighbourShortName>& OutShortNamesPath);
	void TurnShortNamesPathInVectorsPath(TArray<ECPPE_NeighbourShortName>& OutShortNamesPath, TArray<FVector2f>& VectorsPath);
	bool GetAStarPath(FVector2f StartLocation, FVector2f EndLocation,
		TArray<FVector2f>& OutPath, int& OutPathCost);
	bool ChangeCurrentPath(const ACPP_Cell* Cell, int PathIndex = -1);
	void ReturnCellsToLocation(const ACPP_Cell* StartCell);
	void ClearShiftingStates();

};