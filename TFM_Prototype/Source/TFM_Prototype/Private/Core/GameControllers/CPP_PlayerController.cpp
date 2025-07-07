#include "Core/GameControllers/CPP_PlayerController.h"
#include "Core/Subsystems/EventBuses/CPP_SS_InputEventBus.h"
#include "Actors/Cell/CPP_Cell.h"
#include "Core/Subsystems/Managers/CPP_SS_LocalGameManager.h"
#include "Core/Subsystems/Managers/CPP_SS_CellsManager.h"
#include "Core/GameInstance/CPP_GameInstance.h"
#include "Actors/Grid/CPP_Grid.h"
#include "Kismet/GameplayStatics.h"
#include "Utils/Macros/Macros.h"




void ACPP_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	InitEventBuses();

	FreeNeighbours.Empty();
	CellsBirthOrder.Empty();
	RegisterEventFunctions();

	LocalGameManager = GetLocalPlayer()->GetSubsystem<UCPP_SS_LocalGameManager>();
	checkf(LocalGameManager, TEXT("***> No CellsManager (nullptr) <***"));

	CellsManager = GetLocalPlayer()->GetSubsystem<UCPP_SS_CellsManager>();
	checkf(CellsManager, TEXT("***> No CellsManager (nullptr) <***"));

	//FTimerDelegate TimerDelegate;
	//FTimerHandle TimerHandle;
	//TimerDelegate.BindUObject(this, &ACPP_PlayerController::StartManagers);
	////GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, GameSettings->StartCellsManagerAfter, false);
	//GetWorldTimerManager().SetTimerForNextTick(TimerDelegate);

	StartManagers();
}



void ACPP_PlayerController::StartManagers()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACPP_Grid::StaticClass(), FoundActors);

	if (FoundActors.Num() == 0)
	{
		checkf(true, TEXT("***> No Grid in game. Spawn a Grid from editor <***"));
	}
	else if (FoundActors.Num() > 1)
	{
		checkf(true, TEXT("***> Multiple grid in game. Delete from editor and leave only one. <***"));
	}

	const ACPP_Grid* Grid = Cast<ACPP_Grid>(FoundActors[0]);

	CellsManager->StartManager();
	LocalGameManager->StartManager(CellsManager, Grid);
	
}



void ACPP_PlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UnRegisterEventFunctions();
}


void ACPP_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ACPP_PlayerController::InitEventBuses()
{
	UWorld* World = GetWorld();
	checkf(World, TEXT("***> No World (nullptr) <***"));

	UCPP_GameInstance* GameInstance = Cast<UCPP_GameInstance>(World->GetGameInstance());
	checkf(GameInstance, TEXT("***> No GameInstance (nullptr) <***"));

	GameSettings = GameInstance->GameSettings;
	
	InputEventBus = GameInstance->GetSubsystem<UCPP_SS_InputEventBus>();
	checkf(InputEventBus, TEXT("***> No InputEventBus (nullptr) <***"));

}


void ACPP_PlayerController::RegisterEventFunctions() const
{
	
}


void ACPP_PlayerController::UnRegisterEventFunctions() const
{
	
}


void ACPP_PlayerController::ClickOnActor()
{	
	const AActor* ClickedActor = CursorOverActor();

	if (!ClickedActor)
	{
		return;
	}

	const ACPP_Cell* ClickedCell = Cast<ACPP_Cell>(ClickedActor);
	if (ClickedCell)
	{
		//InputEventBus->RaiseClickOnCellEvent(ClickedCell);
		return;
	}

	const ACPP_Grid* Grid = Cast<ACPP_Grid>(ClickedActor);
	if (Grid)
	{
		return;
	}

	InputEventBus->RaiseCancelEvent();
}


const AActor* ACPP_PlayerController::CursorOverActor()
{	
	ETraceTypeQuery Visibility = UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Visibility);
	FHitResult HitResult;
	bool HasHit = GetHitResultUnderCursorByChannel(Visibility, true, HitResult);

	if (!HasHit)
	{
		return nullptr;
	}
	return HitResult.GetActor();
}

