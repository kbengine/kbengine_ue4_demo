// Fill out your copyright notice in the Description page of Project Settings.

#include "kbengine_ue4_demo.h"
#include "GameModeSelectAvatar.h"
#include "KBEngine.h"

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

void AGameModeSelectAvatar::onReqAvatarList_Implementation(const UKBEventData* pEventData)
{
}

void AGameModeSelectAvatar::onCreateAvatarResult_Implementation(const UKBEventData* pEventData)
{
}

void AGameModeSelectAvatar::onRemoveAvatar_Implementation(const UKBEventData* pEventData)
{
}

void AGameModeSelectAvatar::reqCreateAvatar(uint8 roleType, const FString& name)
{
	// 由于Account实体注册了该事件， 如果此时Account实体存在那么必然会执行到该事件 
	UKBEventData_reqCreateAvatar* pEventData = NewObject<UKBEventData_reqCreateAvatar>();
	pEventData->roleType = roleType;
	pEventData->name = name;
	KBENGINE_EVENT_FIRE("reqCreateAvatar", pEventData);
}

void AGameModeSelectAvatar::reqRemoveAvatar(const FAVATAR_INFOS& avatarInfos)
{
	// 由于Account实体注册了该事件， 如果此时Account实体存在那么必然会执行到该事件 
	UKBEventData_reqRemoveAvatar* pEventData = NewObject<UKBEventData_reqRemoveAvatar>();
	pEventData->avatarInfos = avatarInfos;
	KBENGINE_EVENT_FIRE("reqRemoveAvatar", pEventData);
}

void AGameModeSelectAvatar::selectAvatarGame(const FAVATAR_INFOS& avatarInfos)
{
	// 由于Account实体注册了该事件， 如果此时Account实体存在那么必然会执行到该事件 
	UKBEventData_selectAvatarGame* pEventData = NewObject<UKBEventData_selectAvatarGame>();
	pEventData->avatarInfos = avatarInfos;
	KBENGINE_EVENT_FIRE("selectAvatarGame", pEventData);
}