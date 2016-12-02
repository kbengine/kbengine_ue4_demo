#include "kbengine_ue4_demo.h"
#include "Entity.h"
#include "Teleport.h"


Teleport::Teleport(Entity* entity) :
	self(entity)
{
}

Teleport::~Teleport()
{
}

