#include "kbengine_ue4_demo.h"
#include "Entity.h"
#include "Dialog.h"

ENTITYDEF_CLASS_REGISTER(Dialog)

Dialog::Dialog(Entity* entity) :
	self(entity)
{
}

Dialog::~Dialog()
{
}

