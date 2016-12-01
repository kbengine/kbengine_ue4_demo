#include "kbengine_ue4_demo.h"
#include "Entity.h"
#include "Combat.h"

ENTITYDEF_CLASS_REGISTER(Combat)
ENTITYDEF_PROPERTY_WITH_SETMETHOD_REGISTER(Combat, HP);
ENTITYDEF_PROPERTY_WITH_SETMETHOD_REGISTER(Combat, HP_Max);
ENTITYDEF_PROPERTY_WITH_SETMETHOD_REGISTER(Combat, MP);
ENTITYDEF_PROPERTY_WITH_SETMETHOD_REGISTER(Combat, MP_Max);

Combat::Combat(Entity* entity) :
	self(entity)
{
}

Combat::~Combat()
{
}

void Combat::set_HP(int32 old)
{
	//UKBEventData_set_HP* pEventData = NewObject<UKBEventData_set_HP>();
	//pEventData->HP = HP;
	//pEventData->entityID = id();
	//KBENGINE_EVENT_FIRE("set_HP", pEventData);
}

void Combat::set_HP_Max(int32 old)
{
	//UKBEventData_set_HP_Max* pEventData = NewObject<UKBEventData_set_HP_Max>();
	//pEventData->HP_Max = HP_Max;
	//pEventData->entityID = id();
	//KBENGINE_EVENT_FIRE("set_HP_Max", pEventData);
}

void Combat::set_MP(int32 old)
{
	//UKBEventData_set_MP* pEventData = NewObject<UKBEventData_set_MP>();
	//pEventData->MP = MP;
	//pEventData->entityID = id();
	//KBENGINE_EVENT_FIRE("set_MP", pEventData);
}

void Combat::set_MP_Max(int32 old)
{
	//UKBEventData_MP_Max* pEventData = NewObject<UKBEventData_MP_Max>();
	//pEventData->MP_Max = MP_Max;
	//pEventData->entityID = id();
	//KBENGINE_EVENT_FIRE("set_MP_Max", pEventData);
}