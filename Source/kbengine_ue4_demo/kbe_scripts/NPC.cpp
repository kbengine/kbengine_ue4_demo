#include "kbengine_ue4_demo.h"
#include "Entity.h"
#include "interfaces/GameObject.h"
#include "interfaces/NPCObject.h"
#include "interfaces/Motion.h"
#include "NPC.h"

ENTITYDEF_CLASS_REGISTER(NPC, GameObject, NPCObject, Motion)

ENTITYDEF_DECLARE_GameObject(NPC)
ENTITYDEF_DECLARE_Motion(NPC)
ENTITYDEF_DECLARE_NPCObject(NPC)


NPC::NPC():
	GameObject(),
	NPCObject(this),
	Motion(this)
{
}

NPC::~NPC()
{
}
