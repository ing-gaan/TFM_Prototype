#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CPP_DA_CellType.generated.h"



class UCPP_AC_Cell_Base;



UCLASS()
class TFM_PROTOTYPE_API UCPP_DA_CellType : public UPrimaryDataAsset
{
	GENERATED_BODY()


public:/*Properties*/

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General|Basics")
	const UStaticMesh* CellStaticMesh{ nullptr };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Properties|Necessary actor components")
	TSet<TSubclassOf<UCPP_AC_Cell_Base>> NecessaryCellComponents;



public:/*Functions*/
	
};
