#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_CursorSt_Shifting.h"
#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_Cursor_Context.h"
#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_CursorSt_Normal.h"
#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_CursorSt_Clicked.h"
#include "Actors/Cell/CPP_Cell.h"
#include "Actors/Cell/CPP_DA_CellType.h"
#include "Utils/Macros/Macros.h"





void UCPP_SM_Cell_CursorSt_Shifting::SetState()
{
	Super::SetState();

	PRINT("Entra a estado Shift");
}


const FLinearColor& UCPP_SM_Cell_CursorSt_Shifting::GetMaterialColor()
{
	return SMContext->OwnerCell->CellType->ShiftingColor;
}



void UCPP_SM_Cell_CursorSt_Shifting::ToNormal()
{
	SMContext->ChangeState(UCPP_SM_Cell_CursorSt_Normal::StaticClass());
}

void UCPP_SM_Cell_CursorSt_Shifting::BeginCursorOver()
{
	
}

void UCPP_SM_Cell_CursorSt_Shifting::EndCursorOver()
{

}


void UCPP_SM_Cell_CursorSt_Shifting::Clicked()
{
	SMContext->ChangeState(UCPP_SM_Cell_CursorSt_Clicked::StaticClass());
}


void UCPP_SM_Cell_CursorSt_Shifting::Shift()
{
	
}
