#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"


#include "CPP_SS_CellsManager.generated.h"



class ACPP_Cell;
class ACPP_Grid;
class UCPP_DA_GameSettings;
class UCPP_DA_GridSettings;
class ACPP_PlayerController;
class UCPP_SS_InputEventBus;
class UCPP_SS_CellsManagerEventBus;
class UCPP_SS_UIEventBus;
class UCPP_SS_GameEventBus;
class UCPP_DA_CellType;
class UCPP_SS_LocalGameManager;





UCLASS()
class TFM_PROTOTYPE_API UCPP_SS_CellsManager : public ULocalPlayerSubsystem
{
	GENERATED_BODY()


public:/*Properties*/




public:/*Functions*/
	
	void StartManager();
	const ACPP_Cell* GetCellInMap(FVector2f CellAxialLocation) const;
	const TMap<FVector2f, ACPP_Cell*>* GetCellsMap() const;
	void UpdateToTempLocations(TArray<FVector2f>& AxialLocations);
	int CellsInMapNumber() const;

	



protected:/*Properties*/
	
	UPROPERTY()
	const UCPP_DA_GameSettings* GameSettings { nullptr };

	UPROPERTY()
	const UCPP_DA_GridSettings* GridSettings { nullptr };

	UPROPERTY()
	TMap<FVector2f, ACPP_Cell*> CellsMap;

	UPROPERTY()
	TArray<const ACPP_Cell*> CellsBirthOrder;

	UPROPERTY()
	UCPP_SS_InputEventBus* InputEventBus{ nullptr };

	UPROPERTY()
	UCPP_SS_CellsManagerEventBus* CellsManagerEventBus{ nullptr };

	UPROPERTY()
	UCPP_SS_UIEventBus* UIEventBus{ nullptr };

	UPROPERTY()
	UCPP_SS_GameEventBus* GameEventBus{ nullptr };

	/*UPROPERTY()
	const ACPP_PlayerController* PlayerContller { nullptr };*/

	UPROPERTY()
	const ACPP_Cell* CurrentClickedCell{ nullptr };

	UPROPERTY()
	TSoftClassPtr<ACPP_Cell> FirstCellClass{ nullptr };

	UPROPERTY()
	TSoftObjectPtr<const UCPP_DA_CellType> FirstCellType{ nullptr };


protected:/*Functions*/

	UFUNCTION()
	void MoveCellsEvent(bool bCellsMoving);

	UFUNCTION()
	void ClickOnCellEvent(const ACPP_Cell* ClickedCell);

	UFUNCTION()
	void ClickOnGridEvent(FVector2f AxialLocation);

	UFUNCTION()
	void CancelEvent();

	UFUNCTION()
	void FinishCellDifferentiationEvent(const TSoftObjectPtr<UCPP_DA_CellType> NewCellType);

	UFUNCTION()
	void BeginEliminateCellEvent();

	UFUNCTION()
	void Phase1StartedEvent();



	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void InitEventBuses();
	void RegisterEventFunctions() const;
	void UnRegisterEventFunctions() const;
	
	void AddFirstCell();
	void SpawnFirstCell();

	void FirstCellClassSoftRefLoaded();

	ACPP_Cell* SpawnCell(FVector CellLocation, FRotator CellRotation, TSubclassOf<ACPP_Cell> CellClass);
	void ConfigureFirstCell(ACPP_Cell* NewCell, FVector2f AxialLocation);
	
	void DivideCellEvent(FVector2f AxialLocation);		
	void AddCellSpawned(ACPP_Cell* NewCell);
	void UnclickCurrentCell();
	
	void StartShiftingCellsLocations(const ACPP_Cell* FirstCellToShift) const;
	void ReturnCellsToOriginLocation() const;
	void UpdateCellToTempLocation(ACPP_Cell* Cellptr);

	void DestroyCell(ACPP_Cell* Cell);








	friend class ACPP_Cell;
};
