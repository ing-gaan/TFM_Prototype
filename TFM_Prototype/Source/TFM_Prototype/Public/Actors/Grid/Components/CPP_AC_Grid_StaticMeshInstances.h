#pragma once

#include "CoreMinimal.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"


#include "CPP_AC_Grid_StaticMeshInstances.generated.h"



class UCPP_DA_GridSettings;
class ACPP_PlayerController;


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TFM_PROTOTYPE_API UCPP_AC_Grid_StaticMeshInstances : public UHierarchicalInstancedStaticMeshComponent
{
	GENERATED_BODY()


public:/*Properties*/




public:/*Fucntions*/




protected:/*Properties*/

	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default Static meshes")
	TObjectPtr<UStaticMesh> DefaultGridStaticMesh{ nullptr };*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	const UCPP_DA_GridSettings* GridSettings;

	UPROPERTY()
	TArray<FTransform> InstancesTransforms;

	UPROPERTY()
	TArray<int32> InstacesIndexes;

	UPROPERTY()
	const ACPP_PlayerController* PlayerController { nullptr };

	int32 IndexHitByCursor { 0 };

	


protected:/*Fucntions*/

	UFUNCTION()
	void BeginCursorOver(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void EndCursorOver(UPrimitiveComponent* TouchedComponent);
		

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void InitComponent();
	void RegisterEventFunctions();
	void UnRegisterEventFunctions();

	void SetValuesToOneInstance(int32 Index, TArray<double> Values);
	void SetValuesToAllInstances(TArray<double> Values);


};
