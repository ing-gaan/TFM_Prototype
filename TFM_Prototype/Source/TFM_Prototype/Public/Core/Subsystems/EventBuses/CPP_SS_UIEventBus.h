#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"



#include "CPP_SS_UIEventBus.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBeginDuplicateCellEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBeginTransformCellEvent);


UCLASS()
class TFM_PROTOTYPE_API UCPP_SS_UIEventBus : public UGameInstanceSubsystem
{
	GENERATED_BODY()


public: /*Properties*/

	UPROPERTY(BlueprintAssignable)
	FBeginDuplicateCellEvent BeginDuplicateCellEventDelegate;

	UPROPERTY(BlueprintAssignable)
	FBeginTransformCellEvent BeginTransformCellEventDelegate;

	




public: /*Functions*/

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void RaiseBeginDuplicateCellEvent()
	{
		BeginDuplicateCellEventDelegate.Broadcast();
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void RaiseBeginTransformCellEvent()
	{
		BeginTransformCellEventDelegate.Broadcast();
	}
	
	
	






};
