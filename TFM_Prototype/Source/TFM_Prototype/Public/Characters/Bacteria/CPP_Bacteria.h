#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Core/Interfaces/CPPI_Tooltipable.h"


#include "CPP_Bacteria.generated.h"



class UCPP_DA_GameSettings;
class UCPP_SS_InputEventBus;
class UCPP_SS_CellsManagerEventBus;
class UCPP_SS_TimeEventBus;
class ACPP_Player;
class UCPP_DA_BacteriaType;
class ACPP_Cell;




UCLASS()
class TFM_PROTOTYPE_API ACPP_Bacteria : public APawn, public ICPPI_Tooltipable
{
	GENERATED_BODY()

public:
	ACPP_Bacteria();



public:	/*Properties*/

	
	UPROPERTY()
	const UCPP_DA_GameSettings* GameSettings{ nullptr };

	UPROPERTY()
	UCPP_SS_InputEventBus* InputEventBus{ nullptr };

	UPROPERTY()
	UCPP_SS_CellsManagerEventBus* CellsManagerEventBus{ nullptr };

	UPROPERTY()
	UCPP_SS_TimeEventBus* TimeEventBus{ nullptr };


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	const UCPP_DA_BacteriaType* BacteriaType{ nullptr };


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	const ACPP_Cell* PhantomCell;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsAttachedToGrid{ false };






public:	/*Functions*/

	/// Return true if life points are complete
	UFUNCTION()
	bool AddStolenLifePoints(float StolenPoints);





protected:	/*Properties*/

	UPROPERTY()
	UStaticMeshComponent* MoleculeStaticMeshComponent{ nullptr };

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float LifePoints{ 0 };




protected: /*Functions*/

	UFUNCTION()
	void BeginCursorOver(AActor* TouchedActor);

	UFUNCTION()
	void EndCursorOver(AActor* TouchedActor);

	UFUNCTION(BlueprintCallable)
	void MoveCellsEvent(bool bCellsMoving);

	/// Only to be implemented in Blueprint. 
	UFUNCTION(BlueprintImplementableEvent)
	void BPIE_NotifyFullPoints();



	UFUNCTION()
	void OneSecondEvent(int SecondsCount);



	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	

	void RegisterEventFunctions();
	void UnRegisterEventFunctions();

	void InitEventBuses();
	void InitMolecule();
	void SetStaticMesh();




};
