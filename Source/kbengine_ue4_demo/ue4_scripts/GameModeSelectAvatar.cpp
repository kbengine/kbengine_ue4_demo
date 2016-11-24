// Fill out your copyright notice in the Description page of Project Settings.

#include "kbengine_ue4_demo.h"
#include "GameModeSelectAvatar.h"


AGameModeSelectAvatar::AGameModeSelectAvatar(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AGameModeSelectAvatar::installEvents()
{
	Super::installEvents();

	// select-avatars
	KBENGINE_REGISTER_EVENT("onReqAvatarList", onReqAvatarList);
	KBENGINE_REGISTER_EVENT("onCreateAvatarResult", onCreateAvatarResult);
	KBENGINE_REGISTER_EVENT("onRemoveAvatar", onRemoveAvatar);
}

void AGameModeSelectAvatar::onReqAvatarList_Implementation(const FKEventData& eventData)
{
}

void AGameModeSelectAvatar::onCreateAvatarResult_Implementation(const FKEventData& eventData)
{
}

void AGameModeSelectAvatar::onRemoveAvatar_Implementation(const FKEventData& eventData)
{
}
