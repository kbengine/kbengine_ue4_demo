#include "kbengine_ue4_demo.h"
#include "Entity.h"
#include "Motion.h"


Motion::Motion(Entity* entity) :
	self(entity)
{
}

Motion::~Motion()
{
}

void Motion::set_moveSpeed(uint8 old)
{
	//UKBEventData_set_moveSpeed* pEventData = NewObject<UKBEventData_set_moveSpeed>();
	//pEventData->moveSpeed = moveSpeed;
	//pEventData->entityID = id();
	//KBENGINE_EVENT_FIRE("set_moveSpeed", pEventData);
}
