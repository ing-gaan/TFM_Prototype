#include "Actors/Cell/Components/CPP_AC_Cell_Base.h"
#include "Actors/Cell/CPP_Cell.h"
#include "Core/Subsystems/EventBuses/CPP_SS_InputEventBus.h"
#include "Core/GameInstance/CPP_GameInstance.h"
#include "Core/GameSettings/CPP_DA_GameSettings.h"




UCPP_AC_Cell_Base::UCPP_AC_Cell_Base()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UCPP_AC_Cell_Base::BeginPlay()
{
	Super::BeginPlay();

	InitComponent();
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

	UWorld* World = GetWorld();
	checkf(World, TEXT("***> No World (nullptr) <***"));

	UCPP_GameInstance* GameInstance = Cast<UCPP_GameInstance>(World->GetGameInstance());
	checkf(GameInstance, TEXT("***> No GameInstance (nullptr) <***"));

	GameSettings = GameInstance->GameSettings;
	GridSettings = GameSettings->GridSettings;

	InputEventBus = GameInstance->GetSubsystem<UCPP_SS_InputEventBus>();
	checkf(InputEventBus, TEXT("***> No InputEventBus (nullptr) <***"));

}

