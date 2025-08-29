#include "Characters/Player/CPP_Player.h"
#include "Core/GameInstance/CPP_GameInstance.h"
#include "Core/GameSettings/CPP_DA_GridSettings.h"
#include "Core/GameSettings/CPP_DA_GameSettings.h"
#include "Core/GameSettings/CPP_DA_CameraSettings.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Utils/Macros/Macros.h"




ACPP_Player::ACPP_Player()
{
	PrimaryActorTick.bCanEverTick = true;
}


void ACPP_Player::BeginPlay()
{
	Super::BeginPlay();

	InitPlayer();
	InitCamera();
	SetAxialLocation(GridSettings->FirstAxialLocation);
}


void ACPP_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateCamera(DeltaTime);
}


//void ACPP_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}

void ACPP_Player::InitPlayer()
{
	UWorld* World = GetWorld();
	checkf(World, TEXT("***> No World (nullptr) <***"));

	UCPP_GameInstance* GameInstance = Cast<UCPP_GameInstance>(World->GetGameInstance());
	checkf(GameInstance, TEXT("***> No GameInstance (nullptr) <***"));

	GameSettings = GameInstance->GameSettings;
	GridSettings = GameSettings->GridSettings;	
}


void ACPP_Player::InitCamera()
{
	CameraSettings = GameSettings->CameraSettings;
	CameraSpringArm = FindComponentByClass<USpringArmComponent>();
	PlayerCamera = FindComponentByClass<UCameraComponent>();

	Zoom = CameraSettings->DefaultZoom;
	PlayerCamera->FieldOfView = CameraSettings->FOV;
	PlayerCamera->AspectRatio = CameraSettings->AspectRatio;	
}



FVector2f ACPP_Player::GetAxialLocation() const
{
	return AxialLocation;
}



FVector2D ACPP_Player::GetRelativeLocation() const
{
	return RelativeLocation;
};



void ACPP_Player::SetAxialLocation(FVector2f NewAxialLocation)
{
	AxialLocation = NewAxialLocation;
	
	FVector PlayerLocation = GetActorLocation();
	PlayerLocation.Z = GameSettings->CellsDefaultHeightFromGround;
	SetActorLocation(PlayerLocation);
}



void ACPP_Player::UpdateCamera(float DeltaTime)
{
	FVector NewCameraLoc;
	FRotator NewCameraRot;

	if (IsPlayerMoving())
	{
		NewCameraLoc.X = PlayerCamera->GetRelativeLocation().X;
		NewCameraLoc.Y = PlayerCamera->GetRelativeLocation().Y + LocationChange.Y + CameraSettings->OffsetFromPlayer.Y;
		NewCameraLoc.Z = PlayerCamera->GetRelativeLocation().Z + LocationChange.X + CameraSettings->OffsetFromPlayer.X;

		//ewCameraLoc = PlayerCamera->GetRelativeLocation() + LocationChange;

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

	CameraSpringArm->TargetArmLength = Zoom;

	//OutVT.POV.FOV = Zoom;

	LerpAlpha += DeltaTime * CameraSettings->ZoomChangeStepSpeed;
	LerpAlpha = FMath::Clamp(LerpAlpha, 0.0, 1.0);


	CameraSpringArm->TargetArmLength = FMath::Lerp(CurrentZoom, Zoom, LerpAlpha);
	CurrentZoom2 = CameraSpringArm->TargetArmLength;

	
	//PlayerCamera->SetWorldLocation(FMath::VInterpTo(PlayerCamera->GetComponentLocation(), NewCameraLoc, DeltaTime, CameraSettings->MovementInterpSpeed));
	//PlayerCamera->SetWorldRotation(FMath::RInterpTo(PlayerCamera->GetComponentRotation(), NewCameraRot, DeltaTime, CameraSettings->RotationInterpSpeed));

	

	//PlayerCamera->SetRelativeLocation(FMath::VInterpTo(PlayerCamera->GetRelativeLocation(), NewCameraLoc, DeltaTime, CameraSettings->MovementInterpSpeed));
}


void ACPP_Player::SetZoomDirection(int ZoomDirection)
{	
	CurrentZoom = CurrentZoom2;
	Zoom += ZoomDirection * CameraSettings->ZoomChangeStep;
	Zoom = FMath::Clamp(Zoom, CameraSettings->MinZoom, CameraSettings->MaxZoom);
	LerpAlpha = 0.0;
}


void ACPP_Player::SetPANDirection(FVector2f PANDirection)
{
	PANMovement.X = PlayerCamera->GetRelativeLocation().X + PANDirection.X * CameraSettings->PANMovementMultiplier;
	PANMovement.Y = PlayerCamera->GetRelativeLocation().Y + PANDirection.Y * CameraSettings->PANMovementMultiplier;
}


bool ACPP_Player::IsPlayerMoving()
{
	if (LastPlayerLocation != GetActorLocation())
	{
		LocationChange = LastPlayerLocation - GetActorLocation();
		LastPlayerLocation = GetActorLocation();
		return true;
	}
	return false;
}