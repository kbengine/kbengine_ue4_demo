#include "Monster.h"
#include "Engine/Entity.h"
#include "LogicEvents.h"

namespace KBEngine
{

Monster::Monster():
	MonsterBase()
{
}

Monster::~Monster()
{
}

void Monster::recvDamage(int32 arg1, int32 arg2, int32 arg3, int32 arg4)
{
	UKBEventData_recvDamage* pEventData = NewObject<UKBEventData_recvDamage>();
	pEventData->attackerID = arg1;
	pEventData->skillID = arg2;
	pEventData->damageType = arg3;
	pEventData->damage = arg4;
	pEventData->entityID = id();
	KBENGINE_EVENT_FIRE("recvDamage", pEventData);
}

void Monster::onHPChanged(int32 oldValue)
{
	UKBEventData_set_HP* pEventData = NewObject<UKBEventData_set_HP>();
	pEventData->HP = HP;
	pEventData->entityID = id();
	KBENGINE_EVENT_FIRE("set_HP", pEventData);
}

void Monster::onHP_MaxChanged(int32 oldValue)
{
	UKBEventData_set_HP_Max* pEventData = NewObject<UKBEventData_set_HP_Max>();
	pEventData->HP_Max = HP_Max;
	pEventData->entityID = id();
	KBENGINE_EVENT_FIRE("set_HP_Max", pEventData);
}

void Monster::onMPChanged(int32 oldValue)
{
	UKBEventData_set_MP* pEventData = NewObject<UKBEventData_set_MP>();
	pEventData->MP = MP;
	pEventData->entityID = id();
	KBENGINE_EVENT_FIRE("set_MP", pEventData);
}

void Monster::onMP_MaxChanged(int32 oldValue)
{
	UKBEventData_MP_Max* pEventData = NewObject<UKBEventData_MP_Max>();
	pEventData->MP_Max = MP_Max;
	pEventData->entityID = id();
	KBENGINE_EVENT_FIRE("set_MP_Max", pEventData);
}

void Monster::onEntityNOChanged(uint32 oldValue)
{
	UKBEventData_set_entityNO* pEventData = NewObject<UKBEventData_set_entityNO>();
	pEventData->entityNO = entityNO;
	pEventData->entityID = id();
	KBENGINE_EVENT_FIRE("set_entityNO", pEventData);
}

void Monster::onForbidsChanged(int32 oldValue)
{
	UKBEventData_set_forbids* pEventData = NewObject<UKBEventData_set_forbids>();
	pEventData->forbids = forbids;
	pEventData->entityID = id();
	KBENGINE_EVENT_FIRE("set_forbids", pEventData);
}

void Monster::onModelIDChanged(uint32 oldValue)
{
	UKBEventData_set_modelID* pEventData = NewObject<UKBEventData_set_modelID>();
	pEventData->modelID = modelID;
	pEventData->entityID = id();
	KBENGINE_EVENT_FIRE("set_modelID", pEventData);
}

void Monster::onModelScaleChanged(uint8 oldValue)
{
	UKBEventData_set_modelScale* pEventData = NewObject<UKBEventData_set_modelScale>();
	pEventData->modelScale = modelScale;
	pEventData->entityID = id();
	KBENGINE_EVENT_FIRE("set_modelScale", pEventData);
}

void Monster::onMoveSpeedChanged(uint8 oldValue)
{
	velocity(moveSpeed);

	UKBEventData_set_moveSpeed* pEventData = NewObject<UKBEventData_set_moveSpeed>();
	pEventData->moveSpeed = moveSpeed;
	pEventData->entityID = id();
	KBENGINE_EVENT_FIRE("set_moveSpeed", pEventData);
}

void Monster::onNameChanged(const FString& oldValue)
{
	UKBEventData_set_name* pEventData = NewObject<UKBEventData_set_name>();
	pEventData->name = name;
	pEventData->entityID = id();
	KBENGINE_EVENT_FIRE("set_name", pEventData);
}

void Monster::onStateChanged(int8 oldValue)
{
	UKBEventData_set_state* pEventData = NewObject<UKBEventData_set_state>();
	pEventData->state = state;
	pEventData->entityID = id();
	KBENGINE_EVENT_FIRE("set_state", pEventData);
}

void Monster::onSubStateChanged(uint8 oldValue)
{
	UKBEventData_set_subState* pEventData = NewObject<UKBEventData_set_subState>();
	pEventData->subState = subState;
	pEventData->entityID = id();
	KBENGINE_EVENT_FIRE("set_subState", pEventData);
}

void Monster::onUidChanged(uint32 oldValue)
{

}

void Monster::onUtypeChanged(uint32 oldValue)
{

}

}