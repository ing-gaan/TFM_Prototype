#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"


#include "CPP_SM_Cell_Life_Base.generated.h"



class UCPP_SM_Cell_Life_Context;



UCLASS()
class TFM_PROTOTYPE_API UCPP_SM_Cell_Life_Base : public UObject
{
	GENERATED_BODY()



public:/*Properties*/




public:/*Functions*/

	virtual void InitState(UCPP_SM_Cell_Life_Context* Context, int StateSortPosition);

	virtual void ImplementState();
	virtual void SetStateMaterial();
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
	UMaterialInterface* StateMaterial{ nullptr };
	UPROPERTY()
	UCPP_SM_Cell_Life_Context* SMContext{ nullptr };

	float MaxStateTime{ 0 };
	float RemainingStateTime{ 0 };
	int SortPosition{ 0 };
	int LifeStateTimeDecreaseRate{ 0 };




protected:/*Functions*/

	





private:/*Properties*/

	bool bStateInitiated{ false };




	
};
