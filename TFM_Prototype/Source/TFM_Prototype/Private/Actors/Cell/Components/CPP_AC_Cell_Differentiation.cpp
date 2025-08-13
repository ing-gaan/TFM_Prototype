#include "Actors/Cell/Components/CPP_AC_Cell_Differentiation.h"
#include "Actors/Cell/CPP_Cell.h"
#include "Actors/Cell/CPP_DA_CellType.h"




void UCPP_AC_Cell_Differentiation::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UnRegisterEventFunctions();
}


void UCPP_AC_Cell_Differentiation::InitComponent()
{
	Super::InitComponent();
	RegisterEventFunctions();
}


void UCPP_AC_Cell_Differentiation::RegisterEventFunctions() const
{
	OwnerCell->BeginDifferentiateEventDelegate.BindDynamic(this, &UCPP_AC_Cell_Differentiation::BeginDifferentiateEvent);
}


void UCPP_AC_Cell_Differentiation::UnRegisterEventFunctions() const
{
	OwnerCell->BeginDifferentiateEventDelegate.Clear();
	
}


bool UCPP_AC_Cell_Differentiation::BeginDifferentiateEvent(const UCPP_DA_CellType* NewType)
{
	OwnerCell->CellType = NewType;

	if (OwnerCell->LoadCellTypeComponents(NewType))
	{
		OwnerCell->FinishDifferentiate();
		return true;
	}

	return false;
}


