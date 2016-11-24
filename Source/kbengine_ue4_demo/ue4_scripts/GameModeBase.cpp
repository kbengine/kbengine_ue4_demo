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

void AGameModeBase::installEvents()
{
	// common
	KBENGINE_REGISTER_EVENT("onKicked", onKicked);
	KBENGINE_REGISTER_EVENT("onDisableConnect", onDisableConnect);
	KBENGINE_REGISTER_EVENT("onConnectStatus", onConnectStatus);
}

void AGameModeBase::onKicked_Implementation(const FKEventData& eventData)
{
}

void AGameModeBase::onDisableConnect_Implementation(const FKEventData& eventData)
{
}

void AGameModeBase::onConnectStatus_Implementation(const FKEventData& eventData)
{
}