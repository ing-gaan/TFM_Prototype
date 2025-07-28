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
	SMContext->OwnerCell->Clicked(true);
}

bool UCPP_SM_Cell_CursorSt_Clicked::ToNormal()
{
	SMContext->ChangeState(UCPP_SM_Cell_CursorSt_Normal::StaticClass());

	return true;
}


bool UCPP_SM_Cell_CursorSt_Clicked::NoInteract()
{
	SMContext->ChangeState(UCPP_SM_Cell_CursorSt_NotInteract::StaticClass());

	return true;
}


bool UCPP_SM_Cell_CursorSt_Clicked::BeginCursorOver()
{
	if (UCPP_SS_LocalGameManager::AreCellsShifting())
	{
		SMContext->OwnerCell->NotifyShiftingCanceled();
		return false;
	}

	return false;
}


