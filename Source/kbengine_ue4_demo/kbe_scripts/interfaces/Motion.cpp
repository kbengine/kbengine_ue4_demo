#include "Motion.h"
#include "kbengine_ue4_demo.h"
#include "Entity.h"
#include "kbe_scripts/LogicEvents.h"

Motion::Motion(Entity* entity) :
	self(entity)
{
}

Motion::~Motion()
{
}

void Motion::set_moveSpeed(uint8 old)
{
	self->velocity(moveSpeed);

	UKBEventData_set_moveSpeed* pEventData = NewObject<UKBEventData_set_moveSpeed>();
	pEventData->moveSpeed = moveSpeed;
	pEventData->entityID = self->id();
	KBENGINE_EVENT_FIRE("set_moveSpeed", pEventData);
}
