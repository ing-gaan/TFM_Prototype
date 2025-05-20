#include "Actors/Grid/Components/UCPP_AC_Grid_Base.h"
#include "Actors/Grid/CPP_Grid.h"



UUCPP_AC_Grid_Base::UUCPP_AC_Grid_Base()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UUCPP_AC_Grid_Base::BeginPlay()
{
	Super::BeginPlay();
}

void UUCPP_AC_Grid_Base::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UUCPP_AC_Grid_Base::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}



void UUCPP_AC_Grid_Base::InitComponent()
{
	OwnerGrid = Cast<ACPP_Grid>(GetOwner());
	checkf(OwnerGrid, TEXT("*****> No OwnerCell (nullptr) <*****"));
}
