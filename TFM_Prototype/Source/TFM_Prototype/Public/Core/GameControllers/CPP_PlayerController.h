#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"


#include "CPP_PlayerController.generated.h"



class UCPP_DA_GameSettings;
class UCPP_DA_GridSettings;
//class UCPP_SS_InputEventBus;
//class UCPP_SS_TimersEventBus;
//class UCPP_SS_GameEventBus;
class ACPP_Cell;
//class ACPP_Grid;
class UCPP_SS_CellsManager;
class ACPP_Player;





UCLASS()
class TFM_PROTOTYPE_API ACPP_PlayerController : public APlayerController
{
	GENERATED_BODY()


public: /*Propereties*/

	
	


public: /*Functions*/

	/*UFUNCTION(BlueprintCallable)
	bool IsAxialLocationFree(FVector2f AxialLocation) const;

	UFUNCTION(BlueprintCallable)
	const ACPP_Cell* GetFirstCell() const;*/

	

protected:/*Properties*/

	/*UPROPERTY()
	UCPP_SS_InputEventBus* InputEventBus{ nullptr };

	UPROPERTY()
	UCPP_SS_TimersEventBus* TimersEventBus{ nullptr };*/

	/*UPROPERTY()
	UCPP_SS_GameEventBus* GameEventBus{ nullptr };*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	const UCPP_DA_GameSettings* GameSettings { nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	const UCPP_DA_GridSettings* GridSettings { nullptr };

	/*UPROPERTY(EditAnywhere, BlueprintReadOnly)
	const ACPP_Player* Player { nullptr };*/

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FVector2f, const ACPP_Cell*> CellsMap;*/

	UPROPERTY()
	TArray<const ACPP_Cell*> CellsBirthOrder;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSet<FVector2f> FreeNeighbours;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ACPP_Cell* FirstCell{ nullptr };*/

	UPROPERTY()
	UCPP_SS_CellsManager* CellsManager { nullptr };

	

protected:/*Functions*/

	/*UFUNCTION(BlueprintCallable)
	void AddFirstCell();*/

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;

	void InitEventBuses();

	void RegisterEventFunctions() const;
	void UnRegisterEventFunctions() const;

	/*void SpawnFirstCell();
	void AddCellSpawned(const ACPP_Cell* NewCell);*/

	//void AddNewFreeNeighbours(const ACPP_Cell* NewCell);

};
