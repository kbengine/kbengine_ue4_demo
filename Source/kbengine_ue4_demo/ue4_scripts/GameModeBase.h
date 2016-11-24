// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Event.h"
#include "GameFramework/GameMode.h"
#include "GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class KBENGINE_UE4_DEMO_API AGameModeBase : public AGameMode
{
	GENERATED_UCLASS_BODY()
	
public:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called once this actor has been deleted */
	virtual void Destroyed() override;

	/**
	* Initialize the game.
	* The GameMode's InitGame() event is called before any other functions (including PreInitializeComponents() )
	* and is used by the GameMode to initialize parameters and spawn its helper classes.
	* @warning: this is called before actors' PreInitializeComponents.
	*/
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	/*
	安装登陆时需要监听的KBE事件
	*/
	virtual void installEvents();

	/* KBE事件
		玩家被踢出服务器
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void onKicked(const FKEventData& eventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void onDisableConnect(const FKEventData& eventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void onConnectStatus(const FKEventData& eventData);
	
	
};
