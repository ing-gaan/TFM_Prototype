#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_CursorSt_Normal.h"
#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_Cursor_Context.h"
#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_CursorSt_NotInteract.h"
#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_CursorSt_Over.h"
#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_CursorSt_Shifting.h"
#include "Actors/Cell/CPP_Cell.h"
#include "Actors/Cell/CPP_DA_CellType.h"
#include "Core/Subsystems/Managers/CPP_SS_LocalGameManager.h"
#include "Utils/FunctionLibraries/CPP_FuncLib_CellUtils.h"
#include "Utils/Macros/Macros.h"






void UCPP_SM_Cell_CursorSt_Normal::SetState()
{
	Super::SetState();
	SMContext->OwnerCell->Clicked(false);
}


const FLinearColor& UCPP_SM_Cell_CursorSt_Normal::GetMaterialColor()
{
	return SMContext->OwnerCell->CellType->NormalColor;
}


bool UCPP_SM_Cell_CursorSt_Normal::NoInteract()
{
	SMContext->ChangeState(UCPP_SM_Cell_CursorSt_NotInteract::StaticClass());

	return true;
}


bool UCPP_SM_Cell_CursorSt_Normal::BeginCursorOver()
{			

	if (UCPP_SS_LocalGameManager::IsACellDividing())
	{		
		FVector2f ClickedCellAxLoc = UCPP_SS_LocalGameManager::GetCurrentClickedCell()->GetAxialLocation();
		FVector2f OwnerCellAxLoc = SMContext->OwnerCell->GetAxialLocation();
		bool ClickedAndOwnerCellsAreNeighbours = UCPP_FuncLib_CellUtils::AreNeighbours(OwnerCellAxLoc, ClickedCellAxLoc);

		if (ClickedAndOwnerCellsAreNeighbours)
		{			
			SMContext->OwnerCell->NotifyShiftingActivated();
			return false;
		}		
	}

	if (UCPP_SS_LocalGameManager::AreCellsShifting())
	{
		return false;
	}

	SMContext->ChangeState(UCPP_SM_Cell_CursorSt_Over::StaticClass());
	return true;
}



bool UCPP_SM_Cell_CursorSt_Normal::Shift()
{
	SMContext->ChangeState(UCPP_SM_Cell_CursorSt_Shifting::StaticClass());
	
	return true;
}

