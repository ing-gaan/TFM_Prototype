#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"



#include "CPP_SS_InputEventBus.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FClickOnCellEvent, const ACPP_Cell*, Cell);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FClickOnGridEvent, FVector2f, AxialLocation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCancelEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FClickOnAuxGridElemEvent);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBeginCursorOverEvent, const AActor*, Actor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndCursorOverEvent);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPauseGameEvent, bool, bIsGamePaused);



class ACPP_Cell;



UCLASS()
class TFM_PROTOTYPE_API UCPP_SS_InputEventBus : public UGameInstanceSubsystem
{
	GENERATED_BODY()


public: /*Properties*/

	UPROPERTY(BlueprintAssignable)
	FClickOnCellEvent ClickOnCellEventDelegate;

	UPROPERTY(BlueprintAssignable)
	FClickOnGridEvent ClickOnGridEventDelegate;

	UPROPERTY(BlueprintAssignable)
	FCancelEvent CancelEventDelegate;

	UPROPERTY(BlueprintAssignable)
	FClickOnAuxGridElemEvent ClickOnAuxGridElemEventDelegate;

	UPROPERTY(BlueprintAssignable)
	FBeginCursorOverEvent BeginCursorOverEventDelegate;

	UPROPERTY(BlueprintAssignable)
	FEndCursorOverEvent EndCursorOverEventDelegate;

	UPROPERTY(BlueprintAssignable)
	FPauseGameEvent PauseGameEventDelegate;




public: /*Functions*/
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void RaiseClickOnCellEvent(const ACPP_Cell* Cell) const
	{
		ClickOnCellEventDelegate.Broadcast(Cell);
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void RaiseClickOnGridEvent(FVector2f AxialLocation) const
	{
		ClickOnGridEventDelegate.Broadcast(AxialLocation);
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void RaiseCancelEvent() const
	{
		CancelEventDelegate.Broadcast();
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void RaiseClickOnAuxGridElemEvent() const
	{
		ClickOnAuxGridElemEventDelegate.Broadcast();
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void RaiseBeginCursorOverEvent(const AActor* Actor) const
	{
		BeginCursorOverEventDelegate.Broadcast(Actor);
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void RaiseEndCursorOverEvent() const
	{
		EndCursorOverEventDelegate.Broadcast();
	}


	UFUNCTION(BlueprintCallable)
	FORCEINLINE void RaisePauseGameEvent(bool bIsGamePaused) const
	{
		PauseGameEventDelegate.Broadcast(bIsGamePaused);
	}


	
};
