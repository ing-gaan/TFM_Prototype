#include "Core/Subsystems/Managers/CPP_SS_LocalGameManager.h"
#include "Core/GameInstance/CPP_GameInstance.h"
#include "Core/Subsystems/EventBuses/CPP_SS_InputEventBus.h"
#include "Core/Subsystems/EventBuses/CPP_SS_UIEventBus.h"
#include "Core/Subsystems/EventBuses/CPP_SS_CellsManagerEventBus.h"
#include "Actors/Grid/CPP_Grid.h"




const ACPP_Cell* UCPP_SS_LocalGameManager::CurrentClickedCell{ nullptr };
bool UCPP_SS_LocalGameManager::bIsGridActive{ false };
bool UCPP_SS_LocalGameManager::bAreCellsShifting{ false };
bool UCPP_SS_LocalGameManager::bIsACellDividing{ false };




void UCPP_SS_LocalGameManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	InitEventBuses();
	RegisterEventFunctions();
}


void UCPP_SS_LocalGameManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterEventFunctions();

}


void UCPP_SS_LocalGameManager::StartManager(const UCPP_SS_CellsManager* TheCellsManager, const ACPP_Grid* TheGrid)
{
	CellsManager = TheCellsManager;
	Grid = TheGrid;
}


void UCPP_SS_LocalGameManager::InitEventBuses()
{
	UWorld* World = GetWorld();
	checkf(World, TEXT("***> No World (nullptr) <***"));

	UCPP_GameInstance* GameInstance = Cast<UCPP_GameInstance>(World->GetGameInstance());
	checkf(GameInstance, TEXT("***> No GameInstance (nullptr) <***"));

	InputEventBus = GameInstance->GetSubsystem<UCPP_SS_InputEventBus>();
	checkf(InputEventBus, TEXT("***> No InputEventBus (nullptr) <***"));

	UIEventBus = GameInstance->GetSubsystem<UCPP_SS_UIEventBus>();
	checkf(UIEventBus, TEXT("***> No UIEventBus (nullptr) <***"));

	CellsManagerEventBus = GameInstance->GetSubsystem<UCPP_SS_CellsManagerEventBus>();
	checkf(UIEventBus, TEXT("***> No UIEventBus (nullptr) <***"));

}


void UCPP_SS_LocalGameManager::RegisterEventFunctions() const
{
	InputEventBus->ClickOnCellEventDelegate.AddUniqueDynamic(
		this, &UCPP_SS_LocalGameManager::ClickOnCellEvent);
	InputEventBus->CancelEventDelegate.AddUniqueDynamic(
		this, &UCPP_SS_LocalGameManager::CancelEvent);

	CellsManagerEventBus->CellsShiftingEventDelegate.AddUniqueDynamic(
		this, &UCPP_SS_LocalGameManager::CellsShiftingEvent);
	CellsManagerEventBus->FinishCellDivisionEventDelegate.AddUniqueDynamic(
		this, &UCPP_SS_LocalGameManager::FinishCellDivisionEvent);

	UIEventBus->BeginCellDivisionEventDelegate.AddUniqueDynamic(
		this, &UCPP_SS_LocalGameManager::BeginCellDivisionEvent);

}


void UCPP_SS_LocalGameManager::UnRegisterEventFunctions() const
{
	InputEventBus->ClickOnCellEventDelegate.RemoveDynamic(
		this, &UCPP_SS_LocalGameManager::ClickOnCellEvent);
	InputEventBus->CancelEventDelegate.RemoveDynamic(
		this, &UCPP_SS_LocalGameManager::CancelEvent);

	CellsManagerEventBus->CellsShiftingEventDelegate.RemoveDynamic(
		this, &UCPP_SS_LocalGameManager::CellsShiftingEvent);
	CellsManagerEventBus->FinishCellDivisionEventDelegate.RemoveDynamic(
		this, &UCPP_SS_LocalGameManager::FinishCellDivisionEvent);

	UIEventBus->BeginCellDivisionEventDelegate.RemoveDynamic(
		this, &UCPP_SS_LocalGameManager::BeginCellDivisionEvent);
}



void UCPP_SS_LocalGameManager::ClickOnCellEvent(const ACPP_Cell* ClickedCell)
{	
	CurrentClickedCell = ClickedCell;
}


void UCPP_SS_LocalGameManager::CancelEvent()
{
	CurrentClickedCell = nullptr;
	bIsGridActive = false;
	bAreCellsShifting = false;
	bIsACellDividing = false;
}


void UCPP_SS_LocalGameManager::CellsShiftingEvent(bool ShouldCellsShiftLocation)
{
	bAreCellsShifting = ShouldCellsShiftLocation;
}


void UCPP_SS_LocalGameManager::FinishCellDivisionEvent(FVector2f SpawnAxialLocation)
{
	CurrentClickedCell = nullptr;
	bIsGridActive = false;
	bAreCellsShifting = false;
	bIsACellDividing = false;
}


void UCPP_SS_LocalGameManager::BeginCellDivisionEvent()
{
	bIsGridActive = true;
	bIsACellDividing = true;
}


const ACPP_Cell* UCPP_SS_LocalGameManager::GetCurrentClickedCell()
{
	return CurrentClickedCell;
}


bool UCPP_SS_LocalGameManager::IsGridActive()
{
	return bIsGridActive;
}


bool UCPP_SS_LocalGameManager::AreCellsShifting()
{
	return bAreCellsShifting;
}

bool UCPP_SS_LocalGameManager::IsACellDividing()
{
	return bIsACellDividing;
}


const UCPP_SS_CellsManager* UCPP_SS_LocalGameManager::GetCellsManager() const
{
	return CellsManager;
}


const ACPP_Grid* UCPP_SS_LocalGameManager::GetGrid() const
{
	return Grid;
}





