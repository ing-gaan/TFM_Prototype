#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"



#include "CPP_Grid.generated.h"


UCLASS()
class TFM_PROTOTYPE_API ACPP_Grid : public AActor
{
	GENERATED_BODY()
	
public:	
	ACPP_Grid();

protected:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default Static meshes")
	TObjectPtr<UStaticMesh> DefaultGridStaticMesh{ nullptr };


	virtual void BeginPlay() override;





public:	
	virtual void Tick(float DeltaTime) override;

};
