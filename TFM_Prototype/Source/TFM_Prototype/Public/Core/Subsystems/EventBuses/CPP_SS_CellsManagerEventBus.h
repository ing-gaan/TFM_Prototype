#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"


#include "CPP_SS_CellsManagerEventBus.generated.h"




DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFinishCellDivisionEvent, FVector2f, SpawnAxialLocation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMoveCellsEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCellsShiftingEvent, bool, ShouldCellsShiftLocation);




UCLASS()
class TFM_PROTOTYPE_API UCPP_SS_CellsManagerEventBus : public UGameInstanceSubsystem
{
	GENERATED_BODY()



public: /*Properties*/

	UPROPERTY(BlueprintAssignable)
	FFinishCellDivisionEvent FinishCellDivisionEventDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FMoveCellsEvent MoveCellsEventDelegate;

	UPROPERTY(BlueprintAssignable)
	FCellsShiftingEvent CellsShiftingEventDelegate;



public: /*Functions*/

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void RaiseFinishCellDivisionEvent(FVector2f SpawnAxialLocation)
	{
		FinishCellDivisionEventDelegate.Broadcast(SpawnAxialLocation);
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void RaiseMoveCellsEvent()
	{
		MoveCellsEventDelegate.Broadcast();
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void RaiseCellsShiftingEvent(bool ShouldCellsShiftLocation)
	{
		CellsShiftingEventDelegate.Broadcast(ShouldCellsShiftLocation);
	}

};
