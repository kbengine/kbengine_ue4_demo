
#include "KBEnginePluginsPrivatePCH.h"
#include "Entity.h"
#include "KBEngine.h"

EntityFactory g_EntityFactory;
EntityDefMethodHandles g_EntityDefMethodHandles;
EntityDefPropertyHandles g_EntityDefPropertyHandles;

EntityCreator::EntityCreator(const FString& scriptName)
{
	g_EntityFactory.addEntityCreator(scriptName, this);
}

EntityCreator::~EntityCreator()
{
}

EntityDefMethodHandle::EntityDefMethodHandle(const FString& scriptName, const FString& defMethodName)
{
	g_EntityDefMethodHandles.add(scriptName, defMethodName, this);
}

EntityDefMethodHandle::~EntityDefMethodHandle()
{

}

EntityDefPropertyHandle::EntityDefPropertyHandle(const FString& scriptName, const FString& defPropertyName)
{
	g_EntityDefPropertyHandles.add(scriptName, defPropertyName, this);
}

EntityDefPropertyHandle::~EntityDefPropertyHandle()
{

}

EntityCreator* EntityFactory::addEntityCreator(const FString& scriptName, EntityCreator* pEntityCreator)
{
	creators.Add(scriptName, pEntityCreator);
	DEBUG_MSG("%s", *scriptName);
	return pEntityCreator;
}

EntityCreator* EntityFactory::findCreator(const FString& scriptName)
{
	EntityCreator** pCreator = g_EntityFactory.creators.Find(scriptName);
	if (pCreator == NULL)
	{
		return NULL;
	}

	return (*pCreator);
}

Entity* EntityFactory::create(const FString& scriptName)
{
	EntityCreator** pCreator = g_EntityFactory.creators.Find(scriptName);
	if (pCreator == NULL)
	{
		return NULL;
	}

	Entity* pEntity = (*pCreator)->create();
	pEntity->className(scriptName);
	return pEntity;
}

EntityDefMethodHandle* EntityDefMethodHandles::add(const FString& scriptName, const FString& defMethodName, EntityDefMethodHandle* pEntityDefMethodHandle)
{
	if (!defMethodHandles.Contains(scriptName))
		defMethodHandles.Add(scriptName, TMap<FString, EntityDefMethodHandle*>());

	TMap<FString, EntityDefMethodHandle*>* m = defMethodHandles.Find(scriptName);

	if (m->Contains(defMethodName))
	{
		ERROR_MSG("%s::%s exist!", *scriptName, *defMethodName);
		return NULL;
	}

	DEBUG_MSG("%s::%s", *scriptName, *defMethodName);
	m->Add(defMethodName, pEntityDefMethodHandle);
	return pEntityDefMethodHandle;
}

EntityDefMethodHandle* EntityDefMethodHandles::find(const FString& scriptName, const FString& defMethodName)
{
	TMap<FString, EntityDefMethodHandle*>* m = g_EntityDefMethodHandles.defMethodHandles.Find(scriptName);
	if (!m)
		return NULL;

	EntityDefMethodHandle** pEntityDefMethodHandle = m->Find(defMethodName);
	if (!pEntityDefMethodHandle)
		return NULL;

	return *pEntityDefMethodHandle;
}

EntityDefPropertyHandle* EntityDefPropertyHandles::add(const FString& scriptName, const FString& defPropertyName, EntityDefPropertyHandle* pEntityDefPropertyHandle)
{
	if (!defPropertyHandles.Contains(scriptName))
		defPropertyHandles.Add(scriptName, TMap<FString, EntityDefPropertyHandle*>());

	TMap<FString, EntityDefPropertyHandle*>* m = defPropertyHandles.Find(scriptName);

	if (m->Contains(defPropertyName))
	{
		ERROR_MSG("%s::%s exist!", *scriptName, *defPropertyName);
		return NULL;
	}

	DEBUG_MSG("%s::%s", *scriptName, *defPropertyName);
	m->Add(defPropertyName, pEntityDefPropertyHandle);
	return pEntityDefPropertyHandle;
}

EntityDefPropertyHandle* EntityDefPropertyHandles::find(const FString& scriptName, const FString& defPropertyName)
{
	TMap<FString, EntityDefPropertyHandle*>* m = g_EntityDefPropertyHandles.defPropertyHandles.Find(scriptName);
	if (!m)
		return NULL;

	EntityDefPropertyHandle** pEntityDefPropertyHandle = m->Find(defPropertyName);
	if (!pEntityDefPropertyHandle)
		return NULL;

	return *pEntityDefPropertyHandle;
}

Entity::Entity():
	id_(0),
	className_(TEXT("")),
	position_(),
	direction_(),
	isOnGround_(false),
	base_(NULL),
	cell_(NULL),
	inWorld_(false),
	isControlled_(false),
	inited_(false)
{
}

Entity::~Entity()
{
}

void Entity::clear()
{

}

void Entity::__init__()
{

}

bool Entity::isPlayer()
{
	return id() == KBEngineApp::getSingleton().entity_id();
}

void Entity::callPropertysSetMethods()
{

}

void Entity::enterWorld()
{

}

void Entity::onEnterWorld()
{

}

void Entity::leaveWorld()
{

}

void Entity::onLeaveWorld()
{

}

void Entity::enterSpace()
{

}

void Entity::onEnterSpace()
{

}

void Entity::leaveSpace()
{

}

void Entity::onLeaveSpace()
{

}