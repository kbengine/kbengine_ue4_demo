// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModeDemoBase.h"
#include "kbengine_ue4_demo.h"
#include "Engine/KBEngine.h"

AGameModeDemoBase::AGameModeDemoBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AGameModeDemoBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

// Called when the game starts or when spawned
void AGameModeDemoBase::BeginPlay()
{
	Super::BeginPlay();
	installEvents();
}

void AGameModeDemoBase::Destroyed()
{
	KBENGINE_DEREGISTER_ALL_EVENT();
	Super::Destroyed();
}

void AGameModeDemoBase::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	// 可以在这里理解为玩家编辑器Stop游戏或者离开了这个场景
	if (Exiting)
	{
		KBENGINE_DEREGISTER_ALL_EVENT();
	}
}

void AGameModeDemoBase::installEvents()
{
	// common
	KBENGINE_REGISTER_EVENT("onKicked", onKicked);
	KBENGINE_REGISTER_EVENT("onDisconnected", onDisconnected);
	KBENGINE_REGISTER_EVENT("onConnectionState", onConnectionState);
}

void AGameModeDemoBase::fire(const FString& eventName, UKBEventData* pEventData)
{
	KBENGINE_EVENT_FIRE(eventName, pEventData);
}

void AGameModeDemoBase::onKicked_Implementation(const UKBEventData* pEventData)
{
}

void AGameModeDemoBase::onDisconnected_Implementation(const UKBEventData* pEventData)
{
}

void AGameModeDemoBase::onConnectionState_Implementation(const UKBEventData* pEventData)
{
}