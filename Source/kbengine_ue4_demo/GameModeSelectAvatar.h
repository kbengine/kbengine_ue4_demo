// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameModeDemoBase.h"
#include "GameModeSelectAvatar.generated.h"

/**
 * 
 */
UCLASS()
class KBENGINE_UE4_DEMO_API AGameModeSelectAvatar : public AGameModeDemoBase
{
	GENERATED_UCLASS_BODY()

public:
	/*
		安装登陆时需要监听的KBE事件
	*/
	virtual void installEvents() override;

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void onReqAvatarList(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void onCreateAvatarResult(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void addSpaceGeometryMapping(const UKBEventData* pEventData);
	
	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void onRemoveAvatar(const UKBEventData* pEventData);

	UFUNCTION(BlueprintCallable, Category = KBEngine)
	void reqCreateAvatar(uint8 roleType, const FString& name);

	UFUNCTION(BlueprintCallable, Category = KBEngine)
	void reqRemoveAvatar(const FAVATAR_INFOS& avatarInfos);

	UFUNCTION(BlueprintCallable, Category = KBEngine)
	void selectAvatarGame(const FAVATAR_INFOS& avatarInfos);

};
