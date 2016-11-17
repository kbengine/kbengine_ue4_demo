// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.



#pragma once

#include "KBVar.h"
#include "KBECommon.h"

class Mailbox;


/*
	KBEngine逻辑层的实体基础类
	所有扩展出的游戏实体都应该继承于该模块
*/
class KBENGINEPLUGINS_API Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual void __init__();

	static void clear();

public:
	const FString& className() const {
		return className_;
	}

	void className(const FString& v) {
		className_ = v;
	}

	bool inWorld() const {
		return inWorld_;
	}

	void inWorld(bool v) {
		inWorld_ = v;
	}

	bool isControlled() const {
		return isControlled_;
	}

	void isControlled(bool v) {
		isControlled_ = v;
	}

	bool inited() const {
		return inited_;
	}

	void inited(bool v) {
		inited_ = v;
	}

	ENTITY_ID id() const {
		return id_;
	}

	void id(ENTITY_ID v) {
		id_ = v;
	}

	Mailbox* base() const {
		return base_;
	}

	void base(Mailbox* v) {
		base_ = v;
	}

	Mailbox* cell() const {
		return cell_;
	}

	void cell(Mailbox* v) {
		cell_ = v;
	}


	bool isPlayer();

public:
	virtual void callPropertysSetMethods();

	virtual void onDestroy()
	{
	}

	void enterWorld();
	virtual void onEnterWorld();
	void leaveWorld();
	virtual void onLeaveWorld();

	virtual void enterSpace();
	virtual void onEnterSpace();
	virtual void leaveSpace();
	virtual void onLeaveSpace();

	// This callback method is called when the local entity control by the client has been enabled or disabled. 
	// See the Entity.controlledBy() method in the CellApp server code for more infomation.
	// 对于玩家自身来说，它表示是否自己被其它玩家控制了；
	// 对于其它entity来说，表示我本机是否控制了这个entity
	virtual void onControlled(bool isControlled)
	{

	}

protected:
	ENTITY_ID id_;
	FString className_;

	FVector position_;
	FVector direction_;

	bool isOnGround_;

	Mailbox* base_;
	Mailbox* cell_;

	// enterworld之后设置为true
	bool inWorld_;

	// 对于玩家自身来说，它表示是否自己被其它玩家控制了；
	// 对于其它entity来说，表示我本机是否控制了这个entity
	bool isControlled_;

	bool inited_;
};

/*
	用于在需要创建某个实体时被插件底层调用创建。
	每添加一个新的实体必须在源代码中加入宏 KBENGINE_ENTITY_CLASS_REGISTER(XEntity)，以便底层注册一个相关的EntityCreator
*/
class KBENGINEPLUGINS_API EntityCreator
{
public:
	EntityCreator(const FString& scriptName);

	virtual ~EntityCreator();

	virtual Entity* create() = 0;
};

/*
	实体创建工厂类
*/
class KBENGINEPLUGINS_API EntityFactory
{
public:
	static Entity* create(const FString& scriptName);
	EntityCreator* addEntityCreator(const FString& scriptName, EntityCreator* pEntityCreator);

	static EntityCreator* findCreator(const FString& scriptName);

	TMap<FString, EntityCreator*> creators;
};

/*
	包装实体的defined方法
*/
class KBENGINEPLUGINS_API EntityDefMethodHandle
{
public:
	EntityDefMethodHandle(const FString& scriptName, const FString& defMethodName);

	virtual ~EntityDefMethodHandle();

	virtual void callMethod(Entity* pEntity, KBVar* oldVal) = 0;
};

class KBENGINEPLUGINS_API EntityDefMethodHandles
{
public:
	EntityDefMethodHandle* add(const FString& scriptName, const FString& defMethodName, EntityDefMethodHandle* pEntityDefMethodHandle);
	static EntityDefMethodHandle* find(const FString& scriptName, const FString& defMethodName);

	TMap<FString, TMap<FString, EntityDefMethodHandle*>> defMethodHandles;
};

/*
	包装实体的defined属性
*/
class KBENGINEPLUGINS_API EntityDefPropertyHandle
{
public:
	EntityDefPropertyHandle(const FString& scriptName, const FString& defPropertyName);

	virtual ~EntityDefPropertyHandle();

	virtual void setPropertyValue(Entity* pEntity, KBVar* oldVal) = 0;
	virtual KBVar* getPropertyValue(Entity* pEntity) = 0;
};

class KBENGINEPLUGINS_API EntityDefPropertyHandles
{
public:
	EntityDefPropertyHandle* add(const FString& scriptName, const FString& defPropertyName, EntityDefPropertyHandle* pEntityDefPropertyHandle);
	static EntityDefPropertyHandle* find(const FString& scriptName, const FString& defPropertyName);

	TMap<FString, TMap<FString, EntityDefPropertyHandle*>> defPropertyHandles;
};


// 注册定义的实体类
#define ENTITYDEF_CLASS_REGISTER(ENTITY_SCRIPTMODULE_NAME)	\
	class ENTITY_SCRIPTMODULE_NAME##Creator : public EntityCreator {	\
		public:	\
			ENTITY_SCRIPTMODULE_NAME##Creator(const FString& scriptName):	\
			EntityCreator(scriptName)	\
			{	\
			}	\
			virtual ~ENTITY_SCRIPTMODULE_NAME##Creator()	\
			{	\
			}	\
			virtual Entity* create() override	\
			{	\
				return new ENTITY_SCRIPTMODULE_NAME();	\
			}	\
	};\
	ENTITY_SCRIPTMODULE_NAME##Creator g_ENTITY_SCRIPTMODULE_NAME##Creator(FString(TEXT(#ENTITY_SCRIPTMODULE_NAME)));	\


// 注册定义的方法
#define ENTITYDEF_METHOD_REGISTER(ENTITY_SCRIPTMODULE_NAME, DEF_METHOD_NAME)	\
	class ENTITY_SCRIPTMODULE_NAME##DefMethodHandle : public EntityDefMethodHandle {	\
		public:	\
			ENTITY_SCRIPTMODULE_NAME##DefMethodHandle(const FString& scriptName, const FString& defMethodName):	\
			EntityDefMethodHandle(scriptName, defMethodName)	\
			{	\
			}	\
			virtual ~ENTITY_SCRIPTMODULE_NAME##DefMethodHandle()	\
			{	\
			}	\
			virtual void callMethod(Entity* pEntity, KBVar* oldVal) override	\
			{	\
				static_cast<ENTITY_SCRIPTMODULE_NAME*>(pEntity)->DEF_METHOD_NAME(*oldVal);	\
			}	\
	};\
	ENTITY_SCRIPTMODULE_NAME##DefMethodHandle g_ENTITY_SCRIPTMODULE_NAME##DefMethodHandle(FString(TEXT(#ENTITY_SCRIPTMODULE_NAME)), FString(TEXT(#DEF_METHOD_NAME)));	\


// 注册定义的属性
#define ENTITYDEF_PROPERTY_REGISTER(ENTITY_SCRIPTMODULE_NAME, DEF_PROPERTY_NAME)	\
	class ENTITY_SCRIPTMODULE_NAME##DefPropertyHandle : public EntityDefPropertyHandle {	\
		public:	\
			ENTITY_SCRIPTMODULE_NAME##DefPropertyHandle(const FString& scriptName, const FString& defPropertyName):	\
			EntityDefPropertyHandle(scriptName, defPropertyName)	\
			{	\
			}	\
			virtual ~ENTITY_SCRIPTMODULE_NAME##DefPropertyHandle()	\
			{	\
			}	\
			virtual void setPropertyValue(Entity* pEntity, KBVar* oldVal) override	\
			{	\
				static_cast<ENTITY_SCRIPTMODULE_NAME*>(pEntity)->DEF_PROPERTY_NAME = *oldVal;	\
			}	\
			virtual KBVar* getPropertyValue(Entity* pEntity) override	\
			{	\
				return new KBVar(static_cast<ENTITY_SCRIPTMODULE_NAME*>(pEntity)->DEF_PROPERTY_NAME);	\
			}	\
	};\
	ENTITY_SCRIPTMODULE_NAME##DefPropertyHandle g_ENTITY_SCRIPTMODULE_NAME##DefPropertyHandle(FString(TEXT(#ENTITY_SCRIPTMODULE_NAME)), FString(TEXT(#DEF_PROPERTY_NAME)));	\


// 注册定义的属性，并且属性包含一个set_*方法，属性被更新后改方法被调用
#define ENTITYDEF_PROPERTY_AND_SETMETHOD_REGISTER(ENTITY_SCRIPTMODULE_NAME, DEF_PROPERTY_NAME)	\
	ENTITYDEF_PROPERTY_REGISTER(ENTITY_SCRIPTMODULE_NAME, DEF_PROPERTY_NAME)	\
	ENTITYDEF_METHOD_REGISTER(ENTITY_SCRIPTMODULE_NAME, set_DEF_PROPERTY_NAME)	\

	






