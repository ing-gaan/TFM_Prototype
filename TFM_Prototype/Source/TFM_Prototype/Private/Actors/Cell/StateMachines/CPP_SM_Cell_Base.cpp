#include "Actors/Cell/StateMachines/CPP_SM_Cell_Base.h"
#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_Cursor_Context.h"
#include "Actors/Cell/CPP_Cell.h"
#include "Actors/Cell/CPP_DA_CellType.h"
#include "Core/GameInstance/CPP_GameInstance.h"





void UCPP_SM_Cell_Base::InitializeState(UCPP_SM_Cell_Context* Context)
{
	BaseSMContext = Context;

	UCPP_GameInstance* GameInstance = Cast<UCPP_GameInstance>(Context->World->GetGameInstance());
	checkf(GameInstance, TEXT("***> No GameInstance (nullptr) <***"));

	GameSettings = GameInstance->GameSettings;
}


void UCPP_SM_Cell_Base::SetState()
{
	const FLinearColor& MaterialColor = GetMaterialColor();
	SetMaterialColorParameter(MaterialColor);
	BaseSMContext->CurrentCellColor = MaterialColor;
}


void UCPP_SM_Cell_Base::SetMaterialColorParameter(const FLinearColor& MaterialColor)
{
	FName MaterialColorParameterName = BaseSMContext->OwnerCell->CellType->MaterialColorParameterName;
	BaseSMContext->CellMaterialInstance->SetVectorParameterValue(MaterialColorParameterName, MaterialColor);
}



const FLinearColor& UCPP_SM_Cell_Base::GetMaterialColor()
{
	checkf(false, TEXT("***> Function not implemented. Override without call parent (Not use Super typedef) <***"));
	return FLinearColor::Black;
}



void UCPP_SM_Cell_Base::ImplementState()
{
	checkf(false, TEXT("***> Function not implemented or transition not needed. <***"));
}