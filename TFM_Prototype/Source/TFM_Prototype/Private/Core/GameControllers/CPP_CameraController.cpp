#include "Core/GameControllers/CPP_CameraController.h"
#include "Core/GameSettings/CPP_DA_CameraSettings.h"
#include "Characters/Player/CPP_Player.h"
#include <Kismet/GameplayStatics.h>
#include "Utils/Macros/Macros.h"




void ACPP_CameraController::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<ACPP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	checkf(Player, TEXT("***> No PlayerPawn. Cast fail (nullptr) <***"));

	CameraZoom = CameraSettings->ZeroZoom;
}


void ACPP_CameraController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
}



void ACPP_CameraController::UpdateViewTargetInternal(FTViewTarget& OutVT, float DeltaTime)
{
	Super::UpdateViewTargetInternal(OutVT, DeltaTime);

	FVector NewCameraLoc;
	FRotator NewCameraRot;

	NewCameraLoc.X = Player->GetActorLocation().X + CameraSettings->OffsetFromPlayer.X;
	NewCameraLoc.Y = Player->GetActorLocation().Y + CameraSettings->OffsetFromPlayer.Y;
	NewCameraLoc.Z = CameraZoom;

	NewCameraRot.Roll = CameraSettings->CameraRotation.Roll;
	NewCameraRot.Pitch = CameraSettings->CameraRotation.Pitch;
	NewCameraRot.Yaw = Player->GetActorRotation().Yaw;

	//OutVT.POV.Location = NewCameraLoc;
	//OutVT.POV.Rotation = NewCameraRot;

	OutVT.POV.Location = FMath::VInterpTo(OutVT.POV.Location, NewCameraLoc, DeltaTime, CameraSettings->MovementInterpSpeed);
	OutVT.POV.Rotation = FMath::RInterpTo(OutVT.POV.Rotation, NewCameraRot, DeltaTime, CameraSettings->RotationInterpSpeed);
	//OutVT.POV.FOV = CameraSettings->FOV;
		
	
}



void ACPP_CameraController::SetZoomDirection(int ZoomDirection)
{
	CameraZoom += ZoomDirection * CameraSettings->ZoomStep;
	CameraZoom = FMath::Clamp(CameraZoom, CameraSettings->MinZoom, CameraSettings->MaxZoom);	
}



