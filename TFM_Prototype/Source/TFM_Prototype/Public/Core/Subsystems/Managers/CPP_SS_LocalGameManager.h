#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"


#include "CPP_SS_LocalGameManager.generated.h"




class ACPP_Cell;
class UCPP_SS_InputEventBus;
class UCPP_SS_CellsManagerEventBus;
class UCPP_SS_UIEventBus;
class UCPP_SS_CellsManager;
class UCPP_SS_GameEventBus;
class ACPP_Grid;
enum class ECPPE_CellShiftState : uint8;





UCLASS()
class TFM_PROTOTYPE_API UCPP_SS_LocalGameManager : public ULocalPlayerSubsystem
{
	GENERATED_BODY()



public:/*Properties*/

	static ECPPE_CellShiftState AuxGridElemShiftState;



public:/*Functions*/
	
	static const ACPP_Cell* GetCurrentClickedCell();
	static const ACPP_Cell* GetBeforeClickedCell();
	static bool IsGridActive();
	static bool AreCellsShifting();
	static bool IsACellDividing();
	void StartManager(const UCPP_SS_CellsManager* TheCellsManager, const ACPP_Grid* TheGrid);

	const UCPP_SS_CellsManager* GetCellsManager() const;
	const ACPP_Grid* GetGrid() const;



private:/*Properties*/

	static const ACPP_Cell* CurrentClickedCell;
	static const ACPP_Cell* BeforeClickedCell;
	static bool bIsGridActive;
	static bool bAreCellsShifting;
	static bool bIsACellDividing;



	UPROPERTY()
	UCPP_SS_InputEventBus* InputEventBus{ nullptr };

	UPROPERTY()
	UCPP_SS_CellsManagerEventBus* CellsManagerEventBus{ nullptr };

	UPROPERTY()
	UCPP_SS_UIEventBus* UIEventBus{ nullptr };

	UPROPERTY()
	UCPP_SS_GameEventBus* GameEventBus{ nullptr };

	UPROPERTY()
	const UCPP_SS_CellsManager* CellsManager{ nullptr };

	UPROPERTY()
	const ACPP_Grid* Grid;
	
	


private:/*Functions*/

	UFUNCTION()
	void ClickOnCellEvent(const ACPP_Cell* ClickedCell);

	UFUNCTION()
	void CancelEvent();	
	
	UFUNCTION()
	void CellsShiftingEvent(const ACPP_Cell* FirstCellToShift);

	UFUNCTION()
	void FinishCellsShiftingEvent();

	UFUNCTION()
	void FinishCellDivisionEvent(FVector2f SpawnAxialLocation);

	UFUNCTION()
	void BeginCellDivisionEvent();

	UFUNCTION()
	void Phase2StartedEvent(UCPP_SS_CellsManager* TheCellsManager, ACPP_Grid* TheGrid);


	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;


	void InitEventBuses();
	void RegisterEventFunctions() const;
	void UnRegisterEventFunctions() const;


	

};
