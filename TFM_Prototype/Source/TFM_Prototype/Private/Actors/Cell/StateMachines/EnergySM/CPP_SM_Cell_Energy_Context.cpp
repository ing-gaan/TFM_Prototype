#include "Actors/Cell/StateMachines/EnergySM/CPP_SM_Cell_Energy_Context.h"
#include "Actors/Cell/StateMachines/EnergySM/CPP_SM_Cell_Energy_Base.h"
#include "Actors/Cell/StateMachines/EnergySM/CPP_SM_Cell_EnergySt_Full.h"
#include "Actors/Cell/StateMachines/EnergySM/CPP_SM_Cell_EnergySt_MidHigh.h"
#include "Actors/Cell/StateMachines/EnergySM/CPP_SM_Cell_EnergySt_Mid.h"
#include "Actors/Cell/StateMachines/EnergySM/CPP_SM_Cell_EnergySt_MidLow.h"
#include "Actors/Cell/StateMachines/EnergySM/CPP_SM_Cell_EnergySt_Low.h"
#include "Actors/Cell/StateMachines/EnergySM/CPP_SM_Cell_EnergySt_ExtremeLow.h"
#include "Actors/Cell/StateMachines/EnergySM/CPP_SM_Cell_EnergySt_Zero.h"
#include "Actors/Cell/CPP_Cell.h"




void UCPP_SM_Cell_Energy_Context::InitStateMachine(ACPP_Cell* Cell, UMaterialInstanceDynamic* MaterialInstance, const UWorld* GameWorld)
{
	Super::InitStateMachine(Cell, MaterialInstance, GameWorld);

	OwnerCell = Cell;

	UCPP_SM_Cell_Energy_Base* NewState = NewObject<UCPP_SM_Cell_EnergySt_Full>(this);
	checkf(NewState, TEXT("***> No NewState created (nullptr) <***"));
	NewState->InitializeState(this);
	States.Emplace(UCPP_SM_Cell_EnergySt_Full::StaticClass(), NewState);

	NewState = NewObject<UCPP_SM_Cell_EnergySt_MidHigh>(this);
	checkf(NewState, TEXT("***> No NewState created (nullptr) <***"));
	NewState->InitializeState(this);
	States.Emplace(UCPP_SM_Cell_EnergySt_MidHigh::StaticClass(), NewState);

	NewState = NewObject<UCPP_SM_Cell_EnergySt_Mid>(this);
	checkf(NewState, TEXT("***> No NewState created (nullptr) <***"));
	NewState->InitializeState(this);
	States.Emplace(UCPP_SM_Cell_EnergySt_Mid::StaticClass(), NewState);

	NewState = NewObject<UCPP_SM_Cell_EnergySt_MidLow>(this);
	checkf(NewState, TEXT("***> No NewState created (nullptr) <***"));
	NewState->InitializeState(this);
	States.Emplace(UCPP_SM_Cell_EnergySt_MidLow::StaticClass(), NewState);

	NewState = NewObject<UCPP_SM_Cell_EnergySt_Low>(this);
	checkf(NewState, TEXT("***> No NewState created (nullptr) <***"));
	NewState->InitializeState(this);
	States.Emplace(UCPP_SM_Cell_EnergySt_Low::StaticClass(), NewState);

	NewState = NewObject<UCPP_SM_Cell_EnergySt_ExtremeLow>(this);
	checkf(NewState, TEXT("***> No NewState created (nullptr) <***"));
	NewState->InitializeState(this);
	States.Emplace(UCPP_SM_Cell_EnergySt_ExtremeLow::StaticClass(), NewState);

	NewState = NewObject<UCPP_SM_Cell_EnergySt_Zero>(this);
	checkf(NewState, TEXT("***> No NewState created (nullptr) <***"));
	NewState->InitializeState(this);
	States.Emplace(UCPP_SM_Cell_EnergySt_Zero::StaticClass(), NewState);
}



void UCPP_SM_Cell_Energy_Context::CheckEnergyState()
{
	int EnergyLevel = OwnerCell->GetCellEnergy();

	if (EnergyLevel >= 100)
	{
		CurrentState = States[UCPP_SM_Cell_EnergySt_Full::StaticClass()];
	}
	else if (EnergyLevel < 100 && EnergyLevel >= 70)
	{
		CurrentState = States[UCPP_SM_Cell_EnergySt_MidHigh::StaticClass()];
	}
	else if (EnergyLevel < 70 && EnergyLevel >= 50)
	{
		CurrentState = States[UCPP_SM_Cell_EnergySt_Mid::StaticClass()];
	}
	else if (EnergyLevel < 50 && EnergyLevel >= 30)
	{
		CurrentState = States[UCPP_SM_Cell_EnergySt_MidLow::StaticClass()];
	}
	else if (EnergyLevel < 30 && EnergyLevel >= 10)
	{
		CurrentState = States[UCPP_SM_Cell_EnergySt_Low::StaticClass()];
	}
	else if (EnergyLevel < 10 && EnergyLevel >= 1)
	{
		CurrentState = States[UCPP_SM_Cell_EnergySt_ExtremeLow::StaticClass()];
	}
	else
	{
		CurrentState = States[UCPP_SM_Cell_EnergySt_Zero::StaticClass()];
	}

	CurrentState->ImplementState();
}

