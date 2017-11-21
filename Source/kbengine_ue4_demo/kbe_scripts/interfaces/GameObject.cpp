#include "GameObject.h"
#include "kbengine_ue4_demo.h"
#include "kbe_scripts/LogicEvents.h"

GameObject::GameObject():
	Entity(),
	name(),
	uid(0),
	utype(0),
	modelID(0),
	modelScale(0)
{
}

GameObject::~GameObject()
{
}

void GameObject::set_name(FString old)
{
	UKBEventData_set_name* pEventData = NewObject<UKBEventData_set_name>();
	pEventData->name = name;
	pEventData->entityID = id();
	KBENGINE_EVENT_FIRE("set_name", pEventData);
}

void GameObject::set_modelID(uint32 old)
{
	UKBEventData_set_modelID* pEventData = NewObject<UKBEventData_set_modelID>();
	pEventData->modelID = modelID;
	pEventData->entityID = id();
	KBENGINE_EVENT_FIRE("set_modelID", pEventData);
}

void GameObject::set_modelScale(uint8 old)
{
	UKBEventData_set_modelScale* pEventData = NewObject<UKBEventData_set_modelScale>();
	pEventData->modelScale = modelScale;
	pEventData->entityID = id();
	KBENGINE_EVENT_FIRE("set_modelScale", pEventData);
}