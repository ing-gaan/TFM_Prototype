#include "Core/GameControllers/CPP_PlayerController.h"
#include "Core/GameSettings/CPP_DA_GameSettings.h"
#include "Core/GameSettings/CPP_DA_GridSettings.h"
#include "Actors/Cell/CPP_Cell.h"
#include "Utils/FunctionLibraries/CPP_CellFunctionLibrary.h"
#include "Utils/Macros/Macros.h"
#include "Core/Subsystems/Managers/CPP_SS_CellsManager.h"




void ACPP_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	InitEventBuses();
	//CellsMap.Empty();
	FreeNeighbours.Empty();
	CellsBirthOrder.Empty();
	RegisterEventFunctions();

	CellsManager = GetLocalPlayer()->GetSubsystem<UCPP_SS_CellsManager>();
	checkf(CellsManager, TEXT("***> No CellsManager (nullptr) <***"));


	//CellsManager = NewObject<UCPP_SS_CellsManager>();
	
	//CellsManager->AddFirstCell();
	//AddFirstCell();


	TimerDelegate.BindUFunction(this, FName("StartCellsManager"));
	GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, GameSettings->StartCellsManagerAfter, false);
}



void ACPP_PlayerController::StartCellsManager()
{
	CellsManager->StartManager(GameSettings, GridSettings, this);
}



void ACPP_PlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UnRegisterEventFunctions();
}


void ACPP_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//CursorOverActor();
}


void ACPP_PlayerController::InitEventBuses()
{
	UWorld* World = GetWorld();
	checkf(World, TEXT("***> No World (nullptr) <***"));

	UGameInstance* GameInstance = World->GetGameInstance();
	checkf(GameInstance, TEXT("***> No GameInstance (nullptr) <***"));
	
	/*InputEventBus = GameInstance->GetSubsystem<UCPP_SS_InputEventBus>();
	checkf(InputEventBus, TEXT("***> No InputEventBus (nullptr) <***"));

	TimersEventBus = GameInstance->GetSubsystem<UCPP_SS_TimersEventBus>();
	checkf(TimersEventBus, TEXT("***> No TimersEventBus (nullptr) <***"));
	TimersEventBus->Init(GetWorld());

	GameEventBus = GameInstance->GetSubsystem<UCPP_SS_GameEventBus>();
	checkf(GameEventBus, TEXT("***> No GameEventBus (nullptr) <***"));*/
}


void ACPP_PlayerController::RegisterEventFunctions() const
{
	/*GameEventBus->BeginDestroyCellEventDelegate.AddUniqueDynamic(
		this, &ACPP_PlayerController::BeginDestroyCellEvent);
	GameEventBus->FinishDestroyCellEventDelegate.AddUniqueDynamic(
		this, &ACPP_PlayerController::FinishDestroyCellEvent);*/
}


void ACPP_PlayerController::UnRegisterEventFunctions() const
{
	/*GameEventBus->BeginDestroyCellEventDelegate.RemoveDynamic(
		this, &ACPP_PlayerController::BeginDestroyCellEvent);
	GameEventBus->FinishDestroyCellEventDelegate.RemoveDynamic(
		this, &ACPP_PlayerController::FinishDestroyCellEvent);*/
}


//bool ACPP_PlayerController::IsAxialLocationFree(FVector2f AxialLocation) const
//{
//	return !CellsMap.Contains(AxialLocation);
//}
//
//
//const ACPP_Cell* ACPP_PlayerController::GetFirstCell() const
//{
//	return FirstCell;
//}


//void ACPP_PlayerController::AddFirstCell()
//{
//	if (!CellsMap.IsEmpty())
//	{
//		return;
//	}
//	SpawnFirstCell();
//	AddCellSpawned(FirstCell);
//}



//void ACPP_PlayerController::SpawnFirstCell()
//{
//	FVector Location = FVector::ZeroVector;
//	Location.Z = GameSettings->DefaultHeightFromGround;
//	FRotator Rotation = FRotator::ZeroRotator;
//	TSubclassOf<ACPP_Cell> FirstCellClass = GameSettings->FirstCellBPClass;
//	FActorSpawnParameters SpawnParam;
//	SpawnParam.Name = FName(TEXT("FIRST_CELL"));
//
//	checkf(GetWorld(), TEXT("***> No GetWorld (nullptr) <***"));
//	FirstCell = GetWorld()->SpawnActor<ACPP_Cell>(FirstCellClass, Location, Rotation, SpawnParam);
//
//	if (!FirstCell)
//	{
//		checkf(FirstCell, TEXT("***> No OriginCell (nullptr) <***"));
//		return;
//	}
//
//	FVector2f CellAxialLocation = GridSettings->FirstAxialLocation;
//	const FString StrName = UCPP_CellFunctionLibrary::GetCellLabel(CellAxialLocation);
//	FirstCell->SetActorLabel(StrName);	
//	FirstCell->SetAxialLocation(CellAxialLocation);	
//}


//void ACPP_PlayerController::AddCellSpawned(const ACPP_Cell* NewCell)
//{
//	FVector2f NewAxialLoc = NewCell->GetAxialLocation();	
//	const ACPP_Cell** Cellptr = CellsMap.Find(NewAxialLoc);
//
//	if (Cellptr)
//	{
//		if (*Cellptr != nullptr)
//		{
//			PRINT("ERROR: EXIST A CELL IN AXIAL LOCATION");
//			return;
//		}
//		CellsMap[NewAxialLoc] = NewCell;
//		return;
//	}
//	CellsMap.Emplace(NewAxialLoc, NewCell);
//	CellsBirthOrder.Add(NewCell);
//	FreeNeighbours.Remove(NewCell->GetAxialLocation());
//	AddNewFreeNeighbours(NewCell);
//}


//void ACPP_PlayerController::AddNewFreeNeighbours(const ACPP_Cell* NewCell)
//{
//	FVector2f AxLoc;
//	for (const FVector2f& Elem : GridSettings->InitAxialLocations)
//	{
//		AxLoc = Elem + NewCell->GetAxialLocation();
//		if (!CellsMap.Contains(AxLoc))
//		{
//			FreeNeighbours.Add(AxLoc);
//		}
//	}
//}

//void ACPP_PlayerController::BeginDestroyCellEvent(ACPP_Cell* CellToDestroy)
//{
//	FVector2f AxialLocToDestroy = CellToDestroy->GetAxialLocation();
//	ACPP_Cell** Cellptr = CellsMap.Find(AxialLocToDestroy);
//
//	if (!Cellptr || !(*Cellptr))
//	{
//		PRINT("ERROR: NOT EXIST CELL IN AXIAL LOCATION");
//		return;
//	}
//	CellsMap.Remove(AxialLocToDestroy);
//	CellsBirthOrder.RemoveSingle(CellToDestroy);
//	RemoveFreeNeighbours(AxialLocToDestroy);
//	//StoreCellStaticProperties();
//}


//void ACPP_PlayerController::FinishDestroyCellEvent()
//{
//	//RestoreCellStaticProperties();
//}





//void ACPP_PlayerController::RemoveFreeNeighbours(FVector2f CenterAxialLoc)
//{
//	FVector2f TempAxLoc;
//	for (FVector2f& InitAxLoc : InitData->InitAxialLocations)
//	{
//		TempAxLoc = CenterAxialLoc + InitAxLoc;
//		FreeNeighbours.Remove(TempAxLoc);
//	}
//
//	for (FVector2f& InitAxLoc : InitData->InitAxialLocations)
//	{
//		TempAxLoc = CenterAxialLoc + InitAxLoc;
//		ACPP_Cell** Cellptr = CellsMap.Find(TempAxLoc);
//		if (Cellptr && *Cellptr)
//		{
//			AddNewFreeNeighbours(*Cellptr);
//		}
//	}
//}


//void ACPP_PlayerController::CursorOverActor()
//{
//	ETraceTypeQuery Visibility = UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Visibility);
//	HitResult;
//
//	bool HasHit = GetHitResultUnderCursorByChannel(Visibility, true, HitResult);
//
//	if (!HasHit)
//	{
//		return;
//	}
//
//	HitActor = HitResult.GetActor();
//	HitSMeshComponent = Cast<UStaticMeshComponent>(HitResult.Component);
//
//	if (BeforeSMeshCompCursorOver == HitSMeshComponent)
//	{
//		InputEventBus->RaiseStayCursorOverEvent(BeforeActorCursorOver, BeforeSMeshCompCursorOver);
//		return;
//	}
//
//	InputEventBus->RaiseEndCursorOverEvent(BeforeActorCursorOver, BeforeSMeshCompCursorOver);
//	BeforeActorCursorOver = HitActor;
//	BeforeSMeshCompCursorOver = HitSMeshComponent;
//	InputEventBus->RaiseBeginCursorOverEvent(HitActor, HitSMeshComponent);
//}



//void ACPP_PlayerController::ClickOnActor()
//{
//	if (!HitActor)
//	{
//		return;
//	}
//
//	ACPP_Cell* Cell = Cast<ACPP_Cell>(HitActor);
//	if (Cell)
//	{
//		ClickOnCell(Cell);
//		return;
//	}
//
//	const ACPP_NeighbourGrid* NeighbourGrid = Cast<ACPP_NeighbourGrid>(HitActor);
//	if (NeighbourGrid)
//	{
//		ClickOnGrid(NeighbourGrid);
//		return;
//	}
//	InputEventBus->RaiseCancelEvent();
//}


//void ACPP_PlayerController::ClickOnCell(ACPP_Cell* Cell)
//{
//	const ACPP_AuxiliaryCell* AuxiliaryCell = Cast<ACPP_AuxiliaryCell>(HitActor);
//	if (AuxiliaryCell)
//	{
//		InputEventBus->RaiseClickOnAuxiliaryCellEvent();
//		return;
//	}
//	InputEventBus->RaiseClickOnCellEvent(Cell);
//}



//void ACPP_PlayerController::ClickOnGrid(const ACPP_NeighbourGrid* NeighbourGrid)
//{
//	InputEventBus->RaiseClickOnNeighbourGridEvent(HitSMeshComponent);
//}


//const TSet<FVector2f>* ACPP_PlayerController::GetAllFreeNeighbours() const
//{
//	return &FreeNeighbours;
//}


//void ACPP_PlayerController::GetCellFreeNeighbours(const ACPP_Cell& Cell, TArray<FVector2f>& OutCellFreeNeighbours) const
//{
//	OutCellFreeNeighbours.Empty();
//	FVector2f CellAxLoc = Cell.GetAxialLocation();
//	FVector2f NextToAxLoc;
//
//	for (FVector2f& InitAxLoc : InitData->InitAxialLocations)
//	{
//		NextToAxLoc = CellAxLoc + InitAxLoc;
//
//		if (IsAxialLocationFree(NextToAxLoc))
//		{
//			OutCellFreeNeighbours.Emplace(NextToAxLoc);
//		}
//	}
//}


//int ACPP_PlayerController::GetCellsNumber()
//{
//	return CellsMap.Num();
//}


//void ACPP_PlayerController::GetCellNeighbours(const ACPP_Cell* Cell, TArray<ACPP_Cell*>& OutNeighbours) const
//void ACPP_PlayerController::GetCellNeighbours(const ACPP_Cell* Cell, TSet<ACPP_Cell*>& OutNeighbours) const
//{
//	FVector2f CellAxLoc = Cell->GetAxialLocation();
//	FVector2f NeighbourAxLoc;
//	ACPP_Cell* const* NeighbourPtr;
//
//	for (FVector2f& InitAxLoc : InitData->InitAxialLocations)
//	{
//		NeighbourAxLoc = CellAxLoc + InitAxLoc;
//
//		NeighbourPtr = CellsMap.Find(NeighbourAxLoc);
//		if (NeighbourPtr)
//		{
//			OutNeighbours.Emplace(*NeighbourPtr);
//		}
//	}
//}


/// Returns a const reference to the Cells map
//const TMap<FVector2f, ACPP_Cell*>* ACPP_PlayerController::GetCellsMap() const
//{
//	return &CellsMap;
//}


/// Returns a const reference to the Cell in map or nullptr
//const ACPP_Cell* ACPP_PlayerController::GetCellInMap(FVector2f CellAxialLocation) const
//{
//	ACPP_Cell* const* Cellptr = CellsMap.Find(CellAxialLocation);
//
//	if (!Cellptr)
//	{
//		return nullptr;
//	}
//	return *Cellptr;
//}


//void ACPP_PlayerController::UpdateToTempLocations(TArray<FVector2f>& AxialLocations)
//{
//	ACPP_Cell** Cellptr;
//	//PRINT("FREE NUM BEFORE = %d ON TEMP", FreeNeighbours.Num());
//	for (int i = AxialLocations.Num() - 1; i >= 0; i--)
//	{
//		Cellptr = CellsMap.Find(AxialLocations[i]);
//		if (!Cellptr)
//		{
//			PRINT("ERROR AXIALLOC NOT IN MAP");
//			return;
//		}
//		UpdateCellToTempLocation(*Cellptr);
//	}
//	//PRINT("FREE NUM AFTER = %d ON TEMP", FreeNeighbours.Num());
//}



//void ACPP_PlayerController::UpdateCellToTempLocation(ACPP_Cell* Cell)
//{
//	FVector2f AxialLocation = Cell->GetAxialLocation();
//	FVector2f TempLocation = Cell->GetTempAxialLocation();
//
//	CellsMap[AxialLocation] = nullptr;
//	CellsMap.Emplace(TempLocation, Cell);
//
//	Cell->UpdateToTemporalLocation();
//	UCellFunctionLibrary::ChangeCellLabel(Cell, TempLocation);
//	FreeNeighbours.Remove(TempLocation);
//	AddNewFreeNeighbours(Cell);
//}

//void ACPP_PlayerController::StoreCellStaticProperties()
//{
//	TempClickedCell = ACPP_Cell::CurrentClickedCell;
//	TempFirstCell = ACPP_Cell::FirstCell;
//}
//
//void ACPP_PlayerController::RestoreCellStaticProperties()
//{
//	ACPP_Cell::CurrentClickedCell = TempClickedCell;
//	ACPP_Cell::FirstCell = TempFirstCell;
//}

//const ACPP_Cell* ACPP_PlayerController::GetOldestLiveCell() const
//{
//	return CellsBirthOrder[0];
//}


