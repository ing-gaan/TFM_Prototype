#pragma once

#include "CoreMinimal.h"
#include "Actors/Cell/StateMachines/CPP_SM_Cell_Base.h"


#include "CPP_SM_Cell_Life_Base.generated.h"



class UCPP_SM_Cell_Life_Context;
class UCPP_DA_GameSettings;



UCLASS()
class TFM_PROTOTYPE_API UCPP_SM_Cell_Life_Base : public UCPP_SM_Cell_Base
{
	GENERATED_BODY()



public:/*Properties*/




public:/*Functions*/

	UFUNCTION()
	FText GetLifeStateName() const;


	virtual void InitializeState(UCPP_SM_Cell_Context* Context) override;
	virtual void InitState(UCPP_SM_Cell_Context* Context, int StateSortPosition);

	virtual void ImplementState() override;
	void DecreaseStateTime();
	float GetRemainingStateTime() const;
	float GetMaxStateTime() const;
	bool StateTimeFinished() const;
	int GetStateSortPosition() const;
	bool IsThisEqualOrOlderThan(TSubclassOf<UCPP_SM_Cell_Life_Base> LifeStage) const;
	void ChangeToNewCellTypeState();
	virtual void UpdateMaxStateTime();




protected:/*Properties*/

	UPROPERTY()
	UCPP_SM_Cell_Life_Context* SMContext{ nullptr };

	
	float MaxStateTime{ 0 };
	float RemainingStateTime{ 0 };
	int SortPosition{ 0 };
	int LifeStateTimeDecreaseRate{ 0 };

	FText LifeStateName;
	FName UserTextsStringTableId;


protected:/*Functions*/

	const FLinearColor& GetMaterialColor() override;





private:/*Properties*/

	bool bStateInitiated{ false };




	
};
