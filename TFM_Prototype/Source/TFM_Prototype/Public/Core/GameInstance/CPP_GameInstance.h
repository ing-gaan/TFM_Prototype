#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"


#include "CPP_GameInstance.generated.h"



class UCPP_DA_GameSettings;


UCLASS()
class TFM_PROTOTYPE_API UCPP_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	



public: /*Properties*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	const UCPP_DA_GameSettings* GameSettings{ nullptr };



public: /*Functions*/





protected: /*Properties*/

	
protected: /*Functions*/

};
