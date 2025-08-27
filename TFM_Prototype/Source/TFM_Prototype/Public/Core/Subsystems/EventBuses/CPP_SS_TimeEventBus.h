#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"


#include "CPP_SS_TimeEventBus.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTenMilliSecondsEvent, int, TensMilliSecondsCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOneSecondEvent, int, SecondsCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTenSecondsEvent);




UCLASS()
class TFM_PROTOTYPE_API UCPP_SS_TimeEventBus : public UGameInstanceSubsystem
{
	GENERATED_BODY()


public: /*Properties*/

	UPROPERTY()
	FTenMilliSecondsEvent TenMilliSecondsEventDelegate;

	UPROPERTY()
	FOneSecondEvent OneSecondEventDelegate;

	UPROPERTY()
	FTenSecondsEvent TenSecondsEventDelegate;



public: /*Functions*/

	UFUNCTION()
	FORCEINLINE void RaiseTenMilliSecondsEvent(int TensMilliSecondsCount) const
	{
		TenMilliSecondsEventDelegate.Broadcast(TensMilliSecondsCount);
	}


	UFUNCTION()
	FORCEINLINE void RaiseOneSecondEvent(int SecondsCount) const
	{
		OneSecondEventDelegate.Broadcast(SecondsCount);
	}


	UFUNCTION()
	FORCEINLINE void RaiseTenSecondsEvent() const
	{
		TenSecondsEventDelegate.Broadcast();
	}
	
};
