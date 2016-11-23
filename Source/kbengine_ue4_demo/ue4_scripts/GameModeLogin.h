// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Event.h"
#include "GameFramework/GameMode.h"
#include "GameModeLogin.generated.h"


/**
 * 
 */
UCLASS()
class KBENGINE_UE4_DEMO_API AGameModeLogin : public AGameMode
{
	GENERATED_UCLASS_BODY()
	
public:	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called once this actor has been deleted */
	virtual void Destroyed() override;

	/** Called when a Controller with a PlayerState leaves the match. */
	virtual void Logout(AController* Exiting) override;

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
	void installEvents();

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

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void onCreateAccountResult(const FKEventData& eventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void onLoginFailed(const FKEventData& eventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void onVersionNotMatch(const FKEventData& eventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void onScriptVersionNotMatch(const FKEventData& eventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void onLoginBaseappFailed(const FKEventData& eventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void onLoginSuccessfully(const FKEventData& eventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void onLoginBaseapp(const FKEventData& eventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void Loginapp_importClientMessages(const FKEventData& eventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void Baseapp_importClientMessages(const FKEventData& eventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void Baseapp_importClientEntityDef(const FKEventData& eventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void onReqAvatarList(const FKEventData& eventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void onCreateAvatarResult(const FKEventData& eventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void onRemoveAvatar(const FKEventData& eventData);
};
