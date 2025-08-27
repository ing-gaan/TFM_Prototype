#pragma once


#include "CoreMinimal.h"
#include "Engine/DataAsset.h"


#include "CPP_DA_MoleculeType.generated.h"



enum class ECPPE_MoleculeType : uint8;



UCLASS()
class TFM_PROTOTYPE_API UCPP_DA_MoleculeType : public UPrimaryDataAsset
{
	GENERATED_BODY()


public:/*Properties*/


	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Data")
	ECPPE_MoleculeType MoleculeType;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Basics")
	UStaticMesh* MoleculeStaticMesh{ nullptr };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Basics")
	UMaterialInterface* MoleculeMaterial{ nullptr };



	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Properties|Basics")
	float EnergyItProvides{ 0 };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Properties|Basics",
		meta = (ToolTip = "", ClampMin = 0, Units = "Percent"))
	float ToxicityLevel{ 0 };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Properties|Basics",
		meta = (ToolTip = "", ClampMin = 0, Units = "Percent"))
	float Size{ 0 };


	
};
