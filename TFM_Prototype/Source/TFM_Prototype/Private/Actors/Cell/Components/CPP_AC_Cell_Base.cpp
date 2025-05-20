#include "Actors/Cell/Components/CPP_AC_Cell_Base.h"
#include "Actors/Cell/CPP_Cell.h"




UCPP_AC_Cell_Base::UCPP_AC_Cell_Base()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCPP_AC_Cell_Base::BeginPlay()
{
	Super::BeginPlay();
}

void UCPP_AC_Cell_Base::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UCPP_AC_Cell_Base::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}



void UCPP_AC_Cell_Base::InitComponent()
{
	OwnerCell = Cast<ACPP_Cell>(GetOwner());
	checkf(OwnerCell, TEXT("*****> No OwnerCell (nullptr) <*****"));
}

