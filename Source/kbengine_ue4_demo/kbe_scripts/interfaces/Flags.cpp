#include "kbengine_ue4_demo.h"
#include "Entity.h"
#include "Flags.h"


Flags::Flags(Entity* entity) :
	self(entity)
{
}

Flags::~Flags()
{
}

void Flags::set_flags(int32 old)
{
	//UKBEventData_set_flags* pEventData = NewObject<UKBEventData_set_flags>();
	//pEventData->flags = flags;
	//pEventData->entityID = id();
	//KBENGINE_EVENT_FIRE("set_flags", pEventData);
}
