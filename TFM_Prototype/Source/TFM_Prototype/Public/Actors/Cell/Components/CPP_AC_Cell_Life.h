#pragma once

#include "CoreMinimal.h"
#include "Actors/Cell/Components/CPP_AC_Cell_Base.h"
#include <optional>


#include "CPP_AC_Cell_Life.generated.h"



class ACPP_Cell;
class UCPP_DA_CellType;
class UCPP_SS_TimeEventBus;
class UCPP_SS_GameEventBus;
class UCPP_SS_UIEventBus;
class UCPP_SS_InputEventBus;
class UCPP_SM_Cell_Life_Context;
class UCPP_SM_Cell_Energy_Context;
class UCPP_SM_Cell_Life_Base;





UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TFM_PROTOTYPE_API UCPP_AC_Cell_Life : public UCPP_AC_Cell_Base
{
	GENERATED_BODY()


public:
	UCPP_AC_Cell_Life();




public:/*Properties*/



public:/*Functions*/

	



protected:/*Properties*/

	UPROPERTY()
	UCPP_SS_GameEventBus* GameEventBus{ nullptr };
	
	UPROPERTY()
	UCPP_SM_Cell_Life_Context* LifeSMContext{ nullptr };

	UPROPERTY()
	UCPP_SM_Cell_Energy_Context* EnergySMContext;
	
	UPROPERTY()
	UMaterialInstanceDynamic* MaterialInstance{ nullptr };


	FTimerHandle LifeTimerHandle;
	FTimerDelegate LifeTimerDelegate;


	int LifeStateTimeStep{ 0 };
	int EnergyTimeStep{ 0 };
	float EnergyDecrease{ 0 };




protected:/*Functions*/

	UFUNCTION()
	void TenMilliSecondsEvent(int TensMilliSecondsCount);

	UFUNCTION()
	void FinishDifferentiateEvent();

	UFUNCTION()
	void BeginCellApoptosisEvent();

	UFUNCTION()
	void MoveCellEvent(bool bCellsMoving, bool bIsShifting);
	
	UFUNCTION()
	

	/*UFUNCTION()
	void FinishDestroyCellEvent();*/




	void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void RegisterEventFunctions();
	void UnRegisterEventFunctions();

	virtual void InitComponent() override;

	void InitCellStateMachines();
	void OneLifeStateTimeStep();
	void OneEnergyTimeStep();
	void DecreaseLifeStateTime();
	void DecreaseEnergy();
	
	void ChangeCellLifeState(std::optional<TSubclassOf<UCPP_SM_Cell_Life_Base>> StateType = std::nullopt);
	void DestroyCell();
	//void UpdateDeadCellNeighbours();
	//void SetDeadCellNeighbours();


	
};
