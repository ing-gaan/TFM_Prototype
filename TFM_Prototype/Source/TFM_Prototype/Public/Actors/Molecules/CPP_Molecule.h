#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/Interfaces/CPPI_Tooltipable.h"


#include "CPP_Molecule.generated.h"



class UCPP_DA_GameSettings;
class UCPP_SS_InputEventBus;
class UCPP_DA_MoleculeType;



UCLASS()
class TFM_PROTOTYPE_API ACPP_Molecule : public AActor, public ICPPI_Tooltipable
{
	GENERATED_BODY()
	
public:	
	ACPP_Molecule();



public: /*Properties*/

	UPROPERTY()
	const UCPP_DA_GameSettings* GameSettings{ nullptr };

	UPROPERTY()
	UCPP_SS_InputEventBus* InputEventBus{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	const UCPP_DA_MoleculeType* MoleculeType{ nullptr };


public: /*Functions*/





protected: /*Properties*/

	

	UPROPERTY()
	UStaticMeshComponent* MoleculeStaticMeshComponent{ nullptr };




protected: /*Functions*/

	UFUNCTION()
	void BeginCursorOver(AActor* TouchedActor);

	UFUNCTION()
	void EndCursorOver(AActor* TouchedActor);


	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;

	void RegisterEventFunctions();
	void UnRegisterEventFunctions();
	
	void InitEventBuses();
	void InitMolecule();
	void SetStaticMesh();
	

	


};
