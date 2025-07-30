#include "Actors/Grid/Components/CPP_AC_Grid_ShiftPathController.h"
#include "Actors/Grid/Components/CPP_Util_AC_Grid_ShiftPathsAdmin.h"
#include "Core/GameInstance/CPP_GameInstance.h"
#include "Core/Subsystems/EventBuses/CPP_SS_CellsManagerEventBus.h"
#include "Core/Subsystems/EventBuses/CPP_SS_UIEventBus.h"
#include "Core/Subsystems/EventBuses/CPP_SS_GameEventBus.h"
#include "Core/Subsystems/EventBuses/CPP_SS_InputEventBus.h"
#include "Kismet/GameplayStatics.h"
#include "Core/Subsystems/Managers/CPP_SS_LocalGameManager.h"
#include "Core/Subsystems/Managers/CPP_SS_CellsManager.h"
#include "Actors/Grid/CPP_Grid.h"
#include "Utils/Macros/Macros.h"
#include "Actors/Cell/CPP_Cell.h"





UCPP_AC_Grid_ShiftPathController::UCPP_AC_Grid_ShiftPathController()
{
	ShiftPathsAdmin = CreateDefaultSubobject<UCPP_Util_AC_Grid_ShiftPathsAdmin>(TEXT("ShiftPathsAdmin"));
}



void UCPP_AC_Grid_ShiftPathController::BeginPlay()
{
	Super::BeginPlay();

	InitEventBuses();
	InitComponent();
	RegisterEventFunctions();
}

void UCPP_AC_Grid_ShiftPathController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UnRegisterEventFunctions();
}

void UCPP_AC_Grid_ShiftPathController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}



void UCPP_AC_Grid_ShiftPathController::InitComponent()
{
	Super::InitComponent();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	checkf(PlayerController, TEXT("***> No PlayerController (nullptr) <***"));

	GameManager = PlayerController->GetLocalPlayer()->GetSubsystem<UCPP_SS_LocalGameManager>();
	checkf(GameManager, TEXT("***> No CellsManager (nullptr) <***"));

}



void UCPP_AC_Grid_ShiftPathController::InitEventBuses()
{
	UWorld* World = GetWorld();
	checkf(World, TEXT("***> No World (nullptr) <***"));

	UCPP_GameInstance* GameInstance = Cast<UCPP_GameInstance>(World->GetGameInstance());
	checkf(GameInstance, TEXT("***> No GameInstance (nullptr) <***"));

	CellsManagerEventBus = GameInstance->GetSubsystem<UCPP_SS_CellsManagerEventBus>();
	checkf(CellsManagerEventBus, TEXT("***> No CellsManagerEventBus (nullptr) <***"));

	UIEventBus = GameInstance->GetSubsystem<UCPP_SS_UIEventBus>();
	checkf(UIEventBus, TEXT("***> No UIEventBus (nullptr) <***"));

	GameEventBus = GameInstance->GetSubsystem<UCPP_SS_GameEventBus>();
	checkf(GameEventBus, TEXT("***> No UIEventBus (nullptr) <***"));

	InputEventBus = GameInstance->GetSubsystem<UCPP_SS_InputEventBus>();
	checkf(InputEventBus, TEXT("***> No InputEventBus (nullptr) <***"));
}


void UCPP_AC_Grid_ShiftPathController::RegisterEventFunctions() const
{
	GameEventBus->Phase2StartedEventDelegate.AddUniqueDynamic(
		this, &UCPP_AC_Grid_ShiftPathController::Phase2StartedEvent);

	CellsManagerEventBus->BeginCellsShiftingEventDelegate.AddUniqueDynamic(
		this, &UCPP_AC_Grid_ShiftPathController::CellsShiftingEvent);
	CellsManagerEventBus->CellsShiftingReturnEventDelegate.AddUniqueDynamic(
		this, &UCPP_AC_Grid_ShiftPathController::CellsShiftingReturnEvent);
	CellsManagerEventBus->FinishCellDivisionEventDelegate.AddUniqueDynamic(
		this, &UCPP_AC_Grid_ShiftPathController::FinishCellDivisionEvent);

	UIEventBus->BeginCellDivisionEventDelegate.AddUniqueDynamic(
		this, &UCPP_AC_Grid_ShiftPathController::BeginCellDivisionEvent);

	InputEventBus->ClickOnCellEventDelegate.AddUniqueDynamic(
		this, &UCPP_AC_Grid_ShiftPathController::ClickOnCellEvent);
	InputEventBus->ClickOnAuxGridElemEventDelegate.AddUniqueDynamic(
		this, &UCPP_AC_Grid_ShiftPathController::ClickOnAuxGridElemEvent);
}


void UCPP_AC_Grid_ShiftPathController::UnRegisterEventFunctions() const
{	
	GameEventBus->Phase2StartedEventDelegate.RemoveDynamic(
		this, &UCPP_AC_Grid_ShiftPathController::Phase2StartedEvent);

	CellsManagerEventBus->BeginCellsShiftingEventDelegate.RemoveDynamic(
		this, &UCPP_AC_Grid_ShiftPathController::CellsShiftingEvent);
	CellsManagerEventBus->CellsShiftingReturnEventDelegate.RemoveDynamic(
		this, &UCPP_AC_Grid_ShiftPathController::CellsShiftingReturnEvent);
	CellsManagerEventBus->FinishCellDivisionEventDelegate.RemoveDynamic(
		this, &UCPP_AC_Grid_ShiftPathController::FinishCellDivisionEvent);

	UIEventBus->BeginCellDivisionEventDelegate.RemoveDynamic(
		this, &UCPP_AC_Grid_ShiftPathController::BeginCellDivisionEvent);

	InputEventBus->ClickOnCellEventDelegate.RemoveDynamic(
		this, &UCPP_AC_Grid_ShiftPathController::ClickOnCellEvent);
	InputEventBus->ClickOnAuxGridElemEventDelegate.RemoveDynamic(
		this, &UCPP_AC_Grid_ShiftPathController::ClickOnAuxGridElemEvent);
}


void UCPP_AC_Grid_ShiftPathController::Phase2StartedEvent(UCPP_SS_CellsManager* TheCellsManager, ACPP_Grid* TheGrid)
{
	CellsManager = TheCellsManager;
	ShiftPathsAdmin->Initialize(GameSettings, CellsManager, OwnerGrid);
}


void UCPP_AC_Grid_ShiftPathController::CellsShiftingEvent(const ACPP_Cell* FirstCellToShift)
{
	int CellsShiftings = ShiftPathsAdmin->ChangeCellsLocations(FirstCellToShift);
}


void UCPP_AC_Grid_ShiftPathController::CellsShiftingReturnEvent()
{
	ShiftPathsAdmin->ReturnAllCellsToLocations();
}


void UCPP_AC_Grid_ShiftPathController::FinishCellDivisionEvent(FVector2f SpawnAxialLocation)
{
	if (CellsManager)
	{		
		ShiftPathsUpdate(CurrentClickedCell);	
	}	
}


void UCPP_AC_Grid_ShiftPathController::BeginCellDivisionEvent()
{
	ShiftPathsUpdate(CurrentClickedCell);	
}


void UCPP_AC_Grid_ShiftPathController::ShiftPathsUpdate(const ACPP_Cell* CellToDivide)
{
	ShiftPathsAdmin->Update(CellToDivide);
	bAreCellShiftPathsStatesUpdated = true;
}


void UCPP_AC_Grid_ShiftPathController::ClickOnCellEvent(const ACPP_Cell* ClickedCell)
{
	CurrentClickedCell = ClickedCell;
	if (UCPP_SS_LocalGameManager::IsGridActive())
	{
		ShiftPathsUpdate(CurrentClickedCell);
	}
}


void UCPP_AC_Grid_ShiftPathController::ClickOnAuxGridElemEvent()
{
	UpdateLocationsOfCellsInPath();
	/*if (UpdateLocationsOfCellsInPath())
	{		
		ShiftPathsAdmin->ReturnAllCellsToLocations();
		ShiftPathsUpdate(GameManager->GetBeforeClickedCell());		
	}*/
}



bool UCPP_AC_Grid_ShiftPathController::UpdateLocationsOfCellsInPath()
{
	ECPP_CellShiftState AuxGridElement = UCPP_SS_LocalGameManager::AuxGridElemShiftState;
	ECPP_CellShiftState AtTemporal = ECPP_CellShiftState::AtTempLocation;

	if (AuxGridElement != AtTemporal)
	{
		return false;
	}

	TArray<FVector2f> CellsInPath;
	FVector2f TheFreeNeighbourInPath = ShiftPathsAdmin->GetAxialLocOfCellsInCurrentPath(CellsInPath);

	if (CellsInPath.IsEmpty())
	{
		return false;
	}
	FVector2f FirstAxLocInPath = CellsInPath[0];

	CellsManager->UpdateToTempLocations(CellsInPath);
	OwnerGrid->UpdateToTempLocations(TheFreeNeighbourInPath);

	

	InputEventBus->RaiseClickOnGridEvent(FirstAxLocInPath);

	ShiftPathsUpdate(CurrentClickedCell);

	//ShiftPathsAdmin->ReturnAllCellsToLocations();
	//ShiftPathsUpdate(GameManager->GetBeforeClickedCell());	

	


	return true;
}





