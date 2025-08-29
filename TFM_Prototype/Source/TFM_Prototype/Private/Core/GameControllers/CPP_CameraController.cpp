#include "Core/GameControllers/CPP_CameraController.h"
#include "Core/GameInstance/CPP_GameInstance.h"
#include "Core/GameSettings/CPP_DA_GameSettings.h"
#include "Core/GameSettings/CPP_DA_CameraSettings.h"
#include "Characters/Player/CPP_Player.h"
#include <Kismet/GameplayStatics.h>
#include "Utils/Macros/Macros.h"





void ACPP_CameraController::BeginPlay()
{
	Super::BeginPlay();

	InitCameraController();
	
}


void ACPP_CameraController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);	
}



void ACPP_CameraController::InitCameraController()
{
	UWorld* World = GetWorld();
	checkf(World, TEXT("***> No World (nullptr) <***"));

	UCPP_GameInstance* GameInstance = Cast<UCPP_GameInstance>(World->GetGameInstance());
	checkf(GameInstance, TEXT("***> No GameInstance (nullptr) <***"));

	GameSettings = GameInstance->GameSettings;
	CameraSettings = GameSettings->CameraSettings;

	Player = Cast<ACPP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	checkf(Player, TEXT("***> No PlayerPawn. Cast fail (nullptr) <***"));

	bIsOrthographic = CameraSettings->bIsOrthographic;
	DefaultAspectRatio = CameraSettings->AspectRatio;
	DefaultFOV = CameraSettings->FOV;

	Zoom = CameraSettings->DefaultZoom;
	SetOrthoWidth(Zoom);	

	//CameraStyle = FName(TEXT("FreeCam"));
}



void ACPP_CameraController::UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime)
{
	//Super::UpdateViewTarget(OutVT, DeltaTime);

	//FVector NewCameraLoc;
	//FRotator NewCameraRot;

	//if (IsPlayerMoving())
	//{
	//	NewCameraLoc.X = Player->GetActorLocation().X + CameraSettings->OffsetFromPlayer.X;
	//	NewCameraLoc.Y = Player->GetActorLocation().Y + CameraSettings->OffsetFromPlayer.Y;
	//	PANMovement.X = NewCameraLoc.X;
	//	PANMovement.Y = NewCameraLoc.Y;
	//}
	//else 
	//{
	//	NewCameraLoc.X = PANMovement.X;
	//	NewCameraLoc.Y = PANMovement.Y;
	//}
	//

	//NewCameraRot.Roll = CameraSettings->CameraRotation.Roll;
	//NewCameraRot.Pitch = CameraSettings->CameraRotation.Pitch;
	//NewCameraRot.Yaw = 0;// Player->GetActorRotation().Yaw;

	//
	//OutVT.POV.Zoom = Zoom;
	//
	//LerpAlpha += DeltaTime * CameraSettings->ZoomChangeStepSpeed;
	//LerpAlpha = FMath::Clamp(LerpAlpha, 0.0, 1.0);
	//

	//OutVT.POV.Zoom = FMath::Lerp(CurrentZoom, Zoom, LerpAlpha);
	//CurrentZoom2 = OutVT.POV.Zoom;
	//

	////PRINT("--------- POV= %.4f  Get= %.4f", ViewTarget.POV.Zoom, GetOrthoWidth());

	//if (!bIsInitialized)
	//{
	//	bIsInitialized = true;
	//	OutVT.POV.Location = NewCameraLoc;
	//	OutVT.POV.Rotation = NewCameraRot;
	//	CurrentZoom = Zoom;
	//	//PRINT("POV= %.4f  Get= %.4f", ViewTarget.POV.Zoom, GetOrthoWidth());
	//	return;
	//}

	//OutVT.POV.Location = FMath::VInterpTo(GetCameraLocation(), NewCameraLoc, DeltaTime, CameraSettings->MovementInterpSpeed);
	//OutVT.POV.Rotation = FMath::RInterpTo(GetCameraRotation(), NewCameraRot, DeltaTime, CameraSettings->RotationInterpSpeed);

	
	Super::UpdateViewTarget(OutVT, DeltaTime);

	FVector NewCameraLoc;
	FRotator NewCameraRot;

	if (IsPlayerMoving())
	{
		//NewCameraLoc.X = Player->GetActorLocation().X + CameraSettings->OffsetFromPlayer.X;
		//NewCameraLoc.Y = Player->GetActorLocation().Y + CameraSettings->OffsetFromPlayer.Y;
		//NewCameraLoc.Z = GetCameraLocation().Z;

		NewCameraLoc = GetCameraLocation();
		
		PANMovement.X = NewCameraLoc.X;
		PANMovement.Y = NewCameraLoc.Y;
	}
	else
	{
		NewCameraLoc.X = PANMovement.X;
		NewCameraLoc.Y = PANMovement.Y;
	}

	NewCameraRot.Roll = CameraSettings->CameraRotation.Roll;
	NewCameraRot.Pitch = CameraSettings->CameraRotation.Pitch;
	NewCameraRot.Yaw = 0;// Player->GetActorRotation().Yaw;

	
	OutVT.POV.FOV = Zoom;

	LerpAlpha += DeltaTime * CameraSettings->ZoomChangeStepSpeed;
	LerpAlpha = FMath::Clamp(LerpAlpha, 0.0, 1.0);


	OutVT.POV.FOV = FMath::Lerp(CurrentZoom, Zoom, LerpAlpha);
	CurrentZoom2 = OutVT.POV.FOV;


	//PRINT("--------- POV= %.4f  Get= %.4f", ViewTarget.POV.Zoom, GetOrthoWidth());

	if (!bIsInitialized)
	{
		bIsInitialized = true;
		OutVT.POV.Location = NewCameraLoc;
		OutVT.POV.Rotation = NewCameraRot;
		CurrentZoom = OutVT.POV.FOV;
		//PRINT("POV= %.4f  Get= %.4f", ViewTarget.POV.Zoom, GetOrthoWidth());
		return;
	}

	OutVT.POV.Location = FMath::VInterpTo(GetCameraLocation(), NewCameraLoc, DeltaTime, CameraSettings->MovementInterpSpeed);
	OutVT.POV.Rotation = FMath::RInterpTo(GetCameraRotation(), NewCameraRot, DeltaTime, CameraSettings->RotationInterpSpeed);

}


void ACPP_CameraController::SetZoomDirection(int ZoomDirection)
{	
	/*CurrentZoom = CurrentZoom2;
	Zoom += ZoomDirection * CameraSettings->ZoomChangeStep;
	Zoom = FMath::Clamp(Zoom, CameraSettings->MinZoom, CameraSettings->MaxZoom);
	LerpAlpha = 0.0;*/

	CurrentZoom = CurrentZoom2;
	Zoom += ZoomDirection * CameraSettings->ZoomChangeStep;
	Zoom = FMath::Clamp(Zoom, CameraSettings->MinZoom, CameraSettings->MaxZoom);
	LerpAlpha = 0.0;

	Player->SetZoomDirection(ZoomDirection);

}


void ACPP_CameraController::SetPANDirection(FVector2f PANDirection)
{
	PANMovement.X = GetCameraLocation().X + PANDirection.X * CameraSettings->PANMovementMultiplier;
	PANMovement.Y = GetCameraLocation().Y + PANDirection.Y * CameraSettings->PANMovementMultiplier;

	Player->SetPANDirection(PANDirection);
}


bool ACPP_CameraController::IsPlayerMoving()
{
	if(LastPlayerLocation != FVector2f(Player->GetActorLocation().X, Player->GetActorLocation().Y))
	{
		LastPlayerLocation = FVector2f(Player->GetActorLocation().X, Player->GetActorLocation().Y);
		return true;
	}
	return false;
}


