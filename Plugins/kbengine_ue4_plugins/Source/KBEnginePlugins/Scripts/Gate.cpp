#include "Gate.h"
#include "Engine/Entity.h"
#include "LogicEvents.h"

namespace KBEngine
{

Gate::Gate():
	GateBase()
{
}

Gate::~Gate()
{
}

void Gate::onModelIDChanged(uint32 oldValue)
{
	UKBEventData_set_modelID* pEventData = NewObject<UKBEventData_set_modelID>();
	pEventData->modelID = modelID;
	pEventData->entityID = id();
	KBENGINE_EVENT_FIRE("set_modelID", pEventData);
}

void Gate::onModelScaleChanged(uint8 oldValue)
{
	UKBEventData_set_modelScale* pEventData = NewObject<UKBEventData_set_modelScale>();
	pEventData->modelScale = modelScale;
	pEventData->entityID = id();
	KBENGINE_EVENT_FIRE("set_modelScale", pEventData);
}

void Gate::onNameChanged(const FString& oldValue)
{
	UKBEventData_set_name* pEventData = NewObject<UKBEventData_set_name>();
	pEventData->name = name;
	pEventData->entityID = id();
	KBENGINE_EVENT_FIRE("set_name", pEventData);
}

void Gate::onEntityNOChanged(uint32 oldValue)
{
	UKBEventData_set_entityNO* pEventData = NewObject<UKBEventData_set_entityNO>();
	pEventData->entityNO = entityNO;
	pEventData->entityID = id();
	KBENGINE_EVENT_FIRE("set_entityNO", pEventData);
}

}