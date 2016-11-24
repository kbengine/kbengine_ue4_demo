// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ue4_scripts/GameModeBase.h"
#include "GameModeWorld.generated.h"

/**
 * 
 */
UCLASS()
class KBENGINE_UE4_DEMO_API AGameModeWorld : public AGameModeBase
{
	GENERATED_UCLASS_BODY()

public:
		/*
		安装登陆时需要监听的KBE事件
		*/
		virtual void installEvents() override;
};
