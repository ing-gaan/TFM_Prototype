#include "Actors/Molecules/CPP_Molecule.h"
#include "Core/GameSettings/CPP_DA_GameSettings.h"
#include "Core/GameInstance/CPP_GameInstance.h"
#include "Utils/Macros/Macros.h"




ACPP_Molecule::ACPP_Molecule()
{
	PrimaryActorTick.bCanEverTick = true;
}



void ACPP_Molecule::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	checkf(World, TEXT("***> No World (nullptr) <***"));

	UCPP_GameInstance* GameInstance = Cast<UCPP_GameInstance>(World->GetGameInstance());
	checkf(GameInstance, TEXT("***> No GameInstance (nullptr) <***"));

	GameSettings = GameInstance->GameSettings;

	float ZLocation = GameSettings->CellsDefaultHeightFromGround;
	FVector MoleculeLocation = GetActorLocation();
	MoleculeLocation.Z = ZLocation;
	SetActorLocation(MoleculeLocation);
}



void ACPP_Molecule::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



