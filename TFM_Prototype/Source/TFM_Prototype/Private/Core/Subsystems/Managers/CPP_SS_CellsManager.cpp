#include "Core/Subsystems/Managers/CPP_SS_CellsManager.h"
#include "Core/GameSettings/CPP_DA_GameSettings.h"
#include "Core/GameSettings/CPP_DA_GridSettings.h"
#include "Actors/Cell/CPP_Cell.h"
#include "Utils/FunctionLibraries/CPP_CellFunctionLibrary.h"
#include "Utils/Macros/Macros.h"
#include "Core/GameControllers/CPP_PlayerController.h"
#include "Core/Subsystems/EventBuses/CPP_SS_InputEventBus.h"
#include "Core/Subsystems/EventBuses/CPP_SS_CellsManagerEventBus.h"
#include "Utils/Macros/Macros.h"




void UCPP_SS_CellsManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	InitEventBuses();
	RegisterEventFunctions();
}

void UCPP_SS_CellsManager::Deinitialize()
{
	Super::Deinitialize();

	UnRegisterEventFunctions();
}



void UCPP_SS_CellsManager::InitEventBuses()
{
	UWorld* World = GetWorld();
	checkf(World, TEXT("***> No World (nullptr) <***"));

	UGameInstance* GameInstance = World->GetGameInstance();
	checkf(GameInstance, TEXT("***> No GameInstance (nullptr) <***"));

	InputEventBus = GameInstance->GetSubsystem<UCPP_SS_InputEventBus>();
	checkf(InputEventBus, TEXT("***> No InputEventBus (nullptr) <***"));

	CellsManagerEventBus = GameInstance->GetSubsystem<UCPP_SS_CellsManagerEventBus>();
	checkf(CellsManagerEventBus, TEXT("***> No CellsManagerEventBus (nullptr) <***"));

}


void UCPP_SS_CellsManager::RegisterEventFunctions() const
{
	InputEventBus->ClickOnCellEventDelegate.AddUniqueDynamic(
		this, &UCPP_SS_CellsManager::ClickOnCellEvent);
	InputEventBus->ClickOnGridEventDelegate.AddUniqueDynamic(
		this, &UCPP_SS_CellsManager::ClickOnGridEvent);

}


void UCPP_SS_CellsManager::UnRegisterEventFunctions() const
{
	InputEventBus->ClickOnCellEventDelegate.RemoveDynamic(
		this, &UCPP_SS_CellsManager::ClickOnCellEvent);
	InputEventBus->ClickOnGridEventDelegate.RemoveDynamic(
		this, &UCPP_SS_CellsManager::ClickOnGridEvent);

}



void UCPP_SS_CellsManager::StartManager(const UCPP_DA_GameSettings* GameSettingsDA,
	const UCPP_DA_GridSettings* GridSettingsDA, const ACPP_PlayerController* PlayerController)
{
	GameSettings = GameSettingsDA;
	GridSettings = GridSettingsDA;
	PlayerContller = PlayerController;
	CellsMap.Empty();
	AddFirstCell();
}



void UCPP_SS_CellsManager::ClickOnCellEvent(const ACPP_Cell* ClickedCell)
{
	ClickdCell = ClickedCell;
	//PRINT("Receive clicked cell");
}



void UCPP_SS_CellsManager::ClickOnGridEvent(FVector2f AxialLocation)
{
	DuplicateCell(AxialLocation);
}



void UCPP_SS_CellsManager::AddFirstCell()
{
	if (!CellsMap.IsEmpty())
	{
		return;
	}

	AddCellSpawned(SpawnFirstCell());
	return;
}



ACPP_Cell* UCPP_SS_CellsManager::SpawnFirstCell()
{
	FVector Location = FVector::ZeroVector;
	Location.Z = GameSettings->DefaultHeightFromGround;
	FRotator Rotation = FRotator::ZeroRotator;
	TSubclassOf<ACPP_Cell> FirstCellClass = GameSettings->FirstCellBPClass;

	ACPP_Cell* FirstCell = SpawnCell(Location, Rotation, FirstCellClass);
	FVector2f FirstCellAxialLocation = GridSettings->FirstAxialLocation;
	ConfigureNewCell(FirstCell, FirstCellAxialLocation);

	return FirstCell;
}



void UCPP_SS_CellsManager::DuplicateCell(FVector2f AxialLocation)
{	
	float Distance = GridSettings->DistanceBetweenNeighbours;
	FVector2f OriginAxLoc = FVector2f::Zero();
	FVector2D RelativeLoc;
	UCPP_CellFunctionLibrary::GetRelativeLocationFromAnOrigin(Distance, OriginAxLoc, AxialLocation, RelativeLoc);
	
	FVector Location;
	Location.X = RelativeLoc.X;
	Location.Y = RelativeLoc.Y;
	Location.Z = GameSettings->DefaultHeightFromGround;	
	FRotator Rotation = FRotator::ZeroRotator;
	TSubclassOf<ACPP_Cell> NewCellClass = ClickdCell->GetClass();

	ACPP_Cell* CellSpawned = SpawnCell(Location, Rotation, NewCellClass);
	ConfigureNewCell(CellSpawned, AxialLocation);

	AddCellSpawned(CellSpawned);
}



ACPP_Cell* UCPP_SS_CellsManager::SpawnCell(FVector CellLocation, FRotator CellRotation, TSubclassOf<ACPP_Cell> CellClass)
{
	checkf(GetWorld(), TEXT("***> No GetWorld (nullptr) <***"));

	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ACPP_Cell* CellSpawned = GetWorld()->SpawnActor<ACPP_Cell>(CellClass, CellLocation, CellRotation, SpawnParam);
	checkf(CellSpawned, TEXT("***> No CellSpawned (nullptr) <***"));

	return CellSpawned;
}


void UCPP_SS_CellsManager::ConfigureNewCell(ACPP_Cell* NewCell, FVector2f AxialLocation)
{
	const FString StrName = UCPP_CellFunctionLibrary::GetCellOutlinerLabel(AxialLocation);
	NewCell->SetActorLabel(StrName);
	NewCell->SetAxialLocation(AxialLocation);
	
	//NewCell->ChangeCellType(OwnerCell->CellType);
	//CellSpawned->CurrentClickedCell = OwnerCell->CurrentClickedCell;
	//CellSpawned->ChangeCellCursorState(ECPP_CursorStateEnum::Init);
	//OwnerCell->PlayerController->AddCellSpawned(CellSpawned);
	//GameEventBus->RaiseCellSpawnedEvent(CellSpawned);
}



void UCPP_SS_CellsManager::AddCellSpawned(const ACPP_Cell* NewCell)
{
	FVector2f NewAxialLoc = NewCell->GetAxialLocation();
	const ACPP_Cell** Cellptr = CellsMap.Find(NewAxialLoc);

	if (Cellptr)
	{
		if (*Cellptr != nullptr)
		{
			PRINT("ERROR: EXIST A CELL IN AXIAL LOCATION");
			return;// UCPP_CellFunctionLibrary::BadAxialLocation;
		}
		CellsMap[NewAxialLoc] = NewCell;
		return;// UCPP_CellFunctionLibrary::BadAxialLocation;
	}
	CellsMap.Emplace(NewAxialLoc, NewCell);
	CellsBirthOrder.Add(NewCell);
		
	CellsManagerEventBus->RaiseFinishDuplicateCellEvent(NewAxialLoc);
	//return NewAxialLoc;
}
