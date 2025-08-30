#include "Actors/Camera/CPP_PlayerCamera.h"
#include "Core/GameInstance/CPP_GameInstance.h"
#include "Core/GameSettings/CPP_DA_GameSettings.h"
#include "Core/GameSettings/CPP_DA_CameraSettings.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/Player/CPP_Player.h"
#include "Utils/Macros/Macros.h"



ACPP_PlayerCamera::ACPP_PlayerCamera()
{
	PrimaryActorTick.bCanEverTick = true;
}


void ACPP_PlayerCamera::BeginPlay()
{
	Super::BeginPlay();

	InitActor();
	InitCamera();
}


void ACPP_PlayerCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateCamera(DeltaTime);
}


void ACPP_PlayerCamera::InitActor()
{
	UWorld* World = GetWorld();
	checkf(World, TEXT("***> No World (nullptr) <***"));

	UCPP_GameInstance* GameInstance = Cast<UCPP_GameInstance>(World->GetGameInstance());
	checkf(GameInstance, TEXT("***> No GameInstance (nullptr) <***"));

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	checkf(PlayerPawn, TEXT("***> No Player (nullptr) <***"));

	GameSettings = GameInstance->GameSettings;
}


void ACPP_PlayerCamera::InitCamera()
{
	CameraSettings = GameSettings->CameraSettings;

	PlayerCamera = GetCameraComponent();	
	PlayerCamera->FieldOfView = CameraSettings->FOV;
	PlayerCamera->AspectRatio = CameraSettings->AspectRatio;
	
	Zoom = GameSettings->CellsDefaultHeightFromGround + CameraSettings->DefaultZoom;

	FVector CamLocation;

	CamLocation.X = PlayerPawn->GetActorLocation().X;
	CamLocation.Y = PlayerPawn->GetActorLocation().Y;
	CamLocation.Z = Zoom;

	SetActorLocation(CamLocation);

	CurrentZoom = Zoom;

}



void ACPP_PlayerCamera::UpdateCamera(float DeltaTime)
{
	FVector NewCameraLoc;
	//FRotator NewCameraRot;

	if (IsPlayerMoving())
	{
		NewCameraLoc.X = PlayerPawn->GetActorLocation().X + CameraSettings->OffsetFromPlayer.X;
		NewCameraLoc.Y = PlayerPawn->GetActorLocation().Y + CameraSettings->OffsetFromPlayer.Y;
		PANMovement.X = NewCameraLoc.X;
		PANMovement.Y = NewCameraLoc.Y;
	}
	else
	{
		NewCameraLoc.X = PANMovement.X;
		NewCameraLoc.Y = PANMovement.Y;
	}
	
	LerpAlpha += DeltaTime * CameraSettings->ZoomChangeStepSpeed;
	LerpAlpha = FMath::Clamp(LerpAlpha, 0.0, 1.0);
	NewCameraLoc.Z = FMath::Lerp(CurrentZoom, Zoom, LerpAlpha);

	CurrentZoom2 = NewCameraLoc.Z;

	SetActorLocation(NewCameraLoc);


	//NewCameraRot.Roll = CameraSettings->CameraRotation.Roll;
	//NewCameraRot.Pitch = CameraSettings->CameraRotation.Pitch;
	//NewCameraRot.Yaw = 0;// Player->GetActorRotation().Yaw;

	//SetActorLocation(FMath::VInterpTo(GetActorLocation(), NewCameraLoc, DeltaTime, CameraSettings->MovementInterpSpeed));
	//SetActorRotation(FMath::RInterpTo(GetActorRotation(), NewCameraRot, DeltaTime, CameraSettings->RotationInterpSpeed));
	//PlayerCamera->SetRelativeLocation(FMath::VInterpTo(PlayerCamera->GetRelativeLocation(), NewCameraLoc, DeltaTime, CameraSettings->MovementInterpSpeed));
}


void ACPP_PlayerCamera::SetZoomDirection(int ZoomDirection)
{
	CurrentZoom = CurrentZoom2;
	Zoom += ZoomDirection * CameraSettings->ZoomChangeStep;
	int MinZoom = PlayerPawn->GetActorLocation().Z + CameraSettings->MinZoom;
	int MaxZoom = PlayerPawn->GetActorLocation().Z + CameraSettings->MaxZoom;
	Zoom = FMath::Clamp(Zoom, MinZoom, MaxZoom);
	LerpAlpha = 0.0;
}


void ACPP_PlayerCamera::SetPANDirection(FVector2f PANDirection)
{	
	PANMovement.X = GetActorLocation().X + PANDirection.X * CameraSettings->PANMovementMultiplier;
	PANMovement.Y = GetActorLocation().Y + PANDirection.Y * CameraSettings->PANMovementMultiplier;
}


bool ACPP_PlayerCamera::IsPlayerMoving()
{
	if (LastPlayerLocation != FVector2f(PlayerPawn->GetActorLocation().X, PlayerPawn->GetActorLocation().Y))
	{
		LastPlayerLocation = FVector2f(PlayerPawn->GetActorLocation().X, PlayerPawn->GetActorLocation().Y);		
		return true;
	}
	return false;
}