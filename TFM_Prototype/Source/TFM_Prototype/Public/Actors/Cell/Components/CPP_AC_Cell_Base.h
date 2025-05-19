#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"



#include "CPP_AC_Cell_Base.generated.h"


class ACPP_Cell;



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TFM_PROTOTYPE_API UCPP_AC_Cell_Base : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCPP_AC_Cell_Base();




protected:/*Properties*/
	UPROPERTY()
	ACPP_Cell* OwnerCell{ nullptr };




protected:/*Functions*/
	
	virtual void InitComponent();
	
		
};
