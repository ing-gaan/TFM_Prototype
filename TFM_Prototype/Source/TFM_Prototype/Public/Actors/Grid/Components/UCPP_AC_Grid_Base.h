#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"


#include "UCPP_AC_Grid_Base.generated.h"


class ACPP_Grid;


UCLASS(Abstract, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TFM_PROTOTYPE_API UUCPP_AC_Grid_Base : public UActorComponent
{
	GENERATED_BODY()

public:	

	UUCPP_AC_Grid_Base();



protected:/*Properties*/
	UPROPERTY()
	ACPP_Grid* OwnerGrid{ nullptr };




protected:/*Functions*/

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void InitComponent();

		
};
