#include "Actors/Cell/Components/CPP_AC_Cell_Base.h"
#include "Actors/Cell/CPP_Cell.h"




UCPP_AC_Cell_Base::UCPP_AC_Cell_Base()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UCPP_AC_Cell_Base::InitComponent()
{
	OwnerCell = Cast<ACPP_Cell>(GetOwner());
	checkf(OwnerCell, TEXT("*****> No OwnerCell (nullptr) <*****"));
}

