// Fill out your copyright notice in the Description page of Project Settings.

#include "kbengine_ue4_demo.h"
#include "GameModeLogin.h"

AGameModeLogin::AGameModeLogin(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AGameModeLogin::Logout(AController* Exiting)
{
	// 由于该场景只有玩家自己， 因此可以在这里理解为玩家编辑器Stop游戏或者离开了这个场景
	KBENGINE_DEREGISTER_ALL_EVENT();
	Super::Logout(Exiting);
}

void AGameModeLogin::installEvents()
{
	Super::installEvents();

	// login
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

