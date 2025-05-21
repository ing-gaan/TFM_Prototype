#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"


#include "CPP_Grid.generated.h"



class ACPP_Player;
class UCPP_DA_GridSettings;
class UCPP_DA_GameSettings;
class UCPP_AC_Grid_StaticMeshInstances;
class UCPP_SS_UIEventBus;
class UCPP_SS_InputEventBus;
class UCPP_SS_CellsManagerEventBus;
class ACPP_Cell;




UCLASS()
class TFM_PROTOTYPE_API ACPP_Grid : public AActor
{
	GENERATED_BODY()
	
public:	
	ACPP_Grid();



public:/*Properties*/




public:/*Fucntions*/

	UFUNCTION()
	void ClickOnStaticMeshInstance(FVector2f AxialLocation) const;




protected:/*Properties*/

	UPROPERTY()
	const ACPP_Player* Player;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	const UCPP_DA_GridSettings* GridSettings { nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	const UCPP_DA_GameSettings* GameSettings { nullptr };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCPP_AC_Grid_StaticMeshInstances* StaticMeshInstancesComponent;

	UPROPERTY()
	UCPP_SS_UIEventBus* UIEventBus{ nullptr };

	UPROPERTY()
	UCPP_SS_InputEventBus* InputEventBus{ nullptr };

	UPROPERTY()
	UCPP_SS_CellsManagerEventBus* CellsManagerEventBus;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSet<FVector2f> UsedAxialLocations;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSet<FVector2f> FreeNeighbours;


protected:/*Fucntions*/

	UFUNCTION()
	void ClickOnCellEvent(const ACPP_Cell* NewClickedCell);

	UFUNCTION()
	void BeginDuplicateCellEvent();

	UFUNCTION()
	void FinishDuplicateCellEvent(FVector2f SpawnAxialLocation);

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void InitEventBuses();
	void RegisterEventFunctions();
	void UnRegisterEventFunctions();

	void SetGridLocation();

	void GetStaticMeshInstancesComponent();
	void AddNewFreeNeighbours(FVector2f SpawnAxialLocation);

	void SetGridVisibility(bool bIsVisible);
	

};
