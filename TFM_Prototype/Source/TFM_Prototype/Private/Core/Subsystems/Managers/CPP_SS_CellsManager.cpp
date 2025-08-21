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
#include "Core/Subsystems/EventBuses/CPP_SS_GameEventBus.h"
#include "Core/GameInstance/CPP_GameInstance.h"
#include "Actors/Cell/Components/CPP_AC_Cell_Division.h"
#include "Actors/Cell/Components/CPP_AC_Cell_Differentiation.h"
#include "Actors/Cell/Components/CPP_AC_Cell_Movement.h"
#include "Actors/Cell/CPP_DA_CellType.h"
#include "Core/Subsystems/Managers/CPP_SS_LocalGameManager.h"
#include "Actors/Grid/CPP_Grid.h"
#include "Engine/AssetManager.h"







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

	GameEventBus = GameInstance->GetSubsystem<UCPP_SS_GameEventBus>();
	checkf(GameEventBus, TEXT("***> No UIEventBus (nullptr) <***"));

}


void UCPP_SS_CellsManager::RegisterEventFunctions() const
{
	GameEventBus->Phase1StartedEventDelegate.AddUniqueDynamic(
		this, &UCPP_SS_CellsManager::Phase1StartedEvent);

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

	UIEventBus->BeginEliminateCellEventDelegate.AddUniqueDynamic(
		this, &UCPP_SS_CellsManager::BeginEliminateCellEvent);
}


void UCPP_SS_CellsManager::UnRegisterEventFunctions() const
{
	GameEventBus->Phase1StartedEventDelegate.RemoveDynamic(
		this, &UCPP_SS_CellsManager::Phase1StartedEvent);

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

	UIEventBus->BeginEliminateCellEventDelegate.RemoveDynamic(
		this, &UCPP_SS_CellsManager::BeginEliminateCellEvent);
}



void UCPP_SS_CellsManager::Phase1StartedEvent()
{
	StartManager();
}


void UCPP_SS_CellsManager::StartManager()
{	
	CellsMap.Empty();	
	AddFirstCell();	
	ACPP_Cell::CellsManager = this;
}



void UCPP_SS_CellsManager::MoveCellsEvent(bool bCellsMoving)
{
	for (TPair<FVector2f, ACPP_Cell*>& Elem : CellsMap)
	{
		if (Elem.Value->HasThisAbility(UCPP_AC_Cell_Movement::StaticClass()))
		{
			Elem.Value->MoveCell(bCellsMoving, false);
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
	if (!CurrentClickedCell)
	{ 
		return; 
	}

	UnclickCurrentCell();
}


void UCPP_SS_CellsManager::FinishCellDifferentiationEvent(const TSoftObjectPtr<UCPP_DA_CellType> NewCellType)
{
	if (!CurrentClickedCell->HasThisAbility(UCPP_AC_Cell_Differentiation::StaticClass())) 
	{ 
		return; 
	}

	CurrentClickedCell->BeginDifferentiate(NewCellType);
	//UnclickCurrentCell();
}


void UCPP_SS_CellsManager::BeginEliminateCellEvent()
{
	CurrentClickedCell->BeginCellApoptosis();
}


void UCPP_SS_CellsManager::AddFirstCell()
{
	if (!CellsMap.IsEmpty()) 
	{ 
		return; 
	}
	
	SpawnFirstCell();
	//AddCellSpawned();
}



void UCPP_SS_CellsManager::SpawnFirstCell()
{
	TArray<FSoftObjectPath> AssetsToLoad;
	FirstCellClass = GameSettings->FirstCellBPClass;
	FirstCellType = GameSettings->FirstCellType;
	AssetsToLoad.Add(FirstCellClass.ToSoftObjectPath());
	AssetsToLoad.Add(FirstCellType.ToSoftObjectPath());

	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();

	StreamableManager.RequestAsyncLoad(AssetsToLoad,
		FStreamableDelegate::CreateUObject(this, &UCPP_SS_CellsManager::FirstCellClassSoftRefLoaded));
}


void UCPP_SS_CellsManager::FirstCellClassSoftRefLoaded()
{
	if (!FirstCellClass.IsValid())
	{
		return;
	}

	FVector Location = FVector::ZeroVector;
	Location.Z = GameSettings->CellsDefaultHeightFromGround;
	FRotator Rotation = FRotator::ZeroRotator;

	ACPP_Cell* FirstCell = SpawnCell(Location, Rotation, FirstCellClass.Get());
	FVector2f FirstCellAxialLocation = GridSettings->FirstAxialLocation;
		
	ConfigureFirstCell(FirstCell, FirstCellAxialLocation);
	FirstCell->In_De_creaseCellEnergy(GameSettings->FirstCellInitEnergy);
	AddCellSpawned(FirstCell);

	
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
	//const FString StrName = UCPP_FuncLib_CellUtils::GetCellOutlinerLabel(AxialLocation);
	//FirstCell->SetActorLabel(StrName);	
	FirstCell->SetAxialLocation(AxialLocation);

	if (FirstCellType.IsValid())
	{
		FirstCell->LoadCellTypeComponents(FirstCellType.Get());
	}	
}



void UCPP_SS_CellsManager::DivideCellEvent(FVector2f AxialLocation)
{		
	if (!CurrentClickedCell)
	{ 
		return; 
	}
	if (!CurrentClickedCell->HasThisAbility(UCPP_AC_Cell_Division::StaticClass())) 
	{ 
		return; 
	}
		
	ACPP_Cell* CellSpawned = CurrentClickedCell->Divide(AxialLocation);
	if (!CellSpawned) 
	{	
		return;	
	}

	AddCellSpawned(CellSpawned);
}



void UCPP_SS_CellsManager::AddCellSpawned(ACPP_Cell* NewCell)
{
	FVector2f NewAxialLoc = NewCell->GetAxialLocation();
	ACPP_Cell** Cellptr = CellsMap.Find(NewAxialLoc);

	if (Cellptr)
	{
		if (*Cellptr != nullptr)
		{
			PRINT("ERROR: EXIST A CELL IN AXIAL LOCATION");
			return;// UCPP_FuncLib_CellUtils::BadAxialLocation;
		}
		//CellsMap[NewAxialLoc] = NewCell;
		//return;// UCPP_FuncLib_CellUtils::BadAxialLocation;
	}

	CellsMap.Emplace(NewAxialLoc, NewCell);
	//CellsBirthOrder.Emplace(NewCell);

	CellsManagerEventBus->RaiseFinishCellDivisionEvent(NewAxialLoc);
	//UnclickCurrentCell();
}


void UCPP_SS_CellsManager::UnclickCurrentCell()
{
	if (!CurrentClickedCell)
	{ 
		return; 
	}

	CurrentClickedCell->Unclick();
	CurrentClickedCell = nullptr;
}


void UCPP_SS_CellsManager::StartShiftingCellsLocations(const ACPP_Cell* FirstCellToShift) const
{		
	if (UCPP_SS_LocalGameManager::AreCellsShifting())
	{ 
		
		return; 
	}
	CellsManagerEventBus->RaiseBeginCellsShiftingEvent(FirstCellToShift);
}



void UCPP_SS_CellsManager::ReturnCellsToOriginLocation() const
{
	if (!UCPP_SS_LocalGameManager::AreCellsShifting()) 
	{ 
		return; 
	}

	CellsManagerEventBus->RaiseCellsShiftingReturnEvent();
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


const TMap<FVector2f, ACPP_Cell*>* UCPP_SS_CellsManager::GetCellsMap() const
{
	return &CellsMap;
}



void UCPP_SS_CellsManager::UpdateToTempLocations(TArray<FVector2f>& AxialLocations)
{
	ACPP_Cell** Cellptr;
	FVector2f CurrentAxLoc;

	for (int i = AxialLocations.Num() - 1; i >= 0; i--)
	{
		CurrentAxLoc = AxialLocations[i];
		Cellptr = CellsMap.Find(CurrentAxLoc);
		if (!Cellptr)
		{
			PRINT("ERROR AXIALLOC NOT IN MAP");
			return;
		}
		UpdateCellToTempLocation(*Cellptr);
	}
}


void UCPP_SS_CellsManager::UpdateCellToTempLocation(ACPP_Cell* Cell)
{	
	FVector2f AxialLocation = Cell->GetAxialLocation();
	FVector2f TempLocation = Cell->GetTempAxialLocation();

	//CellsMap[AxialLocation] = nullptr;
	CellsMap.Remove(AxialLocation);
	CellsMap.Emplace(TempLocation, Cell);

	Cell->UpdateToTemporalLocation();
	//Cell->ReturnToOriginAxialLocation();
}

void UCPP_SS_CellsManager::DestroyCell(ACPP_Cell* Cell)
{
	CellsManagerEventBus->RaiseBeginDestroyCellEvent(Cell->GetAxialLocation());
	CellsMap.Remove(Cell->GetAxialLocation());
}



int UCPP_SS_CellsManager::CellsInMapNumber() const
{
	return CellsMap.Num();
}


