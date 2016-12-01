#include "kbengine_ue4_demo.h"
#include "Entity.h"
#include "NPCObject.h"

ENTITYDEF_CLASS_REGISTER(NPCObject)
ENTITYDEF_PROPERTY_REGISTER(NPCObject, entityNO);

NPCObject::NPCObject(Entity* entity) :
	self(entity)
{
}

NPCObject::~NPCObject()
{
}

void NPCObject::set_entityNO(int32 old)
{
	//UKBEventData_set_entityNO* pEventData = NewObject<UKBEventData_set_entityNO>();
	//pEventData->entityNO = entityNO;
	//pEventData->entityID = id();
	//KBENGINE_EVENT_FIRE("set_entityNO", pEventData);
}

