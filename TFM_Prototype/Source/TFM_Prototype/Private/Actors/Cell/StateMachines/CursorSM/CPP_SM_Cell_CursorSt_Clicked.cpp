#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_CursorSt_Clicked.h"
#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_Cursor_Context.h"
#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_CursorSt_Normal.h"
#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_CursorSt_NotInteract.h"
#include "Actors/Cell/CPP_Cell.h"
#include "Actors/Cell/CPP_DA_CellType.h"
#include "Core/Subsystems/Managers/CPP_SS_LocalGameManager.h"
#include "Utils/Macros/Macros.h"








const FLinearColor& UCPP_SM_Cell_CursorSt_Clicked::GetMaterialColor()
{
	return SMContext->OwnerCell->CellType->ClickedColor;
}


void UCPP_SM_Cell_CursorSt_Clicked::SetState()
{
	Super::SetState();

	PRINT("Entra a estado Clicked");
}

void UCPP_SM_Cell_CursorSt_Clicked::ToNormal()
{
	SMContext->ChangeState(UCPP_SM_Cell_CursorSt_Normal::StaticClass());
}


void UCPP_SM_Cell_CursorSt_Clicked::NoInteract()
{
	SMContext->ChangeState(UCPP_SM_Cell_CursorSt_NotInteract::StaticClass());
}


void UCPP_SM_Cell_CursorSt_Clicked::BeginCursorOver()
{
	if (UCPP_SS_LocalGameManager::AreCellsShifting())
	{
		SMContext->OwnerCell->NotifyShiftingCanceled();
	}
	SMContext->ChangeState(UCPP_SM_Cell_CursorSt_Clicked::StaticClass());
}


void UCPP_SM_Cell_CursorSt_Clicked::EndCursorOver()
{
	SMContext->ChangeState(UCPP_SM_Cell_CursorSt_Clicked::StaticClass());
}


void UCPP_SM_Cell_CursorSt_Clicked::Clicked()
{
	SMContext->ChangeState(UCPP_SM_Cell_CursorSt_Clicked::StaticClass());
}
