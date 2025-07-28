#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_CursorSt_Over.h"
#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_Cursor_Context.h"
#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_CursorSt_Normal.h"
#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_CursorSt_NotInteract.h"
#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_CursorSt_Clicked.h"
#include "Actors/Cell/CPP_Cell.h"
#include "Actors/Cell/CPP_DA_CellType.h"
#include "Utils/Macros/Macros.h"
#include "Utils/Enums/CPP_CellShiftState.h"
#include "Core/Subsystems/Managers/CPP_SS_LocalGameManager.h"





void UCPP_SM_Cell_CursorSt_Over::SetState()
{
	Super::SetState();

	//PRINT("Entra a estado Over");
	
}


const FLinearColor& UCPP_SM_Cell_CursorSt_Over::GetMaterialColor()
{
	return SMContext->OwnerCell->CellType->CursorOverColor;
}


bool UCPP_SM_Cell_CursorSt_Over::NoInteract()
{
	SMContext->ChangeState(UCPP_SM_Cell_CursorSt_NotInteract::StaticClass());

	return true;
}


bool UCPP_SM_Cell_CursorSt_Over::EndCursorOver()
{
	SMContext->ChangeState(UCPP_SM_Cell_CursorSt_Normal::StaticClass());

	return true;
}


bool UCPP_SM_Cell_CursorSt_Over::Clicked()
{
	/*bool bCellIsAtOrigin = SMContext->OwnerCell->GetCellShiftState() == ECPP_CellShiftState::AtOriginLocation;

	if (!bCellIsAtOrigin)
	{
		return false;
	}*/

	if (UCPP_SS_LocalGameManager::AreCellsShifting())
	{		
		return false;
	}

	SMContext->ChangeState(UCPP_SM_Cell_CursorSt_Clicked::StaticClass());


	return true;
}
