#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_CursorSt_Init.h"
#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_Cursor_Context.h"
#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_CursorSt_Normal.h"
#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_CursorSt_Over.h"
#include "Actors/Cell/CPP_Cell.h"
#include "Actors/Cell/CPP_DA_CellType.h"
#include "Utils/Macros/Macros.h"





void UCPP_SM_Cell_CursorSt_Init::SetState()
{
	Super::SetState();

	//PRINT("Entra a estado Init");
}


const FLinearColor& UCPP_SM_Cell_CursorSt_Init::GetMaterialColor()
{	
	return SMContext->OwnerCell->CellType->NormalColor;
}


void UCPP_SM_Cell_CursorSt_Init::ToNormal()
{
	SMContext->ChangeState(UCPP_SM_Cell_CursorSt_Normal::StaticClass());
}


void UCPP_SM_Cell_CursorSt_Init::BeginCursorOver()
{
	SMContext->ChangeState(UCPP_SM_Cell_CursorSt_Over::StaticClass());
}

void UCPP_SM_Cell_CursorSt_Init::EndCursorOver()
{
	SMContext->ChangeState(UCPP_SM_Cell_CursorSt_Normal::StaticClass());
}

void UCPP_SM_Cell_CursorSt_Init::Clicked()
{
	SMContext->ChangeState(UCPP_SM_Cell_CursorSt_Normal::StaticClass());
}
