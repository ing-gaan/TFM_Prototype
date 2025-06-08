#include "Core/Subsystems/Managers/CPP_SS_CellsManager.h"
#include "Core/GameSettings/CPP_DA_GameSettings.h"
#include "Core/GameSettings/CPP_DA_GridSettings.h"
#include "Actors/Cell/CPP_Cell.h"
#include "Utils/FunctionLibraries/CPP_CellFunctionLibrary.h"
#include "Utils/Macros/Macros.h"
#include "Core/GameControllers/CPP_PlayerController.h"
#include "Core/Subsystems/EventBuses/CPP_SS_InputEventBus.h"
#include "Core/Subsystems/EventBuses/CPP_SS_CellsManagerEventBus.h"
#include "Core/Subsystems/EventBuses/CPP_SS_UIEventBus.h"
#include "Core/GameInstance/CPP_GameInstance.h"
#include "Actors/Cell/Components/CPP_AC_Cell_Division.h"
#include "Actors/Cell/Components/CPP_AC_Cell_Differentiation.h"
#include "Actors/Cell/CPP_DA_CellType.h"






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

	UCPP_GameInstance* GameInstance = Cast<UCPP_GameInstance>(World->GetGameInstance());
	checkf(GameInstance, TEXT("***> No GameInstance (nullptr) <***"));

	GameSettings = GameInstance->GameSettings;
	GridSettings = GameSettings->GridSettings;

	InputEventBus = GameInstance->GetSubsystem<UCPP_SS_InputEventBus>();
	checkf(InputEventBus, TEXT("***> No InputEventBus (nullptr) <***"));

	CellsManagerEventBus = GameInstance->GetSubsystem<UCPP_SS_CellsManagerEventBus>();
	checkf(CellsManagerEventBus, TEXT("***> No CellsManagerEventBus (nullptr) <***"));

	UIEventBus = GameInstance->GetSubsystem<UCPP_SS_UIEventBus>();
	checkf(UIEventBus, TEXT("***> No UIEventBus (nullptr) <***"));

}


void UCPP_SS_CellsManager::RegisterEventFunctions() const
{
	InputEventBus->ClickOnCellEventDelegate.AddUniqueDynamic(
		this, &UCPP_SS_CellsManager::ClickOnCellEvent);
	InputEventBus->ClickOnGridEventDelegate.AddUniqueDynamic(
		this, &UCPP_SS_CellsManager::ClickOnGridEvent);

	UIEventBus->FinishCellDifferentiationEventDelegate.AddUniqueDynamic(
		this, &UCPP_SS_CellsManager::FinishCellDifferentiationEvent);
}


void UCPP_SS_CellsManager::UnRegisterEventFunctions() const
{
	InputEventBus->ClickOnCellEventDelegate.RemoveDynamic(
		this, &UCPP_SS_CellsManager::ClickOnCellEvent);
	InputEventBus->ClickOnGridEventDelegate.RemoveDynamic(
		this, &UCPP_SS_CellsManager::ClickOnGridEvent);


	UIEventBus->FinishCellDifferentiationEventDelegate.RemoveDynamic(
		this, &UCPP_SS_CellsManager::FinishCellDifferentiationEvent);
}



void UCPP_SS_CellsManager::StartManager(const ACPP_PlayerController* PlayerController)
{	
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



void UCPP_SS_CellsManager::FinishCellDifferentiationEvent(const UCPP_DA_CellType* NewCellType)
{
	if (!ClickdCell->HasThisAbility(UCPP_AC_Cell_Differentiation::StaticClass()))
	{
		return;
	}

	ClickdCell->Differentiate(NewCellType);
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
	ConfigureFirstCell(FirstCell, FirstCellAxialLocation);

	return FirstCell;
}

ACPP_Cell* UCPP_SS_CellsManager::SpawnCell(FVector CellLocation, FRotator CellRotation, TSubclassOf<ACPP_Cell> CellClass)
{
	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ACPP_Cell* CellSpawned = GetWorld()->SpawnActor<ACPP_Cell>(CellClass, CellLocation, CellRotation, SpawnParam);
	checkf(CellSpawned, TEXT("***> No CellSpawned (nullptr) <***"));

	return CellSpawned;
}

void UCPP_SS_CellsManager::ConfigureFirstCell(ACPP_Cell* FirstCell, FVector2f AxialLocation)
{
	const FString StrName = UCPP_CellFunctionLibrary::GetCellOutlinerLabel(AxialLocation);
	FirstCell->SetActorLabel(StrName);
	FirstCell->SetAxialLocation(AxialLocation);
	FirstCell->LoadCellTypeComponents(GameSettings->FirstCellType);
}



void UCPP_SS_CellsManager::DuplicateCell(FVector2f AxialLocation)
{	
	if (!ClickdCell->HasThisAbility(UCPP_AC_Cell_Division::StaticClass()))
	{
		return;
	}
	const ACPP_Cell* CellSpawned = ClickdCell->Divide(AxialLocation);

	if (!CellSpawned)
	{
		return;
	}

	AddCellSpawned(CellSpawned);
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
		
	CellsManagerEventBus->RaiseFinishCellDivisionEvent(NewAxialLoc);
	//return NewAxialLoc;
}
