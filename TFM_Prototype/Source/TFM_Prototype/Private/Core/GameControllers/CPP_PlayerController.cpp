#include "Core/GameControllers/CPP_PlayerController.h"
#include "Core/GameSettings/CPP_DA_GameSettings.h"
#include "Core/Subsystems/EventBuses/CPP_SS_InputEventBus.h"
#include "Actors/Cell/CPP_Cell.h"
#include "Core/Subsystems/Managers/CPP_SS_CellsManager.h"
#include "Core/GameInstance/CPP_GameInstance.h"

#include "Utils/Macros/Macros.h"




void ACPP_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	InitEventBuses();

	FreeNeighbours.Empty();
	CellsBirthOrder.Empty();
	RegisterEventFunctions();

	CellsManager = GetLocalPlayer()->GetSubsystem<UCPP_SS_CellsManager>();
	checkf(CellsManager, TEXT("***> No CellsManager (nullptr) <***"));

	/*TimerDelegate.BindUFunction(this, FName(TEXT("StartCellsManager")));
	GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, GameSettings->StartCellsManagerAfter, false);*/

	StartCellsManager();
}



void ACPP_PlayerController::StartCellsManager()
{
	CellsManager->StartManager(this);
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
		PRINT("Click on cell");
		InputEventBus->RaiseClickOnCellEvent(ClickedCell);
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