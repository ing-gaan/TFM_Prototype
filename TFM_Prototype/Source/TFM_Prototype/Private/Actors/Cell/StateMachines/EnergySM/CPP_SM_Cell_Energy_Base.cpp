#include "Actors/Cell/StateMachines/EnergySM/CPP_SM_Cell_Energy_Base.h"
#include "Actors/Cell/StateMachines/EnergySM/CPP_SM_Cell_Energy_Context.h"




void UCPP_SM_Cell_Energy_Base::InitializeState(UCPP_SM_Cell_Context* Context)
{
	Super::InitializeState(Context);

	SMContext = Cast<UCPP_SM_Cell_Energy_Context>(Context);
}


void UCPP_SM_Cell_Energy_Base::ImplementState()
{
	SetState();
}


const FLinearColor& UCPP_SM_Cell_Energy_Base::GetMaterialColor()
{
	checkf(false, TEXT("***> Function not implemented. Override without call parent (Not use Super typedef) <***"));
	return FLinearColor::Black;
}