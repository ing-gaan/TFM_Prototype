#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"


#include "CPP_PlayerController.generated.h"



class UCPP_SS_InputEventBus;
class UCPP_DA_GameSettings;
class UCPP_DA_GridSettings;
class ACPP_Cell;
class UCPP_SS_CellsManager;
class ACPP_Player;





UCLASS()
class TFM_PROTOTYPE_API ACPP_PlayerController : public APlayerController
{
	GENERATED_BODY()


public: /*Propereties*/

	
	


public: /*Functions*/



	

protected:/*Properties*/

	UPROPERTY()
	UCPP_SS_InputEventBus* InputEventBus;

	UPROPERTY()
	const UCPP_DA_GameSettings* GameSettings { nullptr };

	UPROPERTY()
	TArray<const ACPP_Cell*> CellsBirthOrder;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSet<FVector2f> FreeNeighbours;

	UPROPERTY()
	UCPP_SS_CellsManager* CellsManager { nullptr };

	FTimerDelegate TimerDelegate;
	FTimerHandle TimerHandle;


protected:/*Functions*/

	UFUNCTION(BlueprintCallable)
	void ClickOnActor();

	UFUNCTION()
	void StartCellsManager();



	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;

	void InitEventBuses();
	void RegisterEventFunctions() const;
	void UnRegisterEventFunctions() const;

	const AActor* CursorOverActor();

};
