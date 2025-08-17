#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"


#include "CPP_Molecule.generated.h"



class UCPP_DA_GameSettings;



UCLASS()
class TFM_PROTOTYPE_API ACPP_Molecule : public AActor
{
	GENERATED_BODY()
	
public:	
	ACPP_Molecule();



public: /*Properties*/

	UPROPERTY()
	const UCPP_DA_GameSettings* GameSettings{ nullptr };


public: /*Functions*/





protected: /*Properties*/





protected: /*Functions*/

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


	


};
