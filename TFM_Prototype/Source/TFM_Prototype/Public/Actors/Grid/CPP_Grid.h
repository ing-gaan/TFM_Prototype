#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"



#include "CPP_Grid.generated.h"



class UCPP_AC_Grid_StaticMeshInstances;



UCLASS()
class TFM_PROTOTYPE_API ACPP_Grid : public AActor
{
	GENERATED_BODY()
	
public:	
	ACPP_Grid();



public:/*Properties*/




public:/*Fucntions*/




protected:/*Properties*/

	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default Static meshes") 
	TObjectPtr<UStaticMesh> DefaultGridStaticMesh{ nullptr };*/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCPP_AC_Grid_StaticMeshInstances* StaticMeshInstancesComponent;
	



protected:/*Fucntions*/

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void GetStaticMeshInstancesComponent();

};
