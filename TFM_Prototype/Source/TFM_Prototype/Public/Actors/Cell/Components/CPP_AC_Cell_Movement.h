#pragma once

#include "CoreMinimal.h"
#include "Actors/Cell/Components/CPP_AC_Cell_Base.h"
#include "CPP_AC_Cell_Movement.generated.h"





UCLASS()
class TFM_PROTOTYPE_API UCPP_AC_Cell_Movement : public UCPP_AC_Cell_Base
{
	GENERATED_BODY()


public:
	//UCPP_AC_Cell_Movement();


public:/*Properties*/



public:/*Functions*/




protected:/*Properties*/




protected:/*Functions*/

	UFUNCTION()
	void MoveCellEvent();


	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void RegisterEventFunctions() const;
	void UnRegisterEventFunctions() const;

	virtual void InitComponent() override;

	

};
