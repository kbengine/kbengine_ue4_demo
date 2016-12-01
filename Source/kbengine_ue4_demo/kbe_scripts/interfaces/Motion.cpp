#include "kbengine_ue4_demo.h"
#include "Entity.h"
#include "Motion.h"

ENTITYDEF_CLASS_REGISTER(Motion)
ENTITYDEF_PROPERTY_WITH_SETMETHOD_REGISTER(Motion, moveSpeed);

Motion::Motion(Entity* entity) :
	self(entity)
{
}

Motion::~Motion()
{
}

void Motion::set_moveSpeed(int32 old)
{
	//UKBEventData_set_moveSpeed* pEventData = NewObject<UKBEventData_set_moveSpeed>();
	//pEventData->moveSpeed = moveSpeed;
	//pEventData->entityID = id();
	//KBENGINE_EVENT_FIRE("set_moveSpeed", pEventData);
}
