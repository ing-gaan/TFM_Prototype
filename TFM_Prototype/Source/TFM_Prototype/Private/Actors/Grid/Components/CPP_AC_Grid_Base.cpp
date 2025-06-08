#include "Actors/Grid/Components/CPP_AC_Grid_Base.h"
#include "Actors/Grid/CPP_Grid.h"
#include "Core/GameInstance/CPP_GameInstance.h"
#include "Core/GameSettings/CPP_DA_GameSettings.h"



UCPP_AC_Grid_Base::UCPP_AC_Grid_Base()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCPP_AC_Grid_Base::BeginPlay()
{
	Super::BeginPlay();
}

void UCPP_AC_Grid_Base::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UCPP_AC_Grid_Base::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}



void UCPP_AC_Grid_Base::InitComponent()
{
	OwnerGrid = Cast<ACPP_Grid>(GetOwner());
	checkf(OwnerGrid, TEXT("*****> No OwnerCell (nullptr) <*****"));

	UWorld* World = GetWorld();
	checkf(World, TEXT("***> No World (nullptr) <***"));

	UCPP_GameInstance* GameInstance = Cast<UCPP_GameInstance>(World->GetGameInstance());
	checkf(GameInstance, TEXT("***> No GameInstance (nullptr) <***"));

	GameSettings = GameInstance->GameSettings;
	GridSettings = GameSettings->GridSettings;
}
