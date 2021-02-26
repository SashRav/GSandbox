// Copyright Epic Games, Inc. All Rights Reserved.


#include "GSandboxGameModeBase.h"
#include "SandboxPawn.h"
#include "SandboxPlayerController.h"

AGSandboxGameModeBase::AGSandboxGameModeBase()
{
	DefaultPawnClass = ASandboxPawn::StaticClass();
	PlayerControllerClass = ASandboxPlayerController::StaticClass();

}
