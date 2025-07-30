#include "Actors/Grid/Components/CPP_Util_AC_Grid_ShiftPathsAdmin.h"
#include "Utils/FunctionLibraries/CPP_FuncLib_AStarSearch.h"
#include "Utils/FunctionLibraries/CPP_FuncLib_CellUtils.h"
#include "Core/GameSettings/CPP_DA_GridSettings.h"
#include "Core/GameSettings/CPP_DA_GameSettings.h"
#include "Actors/Cell/CPP_Cell.h"
#include "Actors/Cell/CPP_DA_CellType.h"
#include "Utils/Enums/CPP_NeighbourShortName.h"
#include "Core/Subsystems/Managers/CPP_SS_CellsManager.h"
#include "Actors/Grid/CPP_Grid.h"
#include "Utils/Macros/Macros.h"





/*
* This class is responsible for generating a movement route when a cell is to be
* duplicated in a location occupied by another. Then, it finds the different routes
* where the cells can move and tells each cell where it should move.
* In addition, it programs a timer that when it reaches a time limit tells
* the cell that it must return to its point of origin.
*/



/// Increase the index and returns the new value.
int FShiftPathsState::NextPathCostIndex()
{
	if (CurrentPathCostIndex >= PathsAndCosts.Num() - 1)
	{
		CurrentPathCostIndex = 0;
	}
	else
	{
		CurrentPathCostIndex++;
	}
	return CurrentPathCostIndex;
}




void UCPP_Util_AC_Grid_ShiftPathsAdmin::Initialize(const UCPP_DA_GameSettings* GameSettings, const UCPP_SS_CellsManager* TheCellsManager, const ACPP_Grid* TheGrid)
{
	GridSettings = GameSettings->GridSettings;
	
	/*APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	checkf(PlayerController, TEXT("***> No PlayerController (nullptr) <***"));*/

	/*GameManager = PlayerController->GetLocalPlayer()->GetSubsystem<UCPP_SS_LocalGameManager>();
	checkf(GameManager, TEXT("***> No CellsManager (nullptr) <***"));*/

	CellsManager = TheCellsManager;
	Grid = TheGrid;

	bIsInitialized = true;
	NeighboursShiftPathsStates.Empty();
}



/*
* Save all paths from a neighbour of the ClickedCell to an empty location (a grid location).
* Therefore, the last location doesn´t exists in the Playercontroller CellsMap
*/
void UCPP_Util_AC_Grid_ShiftPathsAdmin::Update(const ACPP_Cell* CellToDivide)
{
	checkf(bIsInitialized, TEXT("***> The ShiftPathsAdmin has not been initialized. Call UCPP_Util_AC_Grid_ShiftPathsAdmin::Initialize() first <***"));

	if (BaseCell != CellToDivide)
	{
		ClearShiftingStates();
		BaseCell = CellToDivide;
		if (!BaseCell)
		{
			return;
		}
	}

	/*ClearShiftingStates();
	BaseCell = CellToDivide;*/
	if (!BaseCell)
	{
		return;
	}

	UpdateBaseCellNeighbours();

	for (auto& Elem : NeighboursShiftPathsStates)
	{
		GetOrdererPathsCosts(Elem.Key, Elem.Value.PathsAndCosts);
	}
}



void UCPP_Util_AC_Grid_ShiftPathsAdmin::UpdateBaseCellNeighbours()
{
	FVector2f NeighbourLocation;

	for (auto& AxialLocat : GridSettings->InitAxialLocations)
	{
		NeighbourLocation = BaseCell->GetAxialLocation() + AxialLocat;
		const ACPP_Cell* NeighbourCell = CellsManager->GetCellInMap(NeighbourLocation);
		bool bIsAlreadyIncluded = NeighboursShiftPathsStates.Contains(NeighbourCell);

		if (!NeighbourCell || bIsAlreadyIncluded)
		{			
			continue;
		}
		
		FShiftPathsState ShiftPathsState;
		NeighboursShiftPathsStates.Emplace(NeighbourCell, ShiftPathsState);
	}
}



/// Get the cost of the all paths of one neighbour.
void UCPP_Util_AC_Grid_ShiftPathsAdmin::GetOrdererPathsCosts(const ACPP_Cell* StartCell, TArray<FPathAndCost>& OutPathsCosts)
{
	OutPathsCosts.Empty();
	const TSet<FVector2f>* FreeNeighbours = Grid->GetAllFreeNeighbours();
	for (auto& EndLocation : *FreeNeighbours)
	{
		CalculatePath(StartCell, EndLocation, OutPathsCosts);
	}
	OutPathsCosts.StableSort([](FPathAndCost A, FPathAndCost B) { return A.Cost < B.Cost; });
}



void UCPP_Util_AC_Grid_ShiftPathsAdmin::CalculatePath(const ACPP_Cell* StartCell, FVector2f EndLocation, TArray<FPathAndCost>& OutPathsCosts)
{
	TArray<FVector2f> CalculatedPath;
	int PathCost;
	FVector2f StartLocation = StartCell->GetAxialLocation();

	bool bHasPath = GetAStarPath(StartLocation, EndLocation, CalculatedPath, PathCost);
	if (!bHasPath)
	{
		return;
	}

	int StartCellShiftCost = StartCell->CellType->ShiftLocationCost;
	PathCost = PathCost + StartCellShiftCost;

	FPathAndCost PathAndCost;
	PathAndCost.Cost = PathCost;

	TurnVectorsPathInShortNamesPath(CalculatedPath, PathAndCost.Path);
	OutPathsCosts.Emplace(PathAndCost);
}



bool UCPP_Util_AC_Grid_ShiftPathsAdmin::GetAStarPath(FVector2f StartLocation, FVector2f EndLocation,
	TArray<FVector2f>& OutPath, int& OutPathCost)
{
	bool bHasPath = UCPP_FuncLib_AStarSearch::CalculatePath(CellsManager->GetCellsMap(),
		&(GridSettings->InitAxialLocations), StartLocation, EndLocation, OutPath, OutPathCost);

	return bHasPath;
}


/*
* @Return The number of cells shiftings
*/
int UCPP_Util_AC_Grid_ShiftPathsAdmin::ChangeCellsLocations(const ACPP_Cell* FirstCellToShift)
{
	CurrentStartCell = FirstCellToShift;
	FShiftPathsState* CellShiftingState = NeighboursShiftPathsStates.Find(FirstCellToShift);

	if (!CellShiftingState)
	{
		return 0;
	}

	//if (CellShiftingState->bAreShiftingLocations)
	if (CellShiftingState->ShiftingTo == ECPP_CellShiftState::ShiftingToTemp)
	{
		return 0;
	}

	if (!ChangeCurrentPath(FirstCellToShift))
	{
		return 0;
	}

	TArray<FVector2f>& CurrentPath = CellShiftingState->CurrentPath;
	const ACPP_Cell* CellInPath;

	/// At init -> shift the last cell to the empty location (last in CurrentPath) 
	/// At end -> shift the START cell to the next location (second in CurrentPath)
	/// Therefore, the last location doesn't exists in the Playercontroller CellsMap
	for (int i = CurrentPath.Num() - 1; i > 0; i--)
	{
		CellInPath = CellsManager->GetCellInMap(CurrentPath[i - 1]);
		CellInPath->ShiftAxialLocation(CurrentPath[i]);	
	}
	CellShiftingState->ShiftingTo = ECPP_CellShiftState::ShiftingToTemp;

	return CurrentPath.Num();
}


bool UCPP_Util_AC_Grid_ShiftPathsAdmin::ChangeCurrentPath(const ACPP_Cell* Cell, int PathIndex)
{
	FShiftPathsState& CellShiftingState = NeighboursShiftPathsStates[Cell];
	TArray<FPathAndCost>& PathsAndCosts = CellShiftingState.PathsAndCosts;
	TArray<FVector2f>& CurrentPath = CellShiftingState.CurrentPath;

	if (PathsAndCosts.IsEmpty())
	{
		return false;
	}
	else if (PathsAndCosts.Num() == 1)
	{
		if (!CurrentPath.IsEmpty())
		{
			return true;
		}
	}

	CurrentPath.Empty();
	if (PathIndex < 0)
	{
		PathIndex = CellShiftingState.NextPathCostIndex();
	}

	TurnShortNamesPathInVectorsPath(PathsAndCosts[PathIndex].Path, CurrentPath);

	return CurrentPath.Num() != 0;
}


void UCPP_Util_AC_Grid_ShiftPathsAdmin::TurnVectorsPathInShortNamesPath(TArray<FVector2f>& VectorsPath, TArray<ECPP_NeighbourShortName>& OutShortNamesPath)
{
	FVector2f BasicAxialLoc;
	int i = 0;

	BasicAxialLoc = VectorsPath[i] - BaseCell->GetAxialLocation();
	OutShortNamesPath.Add(UCPP_FuncLib_CellUtils::GetNeighbourShortName(BasicAxialLoc));
	i++;

	while (i < VectorsPath.Num())
	{
		BasicAxialLoc = VectorsPath[i] - VectorsPath[i - 1];
		OutShortNamesPath.Emplace(UCPP_FuncLib_CellUtils::GetNeighbourShortName(BasicAxialLoc));
		i++;
	}
}


void UCPP_Util_AC_Grid_ShiftPathsAdmin::TurnShortNamesPathInVectorsPath(TArray<ECPP_NeighbourShortName>& ShortNamesPath, TArray<FVector2f>& OutVectorsPath)
{
	FVector2f AddedAxialLoc;
	int i = 0;

	AddedAxialLoc = BaseCell->GetAxialLocation() + UCPP_FuncLib_CellUtils::GetAxialLocationByShortName(ShortNamesPath[i]);
	OutVectorsPath.Insert(AddedAxialLoc, i);
	i++;

	while (i < ShortNamesPath.Num())
	{
		AddedAxialLoc = OutVectorsPath[i - 1] + UCPP_FuncLib_CellUtils::GetAxialLocationByShortName(ShortNamesPath[i]);
		OutVectorsPath.Emplace(AddedAxialLoc);
		i++;
	}
}


//void UCPP_CellShiftingStates::ATimerHasFinished(const ACPP_Cell* StartCell)
//{
//	//PRINT("SE CUMPLIO EL TIEMPO (UCPP_CellShiftingStates)");
//	ReturnCellsToLocation(StartCell);
//}


void UCPP_Util_AC_Grid_ShiftPathsAdmin::ReturnAllCellsToLocations()
{
	for (auto& Elem : NeighboursShiftPathsStates)
	{
		ReturnCellsToLocation(Elem.Key);
	}
}


void UCPP_Util_AC_Grid_ShiftPathsAdmin::ReturnCellsToLocation(const ACPP_Cell* StartCell)
{
	FShiftPathsState& CellShiftingState = NeighboursShiftPathsStates[StartCell];

	//if (CellShiftingState.bAreInOriginalLocation)
	if (CellShiftingState.ShiftingTo == ECPP_CellShiftState::ShiftingToOrigin)
	{
		return;
	}

	TArray<FVector2f>& CurrentPath = CellShiftingState.CurrentPath;
	for (int i = 0; i < CurrentPath.Num() - 1; i++)
	{
		const ACPP_Cell* CellInPath;
		CellInPath = CellsManager->GetCellInMap(CurrentPath[i]);
		if (CellInPath)
		{
			CellInPath->ReturnToOriginAxialLocation();
		}		
	}

	/*CellShiftingState.bAreInOriginalLocation = true;
	CellShiftingState.bAreShiftingLocations = false;*/
	CellShiftingState.ShiftingTo = ECPP_CellShiftState::ShiftingToOrigin;
}



void UCPP_Util_AC_Grid_ShiftPathsAdmin::Enable()
{
	bIsEnable = true;
}


void UCPP_Util_AC_Grid_ShiftPathsAdmin::Disable()
{
	bIsEnable = false;
	ReturnAllCellsToLocations();
	ClearShiftingStates();
}


bool UCPP_Util_AC_Grid_ShiftPathsAdmin::IsEnable() const
{
	return bIsEnable;
}



/*
* The first location is the neighbour's axial location of the ClickedCell.
* The last location is a free location (free Neighbour),so doesn't exists in the Playercontroller CellsMap
* @Return The last location.
*/
FVector2f UCPP_Util_AC_Grid_ShiftPathsAdmin::GetAxialLocOfCellsInCurrentPath(TArray<FVector2f>& OutCurrentAxialLocationsPath)
{
	OutCurrentAxialLocationsPath.Empty();
	FShiftPathsState& CellShiftingState = NeighboursShiftPathsStates[CurrentStartCell];
	TArray<FVector2f>& CurrentPath = CellShiftingState.CurrentPath;

	/// The last location is a free location,so doesn't exists in the Playercontroller CellsMap.
	/// Therefore, it's not taken in account.	
	for (int i = 0; i < CurrentPath.Num() - 1; i++)
	{
		OutCurrentAxialLocationsPath.Emplace(CurrentPath[i]);
	}
	//PRINT("OUTPATH NUM = %d (UCPP_CellShiftingStates)", OutCurrentAxialLocationsPath.Num());
	return CurrentPath.Last();
}



void UCPP_Util_AC_Grid_ShiftPathsAdmin::ClearShiftingStates()
{
	if (NeighboursShiftPathsStates.IsEmpty())
	{
		return;
	}

	NeighboursShiftPathsStates.Empty();
	BaseCell = nullptr;
	//CellsManager = nullptr;
	//Grid = nullptr;
}

