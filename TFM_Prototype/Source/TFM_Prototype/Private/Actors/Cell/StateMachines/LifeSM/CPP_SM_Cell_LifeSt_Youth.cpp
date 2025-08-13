#include "Actors/Cell/StateMachines/LifeSM/CPP_SM_Cell_LifeSt_Youth.h"
#include "Actors/Cell/StateMachines/LifeSM/CPP_SM_Cell_Life_Context.h"
#include "Core/GameSettings/CPP_DA_GameSettings.h"
#include "Actors/Cell/CPP_Cell.h"
#include "Actors/Cell/CPP_DA_CellType.h"




void UCPP_SM_Cell_LifeSt_Youth::InitState(UCPP_SM_Cell_Context* Context, int StateSortPosition)
{
	Super::InitState(Context, StateSortPosition);
	UpdateMaxStateTime();
}


void UCPP_SM_Cell_LifeSt_Youth::UpdateMaxStateTime()
{
	float MaxYouthTime = SMContext->OwnerCell->CellType->MaxYouthTime;
	float MaxCellsYouthTimeMultiplier = GameSettings->MaxCellsYouthTimeMultiplier;
	MaxStateTime = MaxYouthTime * MaxCellsYouthTimeMultiplier;
}


const FLinearColor& UCPP_SM_Cell_LifeSt_Youth::GetMaterialColor()
{
	return SMContext->OwnerCell->CellType->NormalColor;
}
