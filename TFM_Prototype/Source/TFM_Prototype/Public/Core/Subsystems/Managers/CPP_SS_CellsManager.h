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
class UCPP_SS_TimeEventBus;
class UCPP_DA_CellType;
class UCPP_SS_LocalGameManager;
class ACPP_Player;



class ACPP_Bacteria;





UCLASS()
class TFM_PROTOTYPE_API UCPP_SS_CellsManager : public ULocalPlayerSubsystem
{
	GENERATED_BODY()


public:/*Properties*/

	//******* TESTING BACTERIA *******//
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ACPP_Bacteria* CurrentAttachedBacteria{ nullptr };



public:/*Functions*/

	UFUNCTION(BlueprintCallable)
	float GetCurrentOrganismSpeed();

	UFUNCTION(BlueprintCallable)
	float GetCurrentOrganismRotationSpeed();

	
	void StartManager();
	const ACPP_Cell* GetCellInMap(FVector2f CellAxialLocation) const;
	const TMap<FVector2f, ACPP_Cell*>* GetCellsMap() const;
	void UpdateToTempLocations(TArray<FVector2f>& AxialLocations);
	int CellsInMapNumber() const;


	void GetNeighboursInRange(FVector2f AxialLocation, int RangeDistance, TArray<ACPP_Cell*>& OutNeighboursInRange) const;
	



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

	UPROPERTY()
	UCPP_SS_TimeEventBus* TimeEventBus{ nullptr };


	/*UPROPERTY()
	const ACPP_PlayerController* PlayerContller { nullptr };*/

	UPROPERTY()
	const ACPP_Cell* CurrentClickedCell{ nullptr };

	UPROPERTY()
	TSoftClassPtr<ACPP_Cell> FirstCellClass{ nullptr };

	UPROPERTY()
	TSoftClassPtr<ACPP_Cell> PhantomCellClass{ nullptr };

	UPROPERTY()
	ACPP_Cell* PhantomCell{ nullptr };

	UPROPERTY()
	TSoftObjectPtr<const UCPP_DA_CellType> FirstCellType{ nullptr };

	UPROPERTY()
	TSoftObjectPtr<const UCPP_DA_CellType> PhantomCellType{ nullptr };

	UPROPERTY()
	ACPP_Grid* Grid;

	UPROPERTY()
	ACPP_Player* Player { nullptr };


	float CurrentOrganismSpeed{ 0.f };


	//******* TESTING BACTERIA *******//
	TArray<ACPP_Cell*> NeighborsAffectedByBacteria;

	int DistanceToFarthestNeighbor{0};

	


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
	void Phase1StartedEvent(ACPP_Grid* TheGrid);

	UFUNCTION()
	void OneSecondEvent(int SecondsCount);


	//******* TESTING BACTERIA *******//
	UFUNCTION()
	void BacteriaAttachedEvent(ACPP_Bacteria* AttachedBacteria);



	
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
