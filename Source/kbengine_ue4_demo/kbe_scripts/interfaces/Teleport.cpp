#include "Teleport.h"
#include "kbengine_ue4_demo.h"
#include "Entity.h"
#include "kbe_scripts/LogicEvents.h"

Teleport::Teleport(Entity* entity) :
	self(entity)
{
}

Teleport::~Teleport()
{
}

