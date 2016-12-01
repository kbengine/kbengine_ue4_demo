#include "kbengine_ue4_demo.h"
#include "Entity.h"
#include "interfaces/GameObject.h"
#include "interfaces/NPCObject.h"
#include "NPC.h"

ENTITYDEF_CLASS_REGISTER(NPC, GameObject, NPCObject)

NPC::NPC():
	GameObject(),
	NPCObject(this)
{
}

NPC::~NPC()
{
}
