#pragma once

#include "CoreMinimal.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"


#include "CPP_AC_Grid_StaticMeshInstances.generated.h"



class UCPP_DA_GridSettings;
class UCPP_DA_GameSettings;
class ACPP_PlayerController;
class ACPP_Grid;




UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TFM_PROTOTYPE_API UCPP_AC_Grid_StaticMeshInstances : public UHierarchicalInstancedStaticMeshComponent
{
	GENERATED_BODY()


public:/*Properties*/




public:/*Fucntions*/

	UFUNCTION()
	void InitComponent();

	UFUNCTION()
	void AddExtraInstances();

	UFUNCTION()
	void SetInstancesTransforms(const TSet<FVector2f> AxialLocations);




protected:/*Properties*/

	UPROPERTY()
	const ACPP_Grid* GridOwner;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	const UCPP_DA_GridSettings* GridSettings;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	const UCPP_DA_GameSettings* GameSettings { nullptr };

	UPROPERTY()
	TArray<int32> InstacesIndexes;

	UPROPERTY()
	const ACPP_PlayerController* PlayerController { nullptr };

	UPROPERTY()
	TArray<FVector2f> AxialLocationsOfVisibleInstances;


	int32 IndexHitByCursor { 0 };


	


protected:/*Fucntions*/

	UFUNCTION()
	void BeginCursorOver(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void EndCursorOver(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void Clicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);
		

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	
	void RegisterEventFunctions();
	void UnRegisterEventFunctions();

	void SetValuesToOneInstance(int32 Index, TArray<double> Values);
	void SetValuesToAllInstances(TArray<double> Values);

	void AddNewInstances(int InstancesNum);


};
