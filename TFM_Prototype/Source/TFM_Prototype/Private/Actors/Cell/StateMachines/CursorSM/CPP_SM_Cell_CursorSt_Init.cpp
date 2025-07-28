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
}


const FLinearColor& UCPP_SM_Cell_CursorSt_Init::GetMaterialColor()
{	
	return SMContext->OwnerCell->CellType->NormalColor;
}


//bool UCPP_SM_Cell_CursorSt_Init::ToNormal()
//{
//	PRINT("NOMAL DESDE INIT");
//	//SMContext->ChangeState(UCPP_SM_Cell_CursorSt_Normal::StaticClass());
//
//	return true;
//}


bool UCPP_SM_Cell_CursorSt_Init::BeginCursorOver()
{
	SMContext->ChangeState(UCPP_SM_Cell_CursorSt_Over::StaticClass());
	return true;
}


