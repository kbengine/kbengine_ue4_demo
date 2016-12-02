#include "kbengine_ue4_demo.h"
#include "Entity.h"
#include "State.h"


State::State(Entity* entity) :
	self(entity)
{
}

State::~State()
{
}

void State::set_state(int8 old)
{
	//UKBEventData_set_state* pEventData = NewObject<UKBEventData_set_state>();
	//pEventData->state = state;
	//pEventData->entityID = id();
	//KBENGINE_EVENT_FIRE("set_state", pEventData);
}

void State::set_subState(uint8 old)
{
	//UKBEventData_set_subState* pEventData = NewObject<UKBEventData_set_subState>();
	//pEventData->subState = subState;
	//pEventData->entityID = id();
	//KBENGINE_EVENT_FIRE("set_subState", pEventData);
}

void State::set_forbids(int32 old)
{
	//UKBEventData_set_forbids* pEventData = NewObject<UKBEventData_set_forbids>();
	//pEventData->forbids = forbids;
	//pEventData->entityID = id();
	//KBENGINE_EVENT_FIRE("set_forbids", pEventData);
}

