#include "kbengine_ue4_demo.h"
#include "Entity.h"
#include "interfaces/GameObject.h"
#include "NPC.h"

ENTITYDEF_CLASS_REGISTER(NPC, GameObject)

NPC::NPC():
	GameObject()
{
}

NPC::~NPC()
{
}
