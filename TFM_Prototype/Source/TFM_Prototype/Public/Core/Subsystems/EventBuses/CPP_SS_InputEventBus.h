#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"



#include "CPP_SS_InputEventBus.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FClickOnCellEvent, const ACPP_Cell*, Cell);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FClickOnGridEvent, int32, StaticMeshInstance);




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





public: /*Functions*/

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void RaiseClickOnCellEvent(const ACPP_Cell* Cell)
	{
		ClickOnCellEventDelegate.Broadcast(Cell);
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void RaiseClickOnGridEvent(int32 StaticMeshInstance)
	{
		ClickOnGridEventDelegate.Broadcast(StaticMeshInstance);
	}






	
};
