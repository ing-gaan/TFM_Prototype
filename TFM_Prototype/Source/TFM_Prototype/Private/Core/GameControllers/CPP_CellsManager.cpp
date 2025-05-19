#include "Core/GameControllers/CPP_CellsManager.h"
#include "Core/GameSettings/CPP_DA_GameSettings.h"
#include "Core/GameSettings/CPP_DA_GridSettings.h"
#include "Actors/Cell/CPP_Cell.h"
#include "Utils/FunctionLibraries/CPP_CellFunctionLibrary.h"
#include "Utils/Macros/Macros.h"
#include "Core/GameControllers/CPP_PlayerController.h"





void UCPP_CellsManager::InitManager(const UCPP_DA_GameSettings* GameSettingsDA, 
	const UCPP_DA_GridSettings* GridSettingsDA, const ACPP_PlayerController* PlayerController )
{
	GameSettings = GameSettingsDA;
	GridSettings = GridSettingsDA;
	PlayerContller = PlayerController;
}


const ACPP_Cell* UCPP_CellsManager::AddFirstCell()
{
	if (!CellsMap.IsEmpty())
	{
		return CellsMap[FVector2f::Zero()];
	}
	SpawnFirstCell();
	AddCellSpawned(FirstCell);

	return FirstCell;
}



void UCPP_CellsManager::SpawnFirstCell()
{
	FVector Location = FVector::ZeroVector;
	Location.Z = GameSettings->DefaultHeightFromGround;
	FRotator Rotation = FRotator::ZeroRotator;
	TSubclassOf<ACPP_Cell> FirstCellClass = GameSettings->FirstCellBPClass;
	FActorSpawnParameters SpawnParam;
	SpawnParam.Name = FName(TEXT("FIRST_CELL"));

	checkf(PlayerContller->GetWorld(), TEXT("***> No GetWorld (nullptr) <***"));
	FirstCell = PlayerContller->GetWorld()->SpawnActor<ACPP_Cell>(FirstCellClass, Location, Rotation, SpawnParam);

	if (!FirstCell)
	{
		checkf(FirstCell, TEXT("***> No OriginCell (nullptr) <***"));
		return;
	}

	FVector2f CellAxialLocation = GridSettings->FirstAxialLocation;
	const FString StrName = UCPP_CellFunctionLibrary::GetCellOutlinerLabel(CellAxialLocation);
	FirstCell->SetActorLabel(StrName);
	FirstCell->SetAxialLocation(CellAxialLocation);
}


void UCPP_CellsManager::AddCellSpawned(const ACPP_Cell* NewCell)
{
	FVector2f NewAxialLoc = NewCell->GetAxialLocation();
	const ACPP_Cell** Cellptr = CellsMap.Find(NewAxialLoc);

	if (Cellptr)
	{
		if (*Cellptr != nullptr)
		{
			PRINT("ERROR: EXIST A CELL IN AXIAL LOCATION");
			return;
		}
		CellsMap[NewAxialLoc] = NewCell;
		return;
	}
	CellsMap.Emplace(NewAxialLoc, NewCell);
	CellsBirthOrder.Add(NewCell);
	//FreeNeighbours.Remove(NewCell->GetAxialLocation());
	//AddNewFreeNeighbours(NewCell);
}