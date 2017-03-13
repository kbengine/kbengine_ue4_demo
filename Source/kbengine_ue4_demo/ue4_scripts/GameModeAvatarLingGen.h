// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ue4_scripts/GameModeDemoBase.h"
#include "GameModeAvatarLingGen.generated.h"

/**
 * 
 */
UCLASS()
class KBENGINE_UE4_DEMO_API AGameModeAvatarLingGen : public AGameModeDemoBase
{
	GENERATED_BODY()
	
public:
	/*
	��װ��½ʱ��Ҫ������KBE�¼�
	*/
	virtual void installEvents() override;

	/* KBE�¼�
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void rsp_generate_linggen(const UKBEventData* pEventData);
	
	UFUNCTION(BlueprintCallable, Category = KBEngine)
	void req_generate_linggen();
};
