#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <optional>


#include "CPP_Cell.generated.h"




class UCPP_DA_GridSettings;
class UCPP_DA_GameSettings;
class ACPP_PlayerController;
class UCPP_DA_CellType;
class ACPP_Player;
class UCPP_AC_Cell_Base;
class UCPP_SS_CellsManager;
enum class ECPP_CellShiftState : uint8;
class UCPP_SM_Cell_Life_Base;






//DECLARE_DYNAMIC_DELEGATE(FClickEvent);
DECLARE_DYNAMIC_DELEGATE(FUnclickEvent);
DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(ACPP_Cell*, FDivideEvent, FVector2f, NewAxialLocation);
DECLARE_DYNAMIC_DELEGATE_OneParam(FBeginDifferentiateEvent, TSoftObjectPtr<const UCPP_DA_CellType>, Newtype);
DECLARE_DYNAMIC_DELEGATE_OneParam(FShiftEvent, bool, ShouldShift);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMoveCellEvent, bool, bCellsMoving, bool, bIsShifting);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFinishDifferentiateEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAnimShiftLocationEvent, FVector2f, NewAxialLocation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAnimReturnToOriginEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBeginCellApoptosisEvent);



UCLASS()
class TFM_PROTOTYPE_API ACPP_Cell : public AActor
{
	GENERATED_BODY()
	
public:	
	ACPP_Cell();
	


public: /*Properties*/	

	/*UPROPERTY()
	FClickEvent ClickEventDelegate;*/
	UPROPERTY(BlueprintAssignable)
	FAnimShiftLocationEvent AnimShiftLocationEventDelegate;

	UPROPERTY(BlueprintAssignable)
	FAnimReturnToOriginEvent AnimReturnToOriginEventDelegate;

	UPROPERTY()
	FUnclickEvent UnclickEventDelegate;

	UPROPERTY()
	FMoveCellEvent MoveCellEventDelegate;

	UPROPERTY()
	FDivideEvent DivideEventDelegate;

	UPROPERTY()
	FBeginDifferentiateEvent BeginDifferentiateEventDelegate;

	UPROPERTY()
	FFinishDifferentiateEvent FinishDifferentiateEventDelegate;

	UPROPERTY()
	FShiftEvent ShiftEventDelegate;

	UPROPERTY()
	FBeginCellApoptosisEvent BeginCellApoptosisEventDelegate;



	UPROPERTY()
	const ACPP_PlayerController* PlayerController{ nullptr };

	UPROPERTY()
	const ACPP_Player* Player { nullptr };

	UPROPERTY()
	const UCPP_DA_GridSettings* GridSettings{ nullptr };

	UPROPERTY()
	const UCPP_DA_GameSettings* GameSettings{ nullptr };
	
	UPROPERTY()
	const UCPP_DA_CellType* CellType{ nullptr };
	
	UPROPERTY()
	UStaticMeshComponent* CellStaticMeshComponent{ nullptr };



public: /*Functions*/


	UFUNCTION(BlueprintCallable)
	FVector2f GetAxialLocation() const;

	UFUNCTION(BlueprintCallable)
	void SetAxialLocation(FVector2f NewAxialLocation);

	UFUNCTION(BlueprintCallable)
	FVector2D GetRelativeLocation() const;

	UFUNCTION()
	ACPP_Cell* Divide(FVector2f NewAxialLocation) const;

	UFUNCTION()
	void BeginDifferentiate(const TSoftObjectPtr<UCPP_DA_CellType> Newtype) const;

	UFUNCTION()
	void FinishDifferentiate() const;

	UFUNCTION()
	bool LoadCellTypeComponents(const UCPP_DA_CellType* NewCellType);

	UFUNCTION()
	void Clicked(bool Clicked);
	
	UFUNCTION()
	void Unclick() const;

	UFUNCTION(BlueprintCallable)
	void MoveCell(bool bCellsMoving, bool bIsShifting) const;

	UFUNCTION()
	bool HasThisAbility(TSubclassOf<UCPP_AC_Cell_Base> Ability) const;

	UFUNCTION(BlueprintCallable)
	float GetCellEnergy();

	
	void NotifyShiftingActivated() const;
	void NotifyShiftingCanceled() const;

	void ShiftAxialLocation(FVector2f NewTempAxialLocation) const;
	void ReturnToOriginAxialLocation() const;
	ECPP_CellShiftState GetCellShiftState() const;
	bool CellLifeStateIsEqualOrOlderThan(TSubclassOf<UCPP_SM_Cell_Life_Base> LifeStage) const;
	bool IsClicked() const;
	FVector2f GetTempAxialLocation() const;
	void UpdateToTemporalLocation();

	/**
	 * @brief Increases or decreases Energy.
	 * @param EnergyVariation: Amount of energy to increase (positive) or decrease (negative).
	*/
	void In_De_creaseCellEnergy(float EnergyVariation);


	void BeginCellApoptosis() const;
	const UCPP_SM_Cell_Life_Base* GetCellLifeState() const;
	void SetCellLifeState(const UCPP_SM_Cell_Life_Base* Newstate);
	void DestroyYourself();
	bool IsConnectedToOldestCell();


protected: /*Properties*/	

	static UCPP_SS_CellsManager* CellsManager;

		
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector2f AxialLocation{ FVector2f(0, 0) };

	UPROPERTY(BlueprintReadWrite)
	FVector2f TempAxialLocation{ FVector2f(0, 0) };

	UPROPERTY()
	FVector2D RelativeLocation{ FVector2D(0, 0) };

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsCellMoving{false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECPP_CellShiftState CellShiftState;

	UPROPERTY()
	const UCPP_SM_Cell_Life_Base* CellLifeState;


	bool bIsClicked{ false };
	float CellEnergy{ 0 };
	bool bIsConnectedToOldestCell{ true };

	


protected: /*Functions*/
	
	
	UFUNCTION(BlueprintCallable)
	void SetRelativeLocation(FVector2f AxLocation);

	UFUNCTION(BlueprintImplementableEvent)
	void BPIE_NotifyEnergy(float Energy);

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;

	void RegisterEventFunctions() const;
	void UnRegisterEventFunctions() const;

	void InitCell();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
	



	friend class UCPP_SS_CellsManager;
};
