#include "Actors/Cell/StateMachines/LifeSM/CPP_SM_Cell_LifeSt_OldAge.h"
#include "Actors/Cell/StateMachines/LifeSM/CPP_SM_Cell_Life_Context.h"
#include "Core/GameSettings/CPP_DA_GameSettings.h"
#include "Actors/Cell/CPP_Cell.h"
#include "Actors/Cell/CPP_DA_CellType.h"





void UCPP_SM_Cell_LifeSt_OldAge::InitState(UCPP_SM_Cell_Context* Context, int StateSortPosition)
{
	Super::InitState(Context, StateSortPosition);
	UpdateMaxStateTime();
	LifeStateName = FText::FromStringTable(UserTextsStringTableId, TEXT("State_OldAge"));
}


void UCPP_SM_Cell_LifeSt_OldAge::UpdateMaxStateTime()
{
	float MaxOldAgeTime = SMContext->OwnerCell->CellType->MaxOldAgeTime;
	float MaxCellsOldAgeTimeMultiplier = GameSettings->MaxCellsOldAgeTimeMultiplier;
	MaxStateTime = MaxOldAgeTime * MaxCellsOldAgeTimeMultiplier;
}


const FLinearColor& UCPP_SM_Cell_LifeSt_OldAge::GetMaterialColor()
{
	return SMContext->OwnerCell->CellType->NormalColor;
}


