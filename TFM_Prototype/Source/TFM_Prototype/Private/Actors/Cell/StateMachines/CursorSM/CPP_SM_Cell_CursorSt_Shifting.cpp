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
}


const FLinearColor& UCPP_SM_Cell_CursorSt_Shifting::GetMaterialColor()
{
	return SMContext->OwnerCell->CellType->ShiftingColor;
}


bool UCPP_SM_Cell_CursorSt_Shifting::ToNormal()
{
	SMContext->ChangeState(UCPP_SM_Cell_CursorSt_Normal::StaticClass());

	return true;
}


