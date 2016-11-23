// Fill out your copyright notice in the Description page of Project Settings.

#include "kbengine_ue4_demo.h"
#include "GameModeLogin.h"
#include "Event.h"

AGameModeLogin::AGameModeLogin(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AGameModeLogin::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

// Called when the game starts or when spawned
void AGameModeLogin::BeginPlay()
{
	Super::BeginPlay();
	installEvents();
}


void AGameModeLogin::Destroyed()
{
	KBENGINE_DEREGISTER_ALL_EVENT();
	Super::Destroyed();
}

void AGameModeLogin::Logout(AController* Exiting)
{
	// 由于该场景只有玩家自己， 因此可以在这里理解为玩家编辑器Stop游戏或者离开了这个场景
	KBENGINE_DEREGISTER_ALL_EVENT();
	Super::Logout(Exiting);
}

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

	KB_ARRAY a;
	KBVar a1 = 1;
	KBVar a2 = FString(TEXT("aaa"));
	a.Add(a1);
	a.Add(a2);
	KBVar xxx = a;
	KB_ARRAY s = xxx;
	int iii = s[0];
	FString xxxxx = s[1];


	KB_FIXED_DICT map;
	map.Add("111", a1);
	map.Add("222", a2);

	KBVar mmm = map;
	KB_FIXED_DICT map1 = mmm;
	int iii1 = map1["111"];
	FString xxxxx1 = map1["222"];
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

