#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_Cursor_Base.h"
#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_Cursor_Context.h"
#include "Actors/Cell/CPP_Cell.h"
#include "Actors/Cell/CPP_DA_CellType.h"




void UCPP_SM_Cell_Cursor_Base::InitializeState(UCPP_SM_Cell_Cursor_Context* Context)
{
	SMContext = Context;
}


void UCPP_SM_Cell_Cursor_Base::SetState()
{	
	SetMaterialColorParameter( GetMaterialColor() );
}


void UCPP_SM_Cell_Cursor_Base::SetMaterialColorParameter(const FLinearColor& MaterialColor)
{
	FName MaterialColorParameterName = SMContext->OwnerCell->CellType->MaterialColorParameterName;
	SMContext->CellMaterialInstance->SetVectorParameterValue(MaterialColorParameterName, MaterialColor);
}



const FLinearColor& UCPP_SM_Cell_Cursor_Base::GetMaterialColor()
{
	//checkf(false, TEXT("***> Function not implemented. Override without call parent (Not use Super typedef) <***"));
	return FLinearColor::Black;
}


bool UCPP_SM_Cell_Cursor_Base::ToNormal()
{
	//checkf(false, TEXT("***> Function not implemented or transition not needed. <***"));
	return false;
}


bool UCPP_SM_Cell_Cursor_Base::NoInteract()
{
	//checkf(false, TEXT("***> Function not implemented or transition not needed. <***"));
	return false;
}


bool UCPP_SM_Cell_Cursor_Base::BeginCursorOver()
{
	//checkf(false, TEXT("***> Function not implemented or transition not needed. <***"));
	return false;
}


bool UCPP_SM_Cell_Cursor_Base::EndCursorOver()
{
	//checkf(false, TEXT("***> Function not implemented or transition not needed. <***"));
	return false;
}


bool UCPP_SM_Cell_Cursor_Base::Clicked()
{
	//checkf(false, TEXT("***> Function not implemented or transition not needed. <***"));
	return false;
}


bool UCPP_SM_Cell_Cursor_Base::Shift()
{
	//checkf(false, TEXT("***> Function not implemented or transition not needed. <***"));
	return false;
}


