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
	GENERATED_BODY()
	
public:	
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
