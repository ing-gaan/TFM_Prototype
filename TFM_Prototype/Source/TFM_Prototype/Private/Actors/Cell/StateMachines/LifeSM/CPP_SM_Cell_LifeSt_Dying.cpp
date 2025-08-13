#include "Actors/Cell/StateMachines/LifeSM/CPP_SM_Cell_LifeSt_Dying.h"
#include "Actors/Cell/StateMachines/LifeSM/CPP_SM_Cell_Life_Context.h"
#include "Core/GameSettings/CPP_DA_GameSettings.h"
#include "Actors/Cell/CPP_Cell.h"
#include "Actors/Cell/CPP_DA_CellType.h"





void UCPP_SM_Cell_LifeSt_Dying::InitState(UCPP_SM_Cell_Context* Context, int StateSortPosition)
{
	Super::InitState(Context, StateSortPosition);
	UpdateMaxStateTime();
}


void UCPP_SM_Cell_LifeSt_Dying::UpdateMaxStateTime()
{
	float MaxDyingTime = SMContext->OwnerCell->CellType->MaxDyingTime;
	float MaxCellsDyingTimeMultiplier = GameSettings->MaxCellsDyingTimeMultiplier;
	MaxStateTime = MaxDyingTime * MaxCellsDyingTimeMultiplier;
}


const FLinearColor& UCPP_SM_Cell_LifeSt_Dying::GetMaterialColor()
{
	return SMContext->OwnerCell->CellType->NormalColor;
}


