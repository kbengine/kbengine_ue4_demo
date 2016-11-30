// Fill out your copyright notice in the Description page of Project Settings.

#include "kbengine_ue4_demo.h"
#include "GameModeWorld.h"



AGameModeWorld::AGameModeWorld(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


void AGameModeWorld::installEvents()
{
	Super::installEvents();

	// in world
	// 这个事件触发时我们需要切换地图到游戏世界地图
	KBENGINE_REGISTER_EVENT("addSpaceGeometryMapping", addSpaceGeometryMapping);
	KBENGINE_REGISTER_EVENT("onEnterWorld", onEnterWorld);
	KBENGINE_REGISTER_EVENT("onLeaveWorld", onLeaveWorld);
	KBENGINE_REGISTER_EVENT("set_position", set_position);
	KBENGINE_REGISTER_EVENT("set_direction", set_direction);
	KBENGINE_REGISTER_EVENT("updatePosition", updatePosition);
	KBENGINE_REGISTER_EVENT("onControlled", onControlled);

	// in world(register by scripts)
	KBENGINE_REGISTER_EVENT("onAvatarEnterWorld", onAvatarEnterWorld);
	KBENGINE_REGISTER_EVENT("set_HP", set_HP);
	KBENGINE_REGISTER_EVENT("set_MP", set_MP);
	KBENGINE_REGISTER_EVENT("set_HP_Max", set_HP_Max);
	KBENGINE_REGISTER_EVENT("set_MP_Max", set_MP_Max);
	KBENGINE_REGISTER_EVENT("set_level", set_level);
	KBENGINE_REGISTER_EVENT("set_name", set_name);
	KBENGINE_REGISTER_EVENT("set_state", set_state);
	KBENGINE_REGISTER_EVENT("set_moveSpeed", set_moveSpeed);
	KBENGINE_REGISTER_EVENT("set_modelScale", set_modelScale);
	KBENGINE_REGISTER_EVENT("set_modelID", set_modelID);
	KBENGINE_REGISTER_EVENT("recvDamage", recvDamage);
	KBENGINE_REGISTER_EVENT("otherAvatarOnJump", otherAvatarOnJump);
	KBENGINE_REGISTER_EVENT("onAddSkill", onAddSkill);
}

void AGameModeWorld::addSpaceGeometryMapping_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeWorld::onEnterWorld_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeWorld::onLeaveWorld_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeWorld::set_position_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeWorld::set_direction_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeWorld::updatePosition_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeWorld::onControlled_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeWorld::onAvatarEnterWorld_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeWorld::set_HP_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeWorld::set_MP_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeWorld::set_HP_Max_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeWorld::set_MP_Max_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeWorld::set_level_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeWorld::set_name_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeWorld::set_state_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeWorld::set_moveSpeed_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeWorld::set_modelScale_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeWorld::set_modelID_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeWorld::recvDamage_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeWorld::otherAvatarOnJump_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeWorld::onAddSkill_Implementation(const UKBEventData* pEventData)
{

}
