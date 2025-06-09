#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"


#include "CPP_AC_Cell_Base.generated.h"




class ACPP_Cell;
class UCPP_SS_InputEventBus;
class UCPP_SS_CellsManagerEventBus;
class UCPP_DA_GameSettings;
class UCPP_DA_GridSettings;




UCLASS(Abstract, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TFM_PROTOTYPE_API UCPP_AC_Cell_Base : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCPP_AC_Cell_Base();



public:/*Properties*/







public:/*Functions*/






protected:/*Properties*/
	UPROPERTY()
	ACPP_Cell* OwnerCell{ nullptr };

	UPROPERTY()
	UCPP_SS_InputEventBus* InputEventBus;

	UPROPERTY()
	UCPP_SS_CellsManagerEventBus* CellsManagerEventBus;

	UPROPERTY()
	const UCPP_DA_GameSettings* GameSettings{ nullptr };

	UPROPERTY()
	const UCPP_DA_GridSettings* GridSettings{ nullptr };



protected:/*Functions*/
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void InitComponent();
	
		
};
