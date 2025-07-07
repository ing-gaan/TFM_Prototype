#include "Actors/Cell/StateMachines/LifeSM/CPP_SM_Cell_Life_Context.h"
#include "Actors/Cell/StateMachines/LifeSM/CPP_SM_Cell_Life_Base.h"
#include "Actors/Cell/CPP_Cell.h"
#include "Actors/Cell/StateMachines/LifeSM/CPP_SM_Cell_LifeSt_Init.h"
#include "Actors/Cell/StateMachines/LifeSM/CPP_SM_Cell_LifeSt_Born.h"
#include "Actors/Cell/StateMachines/LifeSM/CPP_SM_Cell_LifeSt_Youth.h"
#include "Actors/Cell/StateMachines/LifeSM/CPP_SM_Cell_LifeSt_OldAge.h"
#include "Actors/Cell/StateMachines/LifeSM/CPP_SM_Cell_LifeSt_Dying.h"
#include "Actors/Cell/StateMachines/LifeSM/CPP_SM_Cell_LifeSt_Dead.h"





void UCPP_SM_Cell_Life_Context::InitContext(ACPP_Cell* Cell)
{
	OwnerCell = Cell;

	int StateSortPosition = 0;
	UCPP_SM_Cell_Life_Base* NewState = NewObject<UCPP_SM_Cell_LifeSt_Init>(this);
	checkf(NewState, TEXT("***> No NewState created (nullptr) <***"));
	NewState->InitState(this, StateSortPosition);
	States.Insert(NewState, StateSortPosition);

	StateSortPosition = 1;
	NewState = NewObject<UCPP_SM_Cell_LifeSt_Born>(this);
	checkf(NewState, TEXT("***> No NewState created (nullptr) <***"));
	NewState->InitState(this, StateSortPosition);
	States.Insert(NewState, StateSortPosition);

	StateSortPosition = 2;
	NewState = NewObject<UCPP_SM_Cell_LifeSt_Youth>(this);
	checkf(NewState, TEXT("***> No NewState created (nullptr) <***"));
	NewState->InitState(this, StateSortPosition);
	States.Insert(NewState, StateSortPosition);

	StateSortPosition = 3;
	NewState = NewObject<UCPP_SM_Cell_LifeSt_OldAge>(this);
	checkf(NewState, TEXT("***> No NewState created (nullptr) <***"));
	NewState->InitState(this, StateSortPosition);
	States.Insert(NewState, StateSortPosition);

	StateSortPosition = 4;
	NewState = NewObject<UCPP_SM_Cell_LifeSt_Dying>(this);
	checkf(NewState, TEXT("***> No NewState created (nullptr) <***"));
	NewState->InitState(this, StateSortPosition);
	States.Insert(NewState, StateSortPosition);

	StateSortPosition = 5;
	NewState = NewObject<UCPP_SM_Cell_LifeSt_Dead>(this);
	checkf(NewState, TEXT("***> No NewState created (nullptr) <***"));
	NewState->InitState(this, StateSortPosition);
	States.Insert(NewState, StateSortPosition);

	CurrentState = States[CurrentStateId];
	CurrentState->ImplementState();
}


void UCPP_SM_Cell_Life_Context::ChangeState()
{
	CurrentStateId++;

	if (CurrentStateId < States.Num())
	{
		CurrentState = States[CurrentStateId];
		CurrentState->ImplementState();
	}
}


void UCPP_SM_Cell_Life_Context::ChangeState(TSubclassOf<UCPP_SM_Cell_Life_Base> StateType)
{
	UCPP_SM_Cell_Life_Base* State = GetState(StateType);
	if (State)
	{
		CurrentState = State;
		CurrentState->ImplementState();
		CurrentStateId = State->GetStateSortPosition();
		return;
	}
	FString Str = StateType->GetName();
	checkf(false, TEXT("***> The State %s is missing <***"), *Str);
}


int UCPP_SM_Cell_Life_Context::GetStateSortPosition(TSubclassOf<UCPP_SM_Cell_Life_Base> StateType)
{
	UCPP_SM_Cell_Life_Base* State = GetState(StateType);
	if (State)
	{
		return State->GetStateSortPosition();
	}

	FString Str = StateType->GetName();
	checkf(false, TEXT("***> The State %s is missing <***"), *Str);
	return 0;
}

void UCPP_SM_Cell_Life_Context::ChangeToNewCellTypeStates()
{
	for (UCPP_SM_Cell_Life_Base* State : States)
	{
		State->ChangeToNewCellTypeState();
	}
}



UCPP_SM_Cell_Life_Base* UCPP_SM_Cell_Life_Context::GetState(TSubclassOf<UCPP_SM_Cell_Life_Base> StateType)
{
	for (UCPP_SM_Cell_Life_Base* State : States)
	{
		if (State->IsA(StateType))
		{
			return State;
		}
	}
	return nullptr;
}





