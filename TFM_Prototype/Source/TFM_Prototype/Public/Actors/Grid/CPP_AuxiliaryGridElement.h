#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"


#include "CPP_AuxiliaryGridElement.generated.h"




class UCPP_DA_GameSettings;
class UCPP_DA_GridSettings;
class ACPP_Player;
class ACPP_Grid;
class UCPP_SS_CellsManagerEventBus;
class UCPP_SS_GameEventBus;
enum class ECPP_CellShiftState : uint8;



DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAnimShiftEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAnimReturnEvent);



UCLASS()
class TFM_PROTOTYPE_API ACPP_AuxiliaryGridElement : public AActor
{
	GENERATED_BODY()
	
public:		
	ACPP_AuxiliaryGridElement();




public: /*Properties*/

	UPROPERTY(BlueprintAssignable)
	FAnimShiftEvent AnimShiftEventDelegate;

	UPROPERTY(BlueprintAssignable)
	FAnimReturnEvent AnimReturnEventDelegate;



	
public: /*Functions*/



	

protected: /*Properties*/
	
	UPROPERTY()
	UCPP_SS_CellsManagerEventBus* CellsManagerEventBus{ nullptr };

	UPROPERTY()
	UCPP_SS_GameEventBus* GameEventBus{ nullptr };

	UPROPERTY(BlueprintReadOnly)
	const UCPP_DA_GameSettings* GameSettings{ nullptr };

	UPROPERTY()
	const UCPP_DA_GridSettings* GridSettings{ nullptr };

	UPROPERTY()
	ACPP_Grid* Grid;

	UPROPERTY()
	UStaticMeshComponent* AuxElemStaticMesh{ nullptr };

	UPROPERTY()
	UMaterialInstanceDynamic* MaterialInstance{ nullptr };

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector2f AxialLocation{ FVector2f(0, 0) };

	/*UPROPERTY(BlueprintReadWrite)
	FVector2f TempAxialLocation{ FVector2f(0, 0) };*/

	UPROPERTY()
	FVector2D RelativeLocation{ FVector2D(0, 0) };

	UPROPERTY()
	const ACPP_Player* Player { nullptr };

	UPROPERTY(BlueprintReadWrite)
	float CurrentZLocation{ 0.0 };

	UPROPERTY(BlueprintReadOnly)
	ECPP_CellShiftState ShiftState;



protected: /*Functions*/

	UFUNCTION()
	void BeginCursorOver(AActor* TouchedActor);

	UFUNCTION()
	void EndCursorOver(AActor* TouchedActor);

	UFUNCTION()
	void Clicked(AActor* TouchedComponent, FKey ButtonPressed);

	UFUNCTION(BlueprintCallable)
	void SetRelativeLocation(FVector2f AxLocation);

	UFUNCTION()
	void CellsShiftingEvent(const ACPP_Cell* FirstCellToShift);

	UFUNCTION()
	void CellsShiftingReturnEvent();

	UFUNCTION()
	void Phase2StartedEvent(UCPP_SS_CellsManager* TheCellsManager, ACPP_Grid* TheGrid);

	UFUNCTION(BlueprintCallable)
	void SetShiftState(ECPP_CellShiftState CurrentShiftState);

	UFUNCTION(BlueprintCallable)
	void SetElementVisibility(bool bIsVisible);

	UFUNCTION(BlueprintCallable)
	void FinishCellsShifting();
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;

	void RegisterEventFunctions();
	void UnRegisterEventFunctions();

	void InitEventBuses();
	void InitElement();

	void SetMaterialColorParameter(const FLinearColor& MaterialColor);
	void SetMaterial();

	

};
