#include "Actors/Cell/StateMachines/LifeSM/CPP_SM_Cell_LifeSt_Init.h"
#include "Actors/Cell/StateMachines/LifeSM/CPP_SM_Cell_Life_Context.h"
#include "Core/GameSettings/CPP_DA_GameSettings.h"
#include "Actors/Cell/CPP_Cell.h"
#include "Actors/Cell/CPP_DA_CellType.h"





void UCPP_SM_Cell_LifeSt_Init::InitState(UCPP_SM_Cell_Context* Context, int StateSortPosition)
{
	Super::InitState(Context, StateSortPosition);
	UpdateMaxStateTime();
	LifeStateName = FText::FromStringTable(UserTextsStringTableId, TEXT("State_Init"));
}


void UCPP_SM_Cell_LifeSt_Init::UpdateMaxStateTime()
{
	MaxStateTime = 0;
}


const FLinearColor& UCPP_SM_Cell_LifeSt_Init::GetMaterialColor()
{
	return SMContext->OwnerCell->CellType->NormalColor;
}



