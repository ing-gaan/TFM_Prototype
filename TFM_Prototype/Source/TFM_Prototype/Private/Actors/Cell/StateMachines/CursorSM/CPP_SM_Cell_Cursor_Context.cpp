#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_Cursor_Context.h"
#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_Cursor_Base.h"
#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_CursorSt_Init.h"






void UCPP_SM_Cell_Cursor_Context::InitStateMachine(ACPP_Cell* Cell, UMaterialInstanceDynamic* MaterialInstance, const UWorld* GameWorld)
{
	Super::InitStateMachine(Cell, MaterialInstance, GameWorld);

	States.Empty();
	ChangeState(UCPP_SM_Cell_CursorSt_Init::StaticClass());
	bIsInitialized = true;
}


void UCPP_SM_Cell_Cursor_Context::ChangeState(TSubclassOf<UCPP_SM_Cell_Cursor_Base> NewStateType)
{	
	if (!States.Contains(NewStateType))
	{
		UCPP_SM_Cell_Cursor_Base* NewState = NewObject<UCPP_SM_Cell_Cursor_Base>(this, NewStateType);		
		checkf(NewState, TEXT("***> No NewState created (nullptr) <***"));

		States.Emplace(NewStateType, NewState);
		NewState->InitializeState(this);
	}

	CurrentState = States[NewStateType];
	CurrentState->SetState();
}


UCPP_SM_Cell_Cursor_Base* UCPP_SM_Cell_Cursor_Context::GetCurrentState()
{
	checkf(bIsInitialized, TEXT("***> The state machine has not been initialized. Call UCPP_SM_Cell_Cursor_Context::InitStateMachine() first +<***"));
	return CurrentState;
}

