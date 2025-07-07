#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_CursorSt_Over.h"
#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_Cursor_Context.h"
#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_CursorSt_Normal.h"
#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_CursorSt_NotInteract.h"
#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_CursorSt_Clicked.h"
#include "Actors/Cell/CPP_Cell.h"
#include "Actors/Cell/CPP_DA_CellType.h"
#include "Utils/Macros/Macros.h"





void UCPP_SM_Cell_CursorSt_Over::SetState()
{
	Super::SetState();

	//PRINT("Entra a estado Over");
}


const FLinearColor& UCPP_SM_Cell_CursorSt_Over::GetMaterialColor()
{
	return SMContext->OwnerCell->CellType->CursorOverColor;
}


void UCPP_SM_Cell_CursorSt_Over::NoInteract()
{
	SMContext->ChangeState(UCPP_SM_Cell_CursorSt_NotInteract::StaticClass());
}


void UCPP_SM_Cell_CursorSt_Over::EndCursorOver()
{
	SMContext->ChangeState(UCPP_SM_Cell_CursorSt_Normal::StaticClass());
}


void UCPP_SM_Cell_CursorSt_Over::Clicked()
{
	SMContext->ChangeState(UCPP_SM_Cell_CursorSt_Clicked::StaticClass());
}
