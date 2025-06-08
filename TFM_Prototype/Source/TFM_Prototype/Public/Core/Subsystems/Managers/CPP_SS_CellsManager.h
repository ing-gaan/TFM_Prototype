#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"


#include "CPP_SS_CellsManager.generated.h"



class ACPP_Cell;
class UCPP_DA_GameSettings;
class UCPP_DA_GridSettings;
class ACPP_PlayerController;
class UCPP_SS_InputEventBus;
class UCPP_SS_CellsManagerEventBus;
class UCPP_SS_UIEventBus;
class UCPP_DA_CellType;





UCLASS()
class TFM_PROTOTYPE_API UCPP_SS_CellsManager : public ULocalPlayerSubsystem
{
	GENERATED_BODY()


public:/*Properties*/




public:/*Functions*/

	void StartManager(const ACPP_PlayerController* PlayerController);

		





private:/*Properties*/

	UPROPERTY()
	const UCPP_DA_GameSettings* GameSettings { nullptr };

	UPROPERTY()
	const UCPP_DA_GridSettings* GridSettings { nullptr };

	UPROPERTY()
	TMap<FVector2f, const ACPP_Cell*> CellsMap;

	UPROPERTY()
	TArray<const ACPP_Cell*> CellsBirthOrder;

	UPROPERTY()
	UCPP_SS_InputEventBus* InputEventBus;

	UPROPERTY()
	UCPP_SS_CellsManagerEventBus* CellsManagerEventBus;

	UPROPERTY()
	UCPP_SS_UIEventBus* UIEventBus;

	UPROPERTY()
	const ACPP_PlayerController* PlayerContller { nullptr };

	UPROPERTY()
	const ACPP_Cell* ClickdCell { nullptr };


private:/*Functions*/

	UFUNCTION()
	void ClickOnCellEvent(const ACPP_Cell* ClickedCell);

	UFUNCTION()
	void ClickOnGridEvent(FVector2f AxialLocation);

	UFUNCTION()
	void FinishCellDifferentiationEvent(const UCPP_DA_CellType* NewCellType);

	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void InitEventBuses();
	void RegisterEventFunctions() const;
	void UnRegisterEventFunctions() const;
	
	void AddFirstCell();
	ACPP_Cell* SpawnFirstCell();
	ACPP_Cell* SpawnCell(FVector CellLocation, FRotator CellRotation, TSubclassOf<ACPP_Cell> CellClass);
	void ConfigureFirstCell(ACPP_Cell* NewCell, FVector2f AxialLocation);
	
	void DuplicateCell(FVector2f AxialLocation);		
	void AddCellSpawned(const ACPP_Cell* NewCell);

	

};
