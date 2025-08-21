#include "Actors/Cell/StateMachines/LifeSM/CPP_SM_Cell_LifeSt_Dead.h"
#include "Actors/Cell/StateMachines/LifeSM/CPP_SM_Cell_Life_Context.h"
#include "Core/GameSettings/CPP_DA_GameSettings.h"
#include "Actors/Cell/CPP_Cell.h"
#include "Actors/Cell/CPP_DA_CellType.h"




void UCPP_SM_Cell_LifeSt_Dead::InitState(UCPP_SM_Cell_Context* Context, int StateSortPosition)
{
	Super::InitState(Context, StateSortPosition);
	UpdateMaxStateTime();
	LifeStateName = FText::FromStringTable(UserTextsStringTableId, TEXT("State_Dead"));
}


void UCPP_SM_Cell_LifeSt_Dead::UpdateMaxStateTime()
{
	float MaxDeadTime = SMContext->OwnerCell->CellType->MaxDeadTime;
	float MaxCellsDeadTimeMultiplier = GameSettings->MaxCellsDeadTimeMultiplier;
	MaxStateTime = MaxDeadTime * MaxCellsDeadTimeMultiplier;
}


const FLinearColor& UCPP_SM_Cell_LifeSt_Dead::GetMaterialColor()
{
	return SMContext->OwnerCell->CellType->NormalColor;
}


