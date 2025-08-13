#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_Cursor_Base.h"
#include "Actors/Cell/StateMachines/CursorSM/CPP_SM_Cell_Cursor_Context.h"
#include "Actors/Cell/CPP_Cell.h"
#include "Actors/Cell/CPP_DA_CellType.h"




void UCPP_SM_Cell_Cursor_Base::InitializeState(UCPP_SM_Cell_Context* Context)
{
	Super::InitializeState(Context);

	SMContext = Cast<UCPP_SM_Cell_Cursor_Context>(Context);
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


