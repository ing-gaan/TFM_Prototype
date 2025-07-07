#include "Utils/FunctionLibraries/CPP_FuncLib_AStarSearch.h"
#include "Utils/FunctionLibraries/CPP_FuncLib_CellUtils.h"
#include "Actors/Cell/CPP_Cell.h"
#include "Actors/Cell/CPP_DA_CellType.h"
#include "Actors/Cell/StateMachines/LifeSM/CPP_SM_Cell_LifeSt_OldAge.h"






FASearchNode::FASearchNode() :
	G{ 0 }, H{ 0 }, ParentLocation{ FVector2f(0, 0) }, AxialLocation{ FVector2f(0, 0) }
{
	F = G + H;
}



FASearchNode::FASearchNode(int G, int H, FVector2f ParentLocation, FVector2f AxialLocation) :
	G{ G }, H{ H }, ParentLocation{ ParentLocation }, AxialLocation{ AxialLocation }
{
	F = G + H;
}



bool UCPP_FuncLib_AStarSearch::CalculatePath(const TMap<FVector2f, const ACPP_Cell*>* CellsMap, const TArray<FVector2f>* InitAxialLocations,
	FVector2f StartAxialLocation, FVector2f EndAxialLocation, TArray<FVector2f>& OutPath, int& OutPathCost)
{
	Init(StartAxialLocation, EndAxialLocation, OutPath);

	if (!WouldThereBeValidPath(CellsMap, InitAxialLocations))
	{
		return false;
	}

	FASearchNode ChosenNode;
	ChosenNode = FASearchNode(0, 0, FVector2f(0, 0), StartLocation);
	ChosenNodes.Emplace(StartLocation, ChosenNode);

	for (int i = 0; i < CellsMap->Num(); i++)
	{
		bWasPathFound = AddLikelyNodes(CellsMap, InitAxialLocations, ChosenNode);
		if (bWasPathFound)
		{
			BuildPath(ChosenNode, OutPath);
			OutPathCost = ChosenNode.F;
			return true;
		}
		if (LikelyNodes.IsEmpty())
		{
			OutPathCost = INT_MAX;
			return false;
		}

		ChosenNode = ChoseBetterNextNode();
		ChosenNodes.Emplace(ChosenNode.AxialLocation, ChosenNode);
		LikelyNodes.Remove(ChosenNode.AxialLocation);
	}

	return false;
}


void UCPP_FuncLib_AStarSearch::Init(FVector2f StartAxialLocation, FVector2f EndAxialLocation, TArray<FVector2f>& OutPath)
{
	bWasPathFound = false;
	//OutPath.Empty();
	LikelyNodes.Empty();
	ChosenNodes.Empty();
	StartLocation = StartAxialLocation;
	EndLocation = EndAxialLocation;
}


bool UCPP_FuncLib_AStarSearch::WouldThereBeValidPath(const TMap<FVector2f, const ACPP_Cell*>* CellsMap, const TArray<FVector2f>* InitAxialLocations)
{
	bool bStartCellCanShiftLocation{ false };
	bool bEndCellCanShiftLocation{ false };
	const ACPP_Cell* const* StartCell{ nullptr };
	const ACPP_Cell* const* EndCell{ nullptr };

	if (StartLocation == EndLocation)
	{
		return false;
	}

	StartCell = CellsMap->Find(StartLocation);

	if (!StartCell)
	{
		return false;
	}

	bStartCellCanShiftLocation = (*StartCell)->CellType->bCanShiftLocation;
	if (!bStartCellCanShiftLocation)
	{
		return false;
	}

	if (!CellsMap->Contains(EndLocation))
	{
		for (auto& Elem : *InitAxialLocations)
		{
			EndCell = CellsMap->Find(EndLocation + Elem);
			if (!EndCell)
			{
				continue;
			}

			bEndCellCanShiftLocation = (*EndCell)->CellType->bCanShiftLocation;
			if (bEndCellCanShiftLocation)
			{
				return true;
			}
		}
		return false;
	}
	return true;
}


/*
* Return true when a neighbour from parent node is the end of the path
*/
bool UCPP_FuncLib_AStarSearch::AddLikelyNodes(const TMap<FVector2f, const ACPP_Cell*>* CellsMap,
	const TArray<FVector2f>* InitAxialLocations, FASearchNode ParentNode)
{
	FVector2f NeighbourLocation;

	for (auto& InitAxLoc : *InitAxialLocations)
	{
		NeighbourLocation = ParentNode.AxialLocation + InitAxLoc;
		if (NeighbourLocation == EndLocation)
		{
			return true;
		}
		const ACPP_Cell* const* Cell = CellsMap->Find(NeighbourLocation);
		if (!CanBeIncluded(Cell, NeighbourLocation))
		{
			continue;
		}
		AddOrModifyLikelyNode(*Cell, NeighbourLocation, ParentNode);
	}
	return false;
}


bool UCPP_FuncLib_AStarSearch::CanBeIncluded(const ACPP_Cell* const* Cell, FVector2f NeighbourLocation)
{
	if (!Cell)
	{
		return false;
	}

	if (!(*Cell)->CellType->bCanShiftLocation)
	{
		return false;
	}

	if ((*Cell)->IsSelected())
	{
		return false;
	}

	bool bIsOld = (*Cell)->CellLifeStateIsEqualOrOlderThan(UCPP_SM_Cell_LifeSt_OldAge::StaticClass());
	if (bIsOld)
	{
		return false;
	}

	if (ChosenNodes.Contains(NeighbourLocation))
	{
		return false;
	}
	return true;
}


void UCPP_FuncLib_AStarSearch::AddOrModifyLikelyNode(const ACPP_Cell* Cell, FVector2f NeighbourLocation, FASearchNode ParentNode)
{
	int G;
	int H;

	G = ParentNode.G + (Cell)->CellType->ShiftLocationCost;
	H = UCPP_FuncLib_CellUtils::GetDistanceBetweenAxialLocations(NeighbourLocation, EndLocation);

	FASearchNode* Node = LikelyNodes.Find(NeighbourLocation);
	if (Node)
	{
		if (Node->F > G + H)
		{
			Node->G = G;
			Node->F = G + H;
			Node->ParentLocation = ParentNode.AxialLocation;
			return;
		}
		return;
	}

	FASearchNode NewNode = FASearchNode(G, H, ParentNode.AxialLocation, NeighbourLocation);
	LikelyNodes.Emplace(NeighbourLocation, NewNode);
}



FASearchNode UCPP_FuncLib_AStarSearch::ChoseBetterNextNode()
{
	FASearchNode TempNode;
	int TempF = INT_MAX;

	for (auto& Elem : LikelyNodes)
	{
		if (Elem.Value.F < TempF)
		{
			TempF = Elem.Value.F;
			TempNode = Elem.Value;
		}
	}
	return TempNode;
}


void UCPP_FuncLib_AStarSearch::BuildPath(FASearchNode LastChosenNode, TArray<FVector2f>& OutPath)
{
	TArray<FVector2f> ReversePath;
	FVector2f CurrentLocation = EndLocation;
	FASearchNode CurrentNode = LastChosenNode;

	ReversePath.Emplace(CurrentLocation);
	CurrentLocation = CurrentNode.AxialLocation;
	ReversePath.Emplace(CurrentLocation);

	while (CurrentLocation != StartLocation)
	{
		CurrentNode = ChosenNodes[CurrentLocation];
		CurrentLocation = CurrentNode.ParentLocation;
		ReversePath.Emplace(CurrentLocation);
	}

	for (int i = ReversePath.Num() - 1; i >= 0; i--)
	{
		OutPath.Emplace(ReversePath[i]);
	}
}






