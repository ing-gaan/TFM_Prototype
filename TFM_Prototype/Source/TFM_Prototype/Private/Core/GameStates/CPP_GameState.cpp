#include "Core/GameStates/CPP_GameState.h"
#include "Core/Subsystems/EventBuses/CPP_SS_TimeEventBus.h" 




ACPP_GameState::ACPP_GameState()
{
	PrimaryActorTick.bCanEverTick = false;
}



void ACPP_GameState::BeginPlay()
{
	Super::BeginPlay();

	InitGameState();
	StartTenMilliSecondsTimer();
}




void ACPP_GameState::InitGameState()
{
	World = GetWorld();
	checkf(World, TEXT("***> No World (nullptr) <***"));

	TimeEventBus = GetGameInstance()->GetSubsystem<UCPP_SS_TimeEventBus>();
	checkf(TimeEventBus, TEXT("***> No TimeEventBus (nullptr) <***"));
}


void ACPP_GameState::StartTenMilliSecondsTimer()
{
	FTimerHandle TenMilliSecondsTimerHandle;
	FTimerDelegate TenMilliSecondsTimerDelegate;

	FTimerManager& TimerManager = World->GetTimerManager();
	TenMilliSecondsTimerDelegate.BindUFunction(this, FName("TenMilliSecondsPassed"));
	TimerManager.SetTimer(TenMilliSecondsTimerHandle, TenMilliSecondsTimerDelegate, 0.01f, true);
}



void ACPP_GameState::TenMilliSecondsPassed()
{
	TensMilliSecondsPassed++;
	TimeEventBus->RaiseTenMilliSecondsEvent();

	if (TensMilliSecondsPassed % 100 == 0)
	{
		OneSecondPassed();
		TensMilliSecondsPassed = 0;
	}
}



void ACPP_GameState::OneSecondPassed()
{
	SecondsPassed++;
	TimeEventBus->RaiseOneSecondEvent();

	if (SecondsPassed % 10 == 0)
	{
		TimeEventBus->RaiseTenSecondsEvent();
		SecondsPassed = 0;
	}
}

