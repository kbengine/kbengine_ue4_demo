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
	UFUNCTION(BlueprintNativeEvent, Category = "KBEngine")
	void onKicked(const FKEventData& eventData);
	void onKicked_Implementation(const FKEventData& eventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "KBEngine")
	void onDisableConnect(const FKEventData& eventData);
	void onDisableConnect_Implementation(const FKEventData& eventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "KBEngine")
	void onConnectStatus(const FKEventData& eventData);
	void onConnectStatus_Implementation(const FKEventData& eventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "KBEngine")
	void onCreateAccountResult(const FKEventData& eventData);
	void onCreateAccountResult_Implementation(const FKEventData& eventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "KBEngine")
	void onLoginFailed(const FKEventData& eventData);
	void onLoginFailed_Implementation(const FKEventData& eventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "KBEngine")
	void onVersionNotMatch(const FKEventData& eventData);
	void onVersionNotMatch_Implementation(const FKEventData& eventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "KBEngine")
	void onScriptVersionNotMatch(const FKEventData& eventData);
	void onScriptVersionNotMatch_Implementation(const FKEventData& eventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "KBEngine")
	void onLoginBaseappFailed(const FKEventData& eventData);
	void onLoginBaseappFailed_Implementation(const FKEventData& eventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "KBEngine")
	void onLoginSuccessfully(const FKEventData& eventData);
	void onLoginSuccessfully_Implementation(const FKEventData& eventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "KBEngine")
	void onLoginBaseapp(const FKEventData& eventData);
	void onLoginBaseapp_Implementation(const FKEventData& eventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "KBEngine")
	void Loginapp_importClientMessages(const FKEventData& eventData);
	void Loginapp_importClientMessages_Implementation(const FKEventData& eventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "KBEngine")
	void Baseapp_importClientMessages(const FKEventData& eventData);
	void Baseapp_importClientMessages_Implementation(const FKEventData& eventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "KBEngine")
	void Baseapp_importClientEntityDef(const FKEventData& eventData);
	void Baseapp_importClientEntityDef_Implementation(const FKEventData& eventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "KBEngine")
	void onReqAvatarList(const FKEventData& eventData);
	void onReqAvatarList_Implementation(const FKEventData& eventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "KBEngine")
	void onCreateAvatarResult(const FKEventData& eventData);
	void onCreateAvatarResult_Implementation(const FKEventData& eventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "KBEngine")
	void onRemoveAvatar(const FKEventData& eventData);
	void onRemoveAvatar_Implementation(const FKEventData& eventData);
};
