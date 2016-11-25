
#include "KBEnginePluginsPrivatePCH.h"
#include "Entity.h"
#include "KBEngine.h"
#include "KBEvent.h"
#include "DataTypes.h"
#include "Method.h"
#include "ScriptModule.h"
#include "Mailbox.h"

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

void EntityFactory::initialize()
{
	static bool inited = false;

	if (inited)
		return;

	inited = true;

	// 填充所有父类的def信息到子类
	for (auto& item : g_EntityFactory.creators)
	{
		FString scriptName = item.Key;
		EntityCreator* pEntityCreator = item.Value;
		FString parentClasses = pEntityCreator->parentClasses();
		if (parentClasses.Len() == 0)
			continue;

		TArray<FString> parentClassesArray;
		parentClasses.ParseIntoArray(parentClassesArray, TEXT(","), true);

		for (auto& m : parentClassesArray)
		{
			EntityCreator* pEntityParentCreator = g_EntityFactory.creators.FindRef(m);
			if (!pEntityParentCreator || pEntityParentCreator == pEntityCreator)
				continue;

			finishDefs(scriptName, m);
		}
	}
}

void EntityFactory::finishDefs(const FString& scriptName, const FString& parentScriptName)
{
	EntityCreator* pEntityCreator = g_EntityFactory.creators.FindRef(scriptName);
	EntityCreator* pEntityScriptParentCreator = g_EntityFactory.creators.FindRef(parentScriptName);

	const TMap<FString, EntityDefMethodHandle*>& EntityDefMethodHandleArray = g_EntityDefMethodHandles.defMethodHandles.FindRef(parentScriptName);
	for (auto& m1 : EntityDefMethodHandleArray)
	{
		g_EntityDefMethodHandles.add(scriptName, m1.Key, m1.Value);
	}

	const TMap<FString, EntityDefPropertyHandle*>& EntityDefPropertyHandleArray = g_EntityDefPropertyHandles.defPropertyHandles.FindRef(parentScriptName);
	for (auto& m2 : EntityDefPropertyHandleArray)
	{
		g_EntityDefPropertyHandles.add(scriptName, m2.Key, m2.Value);
	}

	FString parentClasses = pEntityScriptParentCreator->parentClasses();
	if (parentClasses.Len() == 0)
		return;

	TArray<FString> parentClassesArray;
	parentClasses.ParseIntoArray(parentClassesArray, TEXT(","), true);

	for (auto& m : parentClassesArray)
	{
		EntityCreator* pEntityParentCreator = g_EntityFactory.creators.FindRef(m);
		if (!pEntityParentCreator || pEntityParentCreator == pEntityCreator)
			continue;

		finishDefs(scriptName, m);
	}
}

Entity* EntityFactory::create(const FString& scriptName)
{
	EntityCreator** pCreator = g_EntityFactory.creators.Find(scriptName);
	if (pCreator == NULL)
	{
		return NULL;
	}

	Entity* pEntity = (*pCreator)->create();
	return pEntity;
}

EntityDefMethodHandle* EntityDefMethodHandles::add(const FString& scriptName, const FString& defMethodName, EntityDefMethodHandle* pEntityDefMethodHandle)
{
	if (!defMethodHandles.Contains(scriptName))
		defMethodHandles.Add(scriptName, TMap<FString, EntityDefMethodHandle*>());

	TMap<FString, EntityDefMethodHandle*>* m = defMethodHandles.Find(scriptName);

	if (m->Contains(defMethodName))
	{
		SCREEN_ERROR_MSG("%s::%s exist!", *scriptName, *defMethodName);
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
		SCREEN_ERROR_MSG("%s::%s exist!", *scriptName, *defPropertyName);
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

ENTITYDEF_CLASS_REGISTER(Entity)
ENTITYDEF_PROPERTY_WITH_SETMETHOD_REGISTER(Entity, position)
ENTITYDEF_PROPERTY_WITH_SETMETHOD_REGISTER(Entity, direction)
ENTITYDEF_PROPERTY_REGISTER(Entity, spaceID)

Entity::Entity():
	id_(0),
	className_(TEXT("")),
	isOnGround_(false),
	base_(NULL),
	cell_(NULL),
	inWorld_(false),
	isControlled_(false),
	inited_(false),
	velocity_(0.f),
	position(),
	direction(),
	spaceID(0)
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
	inWorld_ = true;

	onEnterWorld();

	UKBEventData_onEnterWorld* pEventData = NewObject<UKBEventData_onEnterWorld>();
	KBENGINE_EVENT_FIRE("onEnterWorld", pEventData);
}

void Entity::onEnterWorld()
{

}

void Entity::leaveWorld()
{
	inWorld_ = false;

	onLeaveWorld();

	UKBEventData_onLeaveWorld* pEventData = NewObject<UKBEventData_onLeaveWorld>();
	KBENGINE_EVENT_FIRE("onLeaveWorld", pEventData);
}

void Entity::onLeaveWorld()
{

}

void Entity::enterSpace()
{
	inWorld_ = true;

	onEnterSpace();

	UKBEventData_onEnterSpace* pEventData = NewObject<UKBEventData_onEnterSpace>();
	KBENGINE_EVENT_FIRE("onEnterSpace", pEventData);
}

void Entity::onEnterSpace()
{

}

void Entity::leaveSpace()
{
	inWorld_ = false;

	onLeaveSpace();

	UKBEventData_onLeaveSpace* pEventData = NewObject<UKBEventData_onLeaveSpace>();
	KBENGINE_EVENT_FIRE("onLeaveSpace", pEventData);
}

void Entity::onLeaveSpace()
{

}

void Entity::baseCall(FString methodName, KBVar arg1)
{
	TArray<KBVar*> arguments;
	arguments.Add(&arg1);
	baseCall(methodName, arguments);
}

void Entity::baseCall(FString methodName, KBVar arg1, KBVar arg2)
{
	TArray<KBVar*> arguments;
	arguments.Add(&arg1);
	arguments.Add(&arg2);
	baseCall(methodName, arguments);
}

void Entity::baseCall(FString methodName, const TArray<KBVar*>& arguments)
{
	if (KBEngineApp::getSingleton().currserver() == TEXT("loginapp"))
	{
		ERROR_MSG("className=%s, methodName=%s, currserver=(%s != baseapp)!", 
			*className_, *methodName, *KBEngineApp::getSingleton().currserver());

		return;
	}

	Method** pMethodFind = EntityDef::moduledefs[className_]->base_methods.Find(methodName);
	if (!pMethodFind)
	{
		SCREEN_ERROR_MSG("className=%s, not found methodName(%s)!",
			*className_, *methodName);

		return;
	}

	uint16 methodID = (*pMethodFind)->methodUtype;

	TArray<KBEDATATYPE_BASE*>& args = (*pMethodFind)->args;
	if (arguments.Num() != args.Num())
	{
		ERROR_MSG("className=%s, methodName=%s, args(%d != %d)!",
			*className_, *methodName, arguments.Num(), (*pMethodFind)->args.Num());

		return;
	}

	if (!base_)
	{
		ERROR_MSG("%s no base! methodName=%s", *className_, *methodName);
		return;
	}

	base_->newMail();
	(*base_->pBundle) << methodID;

	for (int32 i = 0; i<args.Num(); ++i)
	{
		if (args[i]->isSameType(*arguments[i]))
		{
			args[i]->addToStream(*base_->pBundle, *arguments[i]);
		}
		else
		{
			ERROR_MSG("className=%s, methodName=%s, args%d error!",
				*className_, *methodName, i);
		}
	}

	base_->postMail(NULL);
}

void Entity::cellCall(FString methodName, const TArray<KBVar*>& arguments)
{
	if (KBEngineApp::getSingleton().currserver() == TEXT("loginapp"))
	{
		ERROR_MSG("className=%s, methodName=%s, currserver=(%s != baseapp)!",
			*className_, *methodName, *KBEngineApp::getSingleton().currserver());

		return;
	}

	Method** pMethodFind = EntityDef::moduledefs[className_]->cell_methods.Find(methodName);
	if (!pMethodFind)
	{
		SCREEN_ERROR_MSG("className=%s, not found methodName(%s)!",
			*className_, *methodName);

		return;
	}

	uint16 methodID = (*pMethodFind)->methodUtype;

	TArray<KBEDATATYPE_BASE*>& args = (*pMethodFind)->args;
	if (arguments.Num() != args.Num())
	{
		ERROR_MSG("className=%s, methodName=%s, args(%d != %d)!",
			*className_, *methodName, arguments.Num(), (*pMethodFind)->args.Num());

		return;
	}

	if (!cell_)
	{
		ERROR_MSG("%s no cell! methodName=%s", *className_, *methodName);
		return;
	}

	cell_->newMail();
	(*cell_->pBundle) << methodID;

	for (int32 i = 0; i<args.Num(); ++i)
	{
		if (args[i]->isSameType(*arguments[i]))
		{
			args[i]->addToStream(*cell_->pBundle, *arguments[i]);
		}
		else
		{
			ERROR_MSG("className=%s, methodName=%s, args%d error!",
				*className_, *methodName, i);
		}
	}

	cell_->postMail(NULL);
}

void Entity::set_position(const FVector& old)
{
	if (isPlayer())
		KBEngineApp::getSingleton().entityServerPos(position);

	if (inWorld_)
	{
		UKBEventData_set_position* pEventData = NewObject<UKBEventData_set_position>();
		pEventData->position = position;
		KBENGINE_EVENT_FIRE("set_position", pEventData);
	}
}

void Entity::set_direction(const FVector& old)
{
	if (inWorld_)
	{
		UKBEventData_set_direction* pEventData = NewObject<UKBEventData_set_direction>();
		pEventData->direction = FRotator();
		KBENGINE_EVENT_FIRE("set_direction", pEventData);
	}
}

