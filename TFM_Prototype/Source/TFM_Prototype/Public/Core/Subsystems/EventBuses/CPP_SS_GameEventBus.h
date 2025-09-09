#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"


#include "CPP_SS_GameEventBus.generated.h"




DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPhase1StartedEvent, ACPP_Grid*, TheGrid);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPhase2StartedEvent, UCPP_SS_CellsManager*, CellsManager, ACPP_Grid*, Grid);




UCLASS()
class TFM_PROTOTYPE_API UCPP_SS_GameEventBus : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	



public: /*Properties*/

	UPROPERTY(BlueprintAssignable)
	FPhase1StartedEvent Phase1StartedEventDelegate;
	FPhase2StartedEvent Phase2StartedEventDelegate;






public: /*Functions*/

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void RaisePhase1StartedEvent(ACPP_Grid* TheGrid)  const
	{
		Phase1StartedEventDelegate.Broadcast(TheGrid);
	}


	UFUNCTION(BlueprintCallable)
	FORCEINLINE void RaisePhase2StartedEvent(UCPP_SS_CellsManager* CellsManager, ACPP_Grid* Grid)  const
	{
		Phase2StartedEventDelegate.Broadcast(CellsManager, Grid);
	}











	
};
