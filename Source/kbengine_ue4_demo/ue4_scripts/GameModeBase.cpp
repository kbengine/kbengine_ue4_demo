// Fill out your copyright notice in the Description page of Project Settings.

#include "kbengine_ue4_demo.h"
#include "GameModeBase.h"


AGameModeBase::AGameModeBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

// Called when the game starts or when spawned
void AGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	installEvents();
}

void AGameModeBase::Destroyed()
{
	KBENGINE_DEREGISTER_ALL_EVENT();
	Super::Destroyed();
}

void AGameModeBase::Logout(AController* Exiting)
{
	// 可以在这里理解为玩家编辑器Stop游戏或者离开了这个场景
	if (Exiting)
	{
		KBENGINE_DEREGISTER_ALL_EVENT();
	}

	Super::Logout(Exiting);
}

void AGameModeBase::installEvents()
{
	// common
	KBENGINE_REGISTER_EVENT("onKicked", onKicked);
	KBENGINE_REGISTER_EVENT("onDisableConnect", onDisableConnect);
	KBENGINE_REGISTER_EVENT("onConnectStatus", onConnectStatus);
}

void AGameModeBase::fire(const FString& eventName, UKBEventData* pEventData)
{
	KBENGINE_EVENT_FIRE(eventName, pEventData);
}

void AGameModeBase::onKicked_Implementation(const UKBEventData* pEventData)
{
}

void AGameModeBase::onDisableConnect_Implementation(const UKBEventData* pEventData)
{
}

void AGameModeBase::onConnectStatus_Implementation(const UKBEventData* pEventData)
{
}