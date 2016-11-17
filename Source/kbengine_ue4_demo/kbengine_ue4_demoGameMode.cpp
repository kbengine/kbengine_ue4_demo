// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "kbengine_ue4_demo.h"
#include "kbengine_ue4_demoGameMode.h"
#include "kbengine_ue4_demoCharacter.h"

Akbengine_ue4_demoGameMode::Akbengine_ue4_demoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
