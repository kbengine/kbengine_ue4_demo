#include "NPC.h"
#include "Engine/Entity.h"
#include "LogicEvents.h"

namespace KBEngine
{

NPC::NPC():
	NPCBase()
{
}

NPC::~NPC()
{
}

void NPC::onEntityNOChanged(uint32 oldValue)
{
	UKBEventData_set_entityNO* pEventData = NewObject<UKBEventData_set_entityNO>();
	pEventData->entityNO = entityNO;
	pEventData->entityID = id();
	KBENGINE_EVENT_FIRE("set_entityNO", pEventData);
}

void NPC::onModelIDChanged(uint32 oldValue)
{
	UKBEventData_set_modelID* pEventData = NewObject<UKBEventData_set_modelID>();
	pEventData->modelID = modelID;
	pEventData->entityID = id();
	KBENGINE_EVENT_FIRE("set_modelID", pEventData);
}

void NPC::onModelScaleChanged(uint8 oldValue)
{
	UKBEventData_set_modelScale* pEventData = NewObject<UKBEventData_set_modelScale>();
	pEventData->modelScale = modelScale;
	pEventData->entityID = id();
	KBENGINE_EVENT_FIRE("set_modelScale", pEventData);
}

void NPC::onMoveSpeedChanged(uint8 oldValue)
{
	velocity(moveSpeed);

	UKBEventData_set_moveSpeed* pEventData = NewObject<UKBEventData_set_moveSpeed>();
	pEventData->moveSpeed = moveSpeed;
	pEventData->entityID = id();
	KBENGINE_EVENT_FIRE("set_moveSpeed", pEventData);
}

void NPC::onNameChanged(const FString& oldValue)
{
	UKBEventData_set_name* pEventData = NewObject<UKBEventData_set_name>();
	pEventData->name = name;
	pEventData->entityID = id();
	KBENGINE_EVENT_FIRE("set_name", pEventData);
}

void NPC::onUidChanged(uint32 oldValue)
{

}

void NPC::onUtypeChanged(uint32 oldValue)
{

}

}