// Fill out your copyright notice in the Description page of Project Settings.

#include "kbengine_ue4_demo.h"
#include "GameModeLogin.h"
#include "Event.h"



void AGameModeLogin::installEvents()
{
	KBENGINE_REGISTER_EVENT("onKicked", onKicked);
	KBENGINE_REGISTER_EVENT("onDisableConnect", onDisableConnect);
	KBENGINE_REGISTER_EVENT("onConnectStatus", onConnectStatus);
	KBENGINE_REGISTER_EVENT("onCreateAccountResult", onCreateAccountResult);
	KBENGINE_REGISTER_EVENT("onLoginFailed", onLoginFailed);
	KBENGINE_REGISTER_EVENT("onVersionNotMatch", onVersionNotMatch);
	KBENGINE_REGISTER_EVENT("onScriptVersionNotMatch", onScriptVersionNotMatch);
	KBENGINE_REGISTER_EVENT("onLoginBaseappFailed", onLoginBaseappFailed);
	KBENGINE_REGISTER_EVENT("onLoginSuccessfully", onLoginSuccessfully);
	KBENGINE_REGISTER_EVENT("onLoginBaseapp", onLoginBaseapp);
	KBENGINE_REGISTER_EVENT("Loginapp_importClientMessages", Loginapp_importClientMessages);
	KBENGINE_REGISTER_EVENT("Baseapp_importClientMessages", Baseapp_importClientMessages);
	KBENGINE_REGISTER_EVENT("Baseapp_importClientEntityDef", Baseapp_importClientEntityDef);
	KBENGINE_REGISTER_EVENT("onReqAvatarList", onReqAvatarList);
	KBENGINE_REGISTER_EVENT("onCreateAvatarResult", onCreateAvatarResult);
	KBENGINE_REGISTER_EVENT("onRemoveAvatar", onRemoveAvatar);
}

void AGameModeLogin::onKicked_Implementation(const FKEventData& eventData)
{
}

void AGameModeLogin::onDisableConnect_Implementation(const FKEventData& eventData)
{
}

void AGameModeLogin::onConnectStatus_Implementation(const FKEventData& eventData)
{
}

void AGameModeLogin::onCreateAccountResult_Implementation(const FKEventData& eventData)
{
}

void AGameModeLogin::onLoginFailed_Implementation(const FKEventData& eventData)
{
}

void AGameModeLogin::onVersionNotMatch_Implementation(const FKEventData& eventData)
{
}

void AGameModeLogin::onScriptVersionNotMatch_Implementation(const FKEventData& eventData)
{
}

void AGameModeLogin::onLoginBaseappFailed_Implementation(const FKEventData& eventData)
{
}

void AGameModeLogin::onLoginSuccessfully_Implementation(const FKEventData& eventData)
{
}

void AGameModeLogin::onLoginBaseapp_Implementation(const FKEventData& eventData)
{
}

void AGameModeLogin::Loginapp_importClientMessages_Implementation(const FKEventData& eventData)
{
}

void AGameModeLogin::Baseapp_importClientMessages_Implementation(const FKEventData& eventData)
{
}

void AGameModeLogin::Baseapp_importClientEntityDef_Implementation(const FKEventData& eventData)
{
}

void AGameModeLogin::onReqAvatarList_Implementation(const FKEventData& eventData)
{
}

void AGameModeLogin::onCreateAvatarResult_Implementation(const FKEventData& eventData)
{
}

void AGameModeLogin::onRemoveAvatar_Implementation(const FKEventData& eventData)
{
}

