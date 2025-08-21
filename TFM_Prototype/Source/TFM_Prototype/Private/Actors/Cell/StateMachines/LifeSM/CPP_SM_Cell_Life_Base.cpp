#include "Actors/Cell/StateMachines/LifeSM/CPP_SM_Cell_Life_Base.h"
#include "Actors/Cell/StateMachines/LifeSM/CPP_SM_Cell_Life_Context.h"
#include "Actors/Cell/CPP_Cell.h"
#include "Actors/Cell/CPP_DA_CellType.h"
#include "Core/GameInstance/CPP_GameInstance.h"
#include "Core/GameSettings/CPP_DA_GameSettings.h"
#include "Internationalization/StringTable.h"




void UCPP_SM_Cell_Life_Base::InitState(UCPP_SM_Cell_Context* Context, int StateSortPosition)
{
	SortPosition = StateSortPosition;
	InitializeState(Context);
	UserTextsStringTableId = GameSettings->GameTextsStringTable->GetStringTableId();
}



FText UCPP_SM_Cell_Life_Base::GetLifeStateName() const
{
	return LifeStateName;
}


void UCPP_SM_Cell_Life_Base::InitializeState(UCPP_SM_Cell_Context* Context)
{
	Super::InitializeState(Context);

	SMContext = Cast<UCPP_SM_Cell_Life_Context>(Context);
	bStateInitiated = true;
	LifeStateTimeDecreaseRate = SMContext->OwnerCell->CellType->LifeStateTimeDecreaseRate;

	UCPP_GameInstance* GameInstance = Cast<UCPP_GameInstance>(Context->World->GetGameInstance());
	checkf(GameInstance, TEXT("***> No GameInstance (nullptr) <***"));

	GameSettings = GameInstance->GameSettings;
}



void UCPP_SM_Cell_Life_Base::ImplementState()
{
	RemainingStateTime = MaxStateTime;
	SetState();
}



void UCPP_SM_Cell_Life_Base::DecreaseStateTime()
{
	RemainingStateTime -= LifeStateTimeDecreaseRate;
}


float UCPP_SM_Cell_Life_Base::GetRemainingStateTime() const
{
	return RemainingStateTime;
}

float UCPP_SM_Cell_Life_Base::GetMaxStateTime() const
{
	return MaxStateTime;
}


bool UCPP_SM_Cell_Life_Base::StateTimeFinished() const
{
	if (RemainingStateTime <= 0)
	{
		return true;
	}
	return false;
}


int UCPP_SM_Cell_Life_Base::GetStateSortPosition() const
{
	return SortPosition;
}


bool UCPP_SM_Cell_Life_Base::IsThisEqualOrOlderThan(TSubclassOf<UCPP_SM_Cell_Life_Base> LifeStage) const
{
	int ValueOfStateToCompare = SMContext->GetStateSortPosition(LifeStage);
	int ValueOfThisState = SortPosition;

	if (ValueOfThisState >= ValueOfStateToCompare)
	{
		return true;
	}
	return false;
}


void UCPP_SM_Cell_Life_Base::ChangeToNewCellTypeState()
{
	float PercentageOfCurrentTime = RemainingStateTime / MaxStateTime;
	UpdateMaxStateTime();
	RemainingStateTime = MaxStateTime * PercentageOfCurrentTime;
}


void UCPP_SM_Cell_Life_Base::UpdateMaxStateTime()
{
	checkf(false, TEXT("***> Method not implemented <***"));
}


const FLinearColor& UCPP_SM_Cell_Life_Base::GetMaterialColor()
{
	checkf(false, TEXT("***> Function not implemented. Override without call parent (Not use Super typedef) <***"));
	return FLinearColor::Black;
}
