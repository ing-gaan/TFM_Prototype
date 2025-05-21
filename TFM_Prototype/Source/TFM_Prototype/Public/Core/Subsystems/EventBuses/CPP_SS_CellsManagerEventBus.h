#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"


#include "CPP_SS_CellsManagerEventBus.generated.h"




DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFinishDuplicateCellEvent, FVector2f, SpawnAxialLocation);



UCLASS()
class TFM_PROTOTYPE_API UCPP_SS_CellsManagerEventBus : public UGameInstanceSubsystem
{
	GENERATED_BODY()



public: /*Properties*/

	UPROPERTY(BlueprintAssignable)
	FFinishDuplicateCellEvent FinishDuplicateCellEventDelegate;



public: /*Functions*/

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void RaiseFinishDuplicateCellEvent(FVector2f SpawnAxialLocation)
	{
		FinishDuplicateCellEventDelegate.Broadcast(SpawnAxialLocation);
	}


};
