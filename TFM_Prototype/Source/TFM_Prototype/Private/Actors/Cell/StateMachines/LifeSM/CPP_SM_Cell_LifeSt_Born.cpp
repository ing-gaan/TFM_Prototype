#include "Actors/Cell/StateMachines/LifeSM/CPP_SM_Cell_LifeSt_Born.h"
#include "Actors/Cell/StateMachines/LifeSM/CPP_SM_Cell_Life_Context.h"
#include "Core/GameSettings/CPP_DA_GameSettings.h"
#include "Actors/Cell/CPP_Cell.h"
#include "Actors/Cell/CPP_DA_CellType.h"





void UCPP_SM_Cell_LifeSt_Born::InitState(UCPP_SM_Cell_Context* Context, int StateSortPosition)
{
	Super::InitState(Context, StateSortPosition);
	UpdateMaxStateTime();
}


void UCPP_SM_Cell_LifeSt_Born::UpdateMaxStateTime()
{
	float MaxBornTime = SMContext->OwnerCell->CellType->MaxBornTime;
	float MaxCellsBornTimeMultiplier = GameSettings->MaxCellsBornTimeMultiplier;
	MaxStateTime = MaxBornTime * MaxCellsBornTimeMultiplier;
}


const FLinearColor& UCPP_SM_Cell_LifeSt_Born::GetMaterialColor()
{
	return SMContext->OwnerCell->CellType->NormalColor;
}



