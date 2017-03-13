#include "kbengine_ue4_demo.h"
#include "Entity.h"
#include "AvatarLingGen.h"
#include "KBEngine.h"
#include "../LogicEvents.h"

AvatarLingGen::AvatarLingGen(Entity* entity) :
	self(entity)
{
	//// ×¢²áÊÂ¼þ
	//KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("req_generate_linggen", "req_generate_linggen", [this](const UKBEventData* pEventData)
	//{
	//	const UKBEventData_req_generate_linggen& data = static_cast<const UKBEventData_req_generate_linggen&>(*pEventData);
	//	req_generate_linggen();
	//});
}

AvatarLingGen::~AvatarLingGen()
{
}

void AvatarLingGen::req_generate_linggen()
{
	DEBUG_MSG("AvatarLingGen::req_generate_linggen");
	self->baseCall("req_generate_linggen");
}

void AvatarLingGen::rsp_generate_linggen(uint8 result)
{
	DEBUG_MSG("AvatarLingGen::rsp_generate_linggen(%d)", result);
}