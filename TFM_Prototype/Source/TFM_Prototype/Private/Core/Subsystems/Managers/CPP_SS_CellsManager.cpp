#include "Core/Subsystems/Managers/CPP_SS_CellsManager.h"
#include "Core/GameSettings/CPP_DA_GameSettings.h"
#include "Core/GameSettings/CPP_DA_GridSettings.h"
#include "Actors/Cell/CPP_Cell.h"
#include "Utils/FunctionLibraries/CPP_FuncLib_CellUtils.h"
#include "Utils/Macros/Macros.h"
#include "Core/GameControllers/CPP_PlayerController.h"
#include "Core/Subsystems/EventBuses/CPP_SS_InputEventBus.h"
#include "Core/Subsystems/EventBuses/CPP_SS_CellsManagerEventBus.h"
#include "Core/Subsystems/EventBuses/CPP_SS_UIEventBus.h"
#include "Core/GameInstance/CPP_GameInstance.h"
#include "Actors/Cell/Components/CPP_AC_Cell_Division.h"
#include "Actors/Cell/Components/CPP_AC_Cell_Differentiation.h"
#include "Actors/Cell/Components/CPP_AC_Cell_Movement.h"
#include "Actors/Cell/CPP_DA_CellType.h"
#include "Core/Subsystems/Managers/CPP_SS_LocalGameManager.h"








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
	CellsManagerEventBus->MoveCellsEventDelegate.AddUniqueDynamic(
		this, &UCPP_SS_CellsManager::MoveCellsEvent);

	InputEventBus->ClickOnCellEventDelegate.AddUniqueDynamic(
		this, &UCPP_SS_CellsManager::ClickOnCellEvent);
	InputEventBus->ClickOnGridEventDelegate.AddUniqueDynamic(
		this, &UCPP_SS_CellsManager::ClickOnGridEvent);
	InputEventBus->CancelEventDelegate.AddUniqueDynamic(
		this, &UCPP_SS_CellsManager::CancelEvent);

	UIEventBus->FinishCellDifferentiationEventDelegate.AddUniqueDynamic(
		this, &UCPP_SS_CellsManager::FinishCellDifferentiationEvent);
}


void UCPP_SS_CellsManager::UnRegisterEventFunctions() const
{
	CellsManagerEventBus->MoveCellsEventDelegate.RemoveDynamic(
		this, &UCPP_SS_CellsManager::MoveCellsEvent);

	InputEventBus->ClickOnCellEventDelegate.RemoveDynamic(
		this, &UCPP_SS_CellsManager::ClickOnCellEvent);
	InputEventBus->ClickOnGridEventDelegate.RemoveDynamic(
		this, &UCPP_SS_CellsManager::ClickOnGridEvent);
	InputEventBus->CancelEventDelegate.RemoveDynamic(
		this, &UCPP_SS_CellsManager::CancelEvent);


	UIEventBus->FinishCellDifferentiationEventDelegate.RemoveDynamic(
		this, &UCPP_SS_CellsManager::FinishCellDifferentiationEvent);
}



void UCPP_SS_CellsManager::StartManager()
{	
	//PlayerContller = PlayerController;
	CellsMap.Empty();	
	AddFirstCell();	
	ACPP_Cell::CellsManager = this;
}



void UCPP_SS_CellsManager::MoveCellsEvent()
{
	for (TPair<FVector2f, const ACPP_Cell*>& Elem : CellsMap)
	{
		if (Elem.Value->HasThisAbility(UCPP_AC_Cell_Movement::StaticClass()))
		{
			Elem.Value->MoveCell();
		}		
	}
}


void UCPP_SS_CellsManager::ClickOnCellEvent(const ACPP_Cell* ClickedCell)
{		
	if (CurrentClickedCell && (ClickedCell != CurrentClickedCell))
	{
		UnclickCurrentCell();		
	}	
	CurrentClickedCell = ClickedCell;
}



void UCPP_SS_CellsManager::ClickOnGridEvent(FVector2f AxialLocation)
{
	DivideCellEvent(AxialLocation);
}


void UCPP_SS_CellsManager::CancelEvent()
{
	if (!CurrentClickedCell){ return; }

	UnclickCurrentCell();
}


void UCPP_SS_CellsManager::FinishCellDifferentiationEvent(const UCPP_DA_CellType* NewCellType)
{
	if (!CurrentClickedCell->HasThisAbility(UCPP_AC_Cell_Differentiation::StaticClass())) { return; }

	CurrentClickedCell->Differentiate(NewCellType);
	UnclickCurrentCell();
}



void UCPP_SS_CellsManager::AddFirstCell()
{
	if (!CellsMap.IsEmpty()) { return; }
	
	AddCellSpawned(SpawnFirstCell());
	return;
}



ACPP_Cell* UCPP_SS_CellsManager::SpawnFirstCell()
{
	FVector Location = FVector::ZeroVector;
	Location.Z = GameSettings->CellsDefaultHeightFromGround;
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
	const FString StrName = UCPP_FuncLib_CellUtils::GetCellOutlinerLabel(AxialLocation);
	FirstCell->SetActorLabel(StrName);	
	FirstCell->LoadCellTypeComponents(GameSettings->FirstCellType);
	//CurrentClickedCell = FirstCell;
	FirstCell->SetAxialLocation(AxialLocation);
}



void UCPP_SS_CellsManager::DivideCellEvent(FVector2f AxialLocation)
{		
	if (!CurrentClickedCell) { return; }
	if (!CurrentClickedCell->HasThisAbility(UCPP_AC_Cell_Division::StaticClass())) { return; }
	
	const ACPP_Cell* CellSpawned = CurrentClickedCell->Divide(AxialLocation);
	if (!CellSpawned) {	return;	}

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
			return;// UCPP_FuncLib_CellUtils::BadAxialLocation;
		}
		CellsMap[NewAxialLoc] = NewCell;
		return;// UCPP_FuncLib_CellUtils::BadAxialLocation;
	}
	CellsMap.Emplace(NewAxialLoc, NewCell);
	CellsBirthOrder.Add(NewCell);
	
	CellsManagerEventBus->RaiseFinishCellDivisionEvent(NewAxialLoc);
	UnclickCurrentCell();
}


void UCPP_SS_CellsManager::UnclickCurrentCell()
{
	if (!CurrentClickedCell) { return; }

	CurrentClickedCell->Unclick();
	CurrentClickedCell = nullptr;
}


void UCPP_SS_CellsManager::StartShiftingCellsLocations(const ACPP_Cell* FirstCellToShift) const
{	
	if (UCPP_SS_LocalGameManager::AreCellsShifting()) { return; }


	CellsManagerEventBus->RaiseCellsShiftingEvent(true);



	//----- CODIGO DEBUG ----- 
	FVector2f NewTempAxialLoc = FirstCellToShift->GetAxialLocation() * 2;
	FirstCellToShift->ShiftAxialLocation(NewTempAxialLoc);
}


//----- CODIGO DEBUG  Quitar clicked cell ----- 
void UCPP_SS_CellsManager::ReturnCellsToOriginLocation(const ACPP_Cell* ClickedCell) const
{
	if (!UCPP_SS_LocalGameManager::AreCellsShifting()) { return; }
	

	PRINT("Cancel Shifting");
	CellsManagerEventBus->RaiseCellsShiftingEvent(false);
	



	//----- CODIGO DEBUG ----- 


	

	if (!ClickedCell)
	{
		return;
	}
	
	for (FVector2f AxLoc : GameSettings->GridSettings->InitAxialLocations)
	{
		FVector2f NeighbourAxLoc = ClickedCell->GetAxialLocation() + AxLoc;

		if (CellsMap.Contains(NeighbourAxLoc))
		{
			CellsMap[NeighbourAxLoc]->ReturnToOriginAxialLocation();
		}
	}
}


const ACPP_Cell* UCPP_SS_CellsManager::GetCellInMap(FVector2f CellAxialLocation) const
{
	const ACPP_Cell* const* Cellptr = CellsMap.Find(CellAxialLocation);

	if (!Cellptr)
	{
		return nullptr;
	}
	return *Cellptr;
}


const TMap<FVector2f, const ACPP_Cell*>* UCPP_SS_CellsManager::GetCellsMap() const
{
	return &CellsMap;
}
