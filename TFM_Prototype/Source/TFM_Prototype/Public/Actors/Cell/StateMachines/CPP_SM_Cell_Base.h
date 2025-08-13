#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"


#include "CPP_SM_Cell_Base.generated.h"



class UCPP_DA_GameSettings;
class UCPP_SM_Cell_Context;



UCLASS()
class TFM_PROTOTYPE_API UCPP_SM_Cell_Base : public UObject
{
	GENERATED_BODY()

public:/*Properties*/

	


public:/*Functions*/

	virtual void InitializeState(UCPP_SM_Cell_Context* Context);
	virtual void SetState();
	virtual void ImplementState();

protected:/*Properties*/

	UPROPERTY()
	const UCPP_DA_GameSettings* GameSettings{ nullptr };

	UPROPERTY()
	UCPP_SM_Cell_Context* BaseSMContext{ nullptr };





protected:/*Functions*/

	virtual const FLinearColor& GetMaterialColor();
	void SetMaterialColorParameter(const FLinearColor& MaterialColor);

	
};
