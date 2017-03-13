// Fill out your copyright notice in the Description page of Project Settings.

#include "kbengine_ue4_demo.h"
#include "GameModeAvatarLingGen.h"
#include "KBEngine.h"

void AGameModeAvatarLingGen::installEvents()
{
	Super::installEvents();

	// select-avatars(register by scripts)
	KBENGINE_REGISTER_EVENT("rsp_generate_linggen", rsp_generate_linggen);
}

void AGameModeAvatarLingGen::rsp_generate_linggen_Implementation(const UKBEventData* pEventData)
{
}

void AGameModeAvatarLingGen::req_generate_linggen()
{
	// 由于Account实体注册了该事件， 如果此时Account实体存在那么必然会执行到该事件 
	UKBEventData_req_generate_linggen* pEventData = NewObject<UKBEventData_req_generate_linggen>();
	KBENGINE_EVENT_FIRE("req_generate_linggen", pEventData);
}

