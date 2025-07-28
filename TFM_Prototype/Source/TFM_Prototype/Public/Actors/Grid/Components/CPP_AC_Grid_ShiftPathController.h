#pragma once

#include "CoreMinimal.h"
#include "Actors/Grid/Components/CPP_AC_Grid_Base.h"


#include "CPP_AC_Grid_ShiftPathController.generated.h"





class UCPP_Util_AC_Grid_ShiftPathsAdmin;
class UCPP_SS_CellsManagerEventBus;
class UCPP_SS_UIEventBus;
class UCPP_SS_GameEventBus;
class UCPP_SS_InputEventBus;
class ACPP_Cell;
class UCPP_SS_LocalGameManager;
class UCPP_SS_CellsManager;





UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TFM_PROTOTYPE_API UCPP_AC_Grid_ShiftPathController : public UCPP_AC_Grid_Base
{
	GENERATED_BODY()


public:
	UCPP_AC_Grid_ShiftPathController();



public:/*Properties*/



public:/*Functions*/





private:/*Properties*/

	UPROPERTY()
	UCPP_Util_AC_Grid_ShiftPathsAdmin* ShiftPathsAdmin { nullptr };

	UPROPERTY()
	UCPP_SS_CellsManagerEventBus* CellsManagerEventBus{ nullptr };

	UPROPERTY()
	UCPP_SS_UIEventBus* UIEventBus{ nullptr };

	UPROPERTY()
	UCPP_SS_GameEventBus* GameEventBus{ nullptr };

	UPROPERTY()
	UCPP_SS_InputEventBus* InputEventBus{ nullptr };

	UPROPERTY()
	const UCPP_SS_LocalGameManager* GameManager{ nullptr };

	UPROPERTY()
	UCPP_SS_CellsManager* CellsManager{ nullptr };

	UPROPERTY()
	const ACPP_Cell* CurrentClickedCell;


	bool bAreCellShiftPathsStatesUpdated{ false };


private:/*Functions*/

	UFUNCTION()
	void CellsShiftingEvent(const ACPP_Cell* FirstCellToShift);

	UFUNCTION()
	void CellsShiftingReturnEvent();

	UFUNCTION()
	void FinishCellDivisionEvent(FVector2f SpawnAxialLocation);

	UFUNCTION()
	void BeginCellDivisionEvent();

	UFUNCTION()
	void Phase2StartedEvent(UCPP_SS_CellsManager* TheCellsManager, ACPP_Grid* TheGrid);

	UFUNCTION()
	void ClickOnCellEvent(const ACPP_Cell* ClickedCell);

	UFUNCTION()
	void ClickOnAuxGridElemEvent();


	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void InitEventBuses();
	void RegisterEventFunctions() const;
	void UnRegisterEventFunctions() const;

	virtual void InitComponent() override;

	void ShiftPathsUpdate(const ACPP_Cell* CellToDivide);
	bool UpdateLocationsOfCellsInPath();

	//void Phase1();

	

};
