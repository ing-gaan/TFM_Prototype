#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"


#include "CPP_SS_TimeEventBus.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTenMilliSecondsEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOneSecondEvent);
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
	FORCEINLINE void RaiseTenMilliSecondsEvent() const
	{
		TenMilliSecondsEventDelegate.Broadcast();
	}


	UFUNCTION()
	FORCEINLINE void RaiseOneSecondEvent() const
	{
		OneSecondEventDelegate.Broadcast();
	}


	UFUNCTION()
	FORCEINLINE void RaiseTenSecondsEvent() const
	{
		TenSecondsEventDelegate.Broadcast();
	}
	
};
