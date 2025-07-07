#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_CursorSt_NotInteract.h"
#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_Cursor_Context.h"
#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_CursorSt_Normal.h"
#include "Actors/Cell/CPP_Cell.h"
#include "Actors/Cell/CPP_DA_CellType.h"
#include "Utils/Macros/Macros.h"





void UCPP_SM_Cell_CursorSt_NotInteract::SetState()
{
	Super::SetState();

	PRINT("Entra a estado NoInteract");
}



const FLinearColor& UCPP_SM_Cell_CursorSt_NotInteract::GetMaterialColor()
{
	return SMContext->OwnerCell->CellType->NotInteractiveColor;
}


void UCPP_SM_Cell_CursorSt_NotInteract::ToNormal()
{
	SMContext->ChangeState(UCPP_SM_Cell_CursorSt_Normal::StaticClass());
}

void UCPP_SM_Cell_CursorSt_NotInteract::NoInteract()
{
	SMContext->ChangeState(UCPP_SM_Cell_CursorSt_NotInteract::StaticClass());
}


void UCPP_SM_Cell_CursorSt_NotInteract::BeginCursorOver()
{
	SMContext->ChangeState(UCPP_SM_Cell_CursorSt_NotInteract::StaticClass());
}


void UCPP_SM_Cell_CursorSt_NotInteract::EndCursorOver()
{
	SMContext->ChangeState(UCPP_SM_Cell_CursorSt_NotInteract::StaticClass());
}


void UCPP_SM_Cell_CursorSt_NotInteract::Clicked()
{
	SMContext->ChangeState(UCPP_SM_Cell_CursorSt_NotInteract::StaticClass());
}

void UCPP_SM_Cell_CursorSt_NotInteract::Shift()
{
	SMContext->ChangeState(UCPP_SM_Cell_CursorSt_NotInteract::StaticClass());
}
