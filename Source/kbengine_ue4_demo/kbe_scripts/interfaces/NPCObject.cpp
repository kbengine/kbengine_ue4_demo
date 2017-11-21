#include "NPCObject.h"
#include "kbengine_ue4_demo.h"
#include "Entity.h"
#include "kbe_scripts/LogicEvents.h"

NPCObject::NPCObject(Entity* entity) :
	self(entity)
{
}

NPCObject::~NPCObject()
{
}

void NPCObject::set_entityNO(uint32 old)
{
	UKBEventData_set_entityNO* pEventData = NewObject<UKBEventData_set_entityNO>();
	pEventData->entityNO = entityNO;
	pEventData->entityID = self->id();
	KBENGINE_EVENT_FIRE("set_entityNO", pEventData);
}

