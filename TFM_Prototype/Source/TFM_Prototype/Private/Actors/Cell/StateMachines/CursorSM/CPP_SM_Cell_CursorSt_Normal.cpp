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

	PRINT("Entra a estado Normal");
	
}


const FLinearColor& UCPP_SM_Cell_CursorSt_Normal::GetMaterialColor()
{
	return SMContext->OwnerCell->CellType->NormalColor;
}


void UCPP_SM_Cell_CursorSt_Normal::NoInteract()
{
	SMContext->ChangeState(UCPP_SM_Cell_CursorSt_NotInteract::StaticClass());
}


void UCPP_SM_Cell_CursorSt_Normal::BeginCursorOver()
{	
	//bool bIsGridActive = UCPP_SS_LocalGameManager::IsGridActive();
	bool bIsACellDividing = UCPP_SS_LocalGameManager::IsACellDividing();

	if (bIsACellDividing)
	{		
		FVector2f ClickedCellAxLoc = UCPP_SS_LocalGameManager::GetCurrentClickedCell()->GetAxialLocation();
		FVector2f OwnerCellAxLoc = SMContext->OwnerCell->GetAxialLocation();
		bool ClickedAndOwnerCellsAreNeighbours = UCPP_FuncLib_CellUtils::AreNeighbours(OwnerCellAxLoc, ClickedCellAxLoc);

		if (ClickedAndOwnerCellsAreNeighbours)
		{
			//----- CODIGO DEBUG ----- 
			SMContext->ChangeState(UCPP_SM_Cell_CursorSt_Shifting::StaticClass());


			SMContext->OwnerCell->NotifyShiftingActivated();
			return;
		}		
	}

	SMContext->ChangeState(UCPP_SM_Cell_CursorSt_Over::StaticClass());
}


void UCPP_SM_Cell_CursorSt_Normal::EndCursorOver()
{
	SMContext->ChangeState(UCPP_SM_Cell_CursorSt_Normal::StaticClass());
}


void UCPP_SM_Cell_CursorSt_Normal::Clicked()
{
	SMContext->ChangeState(UCPP_SM_Cell_CursorSt_Normal::StaticClass());
}

void UCPP_SM_Cell_CursorSt_Normal::Shift()
{
	SMContext->ChangeState(UCPP_SM_Cell_CursorSt_Normal::StaticClass());
}

