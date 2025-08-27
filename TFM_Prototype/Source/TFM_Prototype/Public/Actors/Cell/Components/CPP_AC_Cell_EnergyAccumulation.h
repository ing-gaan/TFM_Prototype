#pragma once

#include "CoreMinimal.h"
#include "Actors/Cell/Components/CPP_AC_Cell_Base.h"


#include "CPP_AC_Cell_EnergyAccumulation.generated.h"





UCLASS()
class TFM_PROTOTYPE_API UCPP_AC_Cell_EnergyAccumulation : public UCPP_AC_Cell_Base
{
	GENERATED_BODY()



public:/*Properties*/






public:/*Functions*/






protected:/*Properties*/

	int TensMilliSecondsPassed{ 0 };
	int TransferEnergyTimeInterval{ 0 };



protected:/*Functions*/

	UFUNCTION()
	void TenMilliSecondsEvent(int TensMilliSecondsCount);


	void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void RegisterEventFunctions();

	void UnRegisterEventFunctions();
	virtual void InitComponent() override;

	void GetThoseWhoReceiveTheEnergy();

};
