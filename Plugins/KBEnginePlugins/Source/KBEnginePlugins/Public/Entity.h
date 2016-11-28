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

	float velocity() const {
		return velocity_;
	}

	void velocity(float v) {
		velocity_ = v;
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

	virtual void onUpdateVolatileData()
	{
	}

	virtual void set_position(const FVector& old);
	virtual void set_direction(const FVector& old);

public:
	void baseCall(FString methodName, const TArray<KBVar*>& arguments = TArray<KBVar*>());
	void baseCall(FString methodName, KBVar arg1);
	void baseCall(FString methodName, KBVar arg1, KBVar arg2);
	void baseCall(FString methodName, KBVar arg1, KBVar arg2, KBVar arg3);
	void baseCall(FString methodName, KBVar arg1, KBVar arg2, KBVar arg3, KBVar arg4);
	void baseCall(FString methodName, KBVar arg1, KBVar arg2, KBVar arg3, KBVar arg4, KBVar arg5);
	void baseCall(FString methodName, KBVar arg1, KBVar arg2, KBVar arg3, KBVar arg4, KBVar arg5, KBVar arg6);
	void baseCall(FString methodName, KBVar arg1, KBVar arg2, KBVar arg3, KBVar arg4, KBVar arg5, KBVar arg6, KBVar arg7);
	void baseCall(FString methodName, KBVar arg1, KBVar arg2, KBVar arg3, KBVar arg4, KBVar arg5, KBVar arg6, KBVar arg7, KBVar arg8);
	void baseCall(FString methodName, KBVar arg1, KBVar arg2, KBVar arg3, KBVar arg4, KBVar arg5, KBVar arg6, KBVar arg7, KBVar arg8, KBVar arg9);
	void baseCall(FString methodName, KBVar arg1, KBVar arg2, KBVar arg3, KBVar arg4, KBVar arg5, KBVar arg6, KBVar arg7, KBVar arg8, KBVar arg9, KBVar arg10);
	void baseCall(FString methodName, KBVar arg1, KBVar arg2, KBVar arg3, KBVar arg4, KBVar arg5, KBVar arg6, KBVar arg7, KBVar arg8, KBVar arg9, KBVar arg10,
		KBVar arg11);
	void baseCall(FString methodName, KBVar arg1, KBVar arg2, KBVar arg3, KBVar arg4, KBVar arg5, KBVar arg6, KBVar arg7, KBVar arg8, KBVar arg9, KBVar arg10,
		KBVar arg11, KBVar arg12);
	void baseCall(FString methodName, KBVar arg1, KBVar arg2, KBVar arg3, KBVar arg4, KBVar arg5, KBVar arg6, KBVar arg7, KBVar arg8, KBVar arg9, KBVar arg10,
		KBVar arg11, KBVar arg12, KBVar arg13);
	void baseCall(FString methodName, KBVar arg1, KBVar arg2, KBVar arg3, KBVar arg4, KBVar arg5, KBVar arg6, KBVar arg7, KBVar arg8, KBVar arg9, KBVar arg10,
		KBVar arg11, KBVar arg12, KBVar arg13, KBVar arg14);
	void baseCall(FString methodName, KBVar arg1, KBVar arg2, KBVar arg3, KBVar arg4, KBVar arg5, KBVar arg6, KBVar arg7, KBVar arg8, KBVar arg9, KBVar arg10,
		KBVar arg11, KBVar arg12, KBVar arg13, KBVar arg14, KBVar arg15);
	void baseCall(FString methodName, KBVar arg1, KBVar arg2, KBVar arg3, KBVar arg4, KBVar arg5, KBVar arg6, KBVar arg7, KBVar arg8, KBVar arg9, KBVar arg10,
		KBVar arg11, KBVar arg12, KBVar arg13, KBVar arg14, KBVar arg15, KBVar arg16);
	void baseCall(FString methodName, KBVar arg1, KBVar arg2, KBVar arg3, KBVar arg4, KBVar arg5, KBVar arg6, KBVar arg7, KBVar arg8, KBVar arg9, KBVar arg10,
		KBVar arg11, KBVar arg12, KBVar arg13, KBVar arg14, KBVar arg15, KBVar arg16, KBVar arg17);
	void baseCall(FString methodName, KBVar arg1, KBVar arg2, KBVar arg3, KBVar arg4, KBVar arg5, KBVar arg6, KBVar arg7, KBVar arg8, KBVar arg9, KBVar arg10,
		KBVar arg11, KBVar arg12, KBVar arg13, KBVar arg14, KBVar arg15, KBVar arg16, KBVar arg17, KBVar arg18);
	void baseCall(FString methodName, KBVar arg1, KBVar arg2, KBVar arg3, KBVar arg4, KBVar arg5, KBVar arg6, KBVar arg7, KBVar arg8, KBVar arg9, KBVar arg10,
		KBVar arg11, KBVar arg12, KBVar arg13, KBVar arg14, KBVar arg15, KBVar arg16, KBVar arg17, KBVar arg18, KBVar arg19);
	void baseCall(FString methodName, KBVar arg1, KBVar arg2, KBVar arg3, KBVar arg4, KBVar arg5, KBVar arg6, KBVar arg7, KBVar arg8, KBVar arg9, KBVar arg10, 
		KBVar arg11, KBVar arg12, KBVar arg13, KBVar arg14, KBVar arg15, KBVar arg16, KBVar arg17, KBVar arg18, KBVar arg19, KBVar arg20);

	void cellCall(FString methodName, const TArray<KBVar*>& arguments = TArray<KBVar*>());
	void cellCall(FString methodName, KBVar arg1);
	void cellCall(FString methodName, KBVar arg1, KBVar arg2);
	void cellCall(FString methodName, KBVar arg1, KBVar arg2, KBVar arg3);
	void cellCall(FString methodName, KBVar arg1, KBVar arg2, KBVar arg3, KBVar arg4);
	void cellCall(FString methodName, KBVar arg1, KBVar arg2, KBVar arg3, KBVar arg4, KBVar arg5);
	void cellCall(FString methodName, KBVar arg1, KBVar arg2, KBVar arg3, KBVar arg4, KBVar arg5, KBVar arg6);
	void cellCall(FString methodName, KBVar arg1, KBVar arg2, KBVar arg3, KBVar arg4, KBVar arg5, KBVar arg6, KBVar arg7);
	void cellCall(FString methodName, KBVar arg1, KBVar arg2, KBVar arg3, KBVar arg4, KBVar arg5, KBVar arg6, KBVar arg7, KBVar arg8);
	void cellCall(FString methodName, KBVar arg1, KBVar arg2, KBVar arg3, KBVar arg4, KBVar arg5, KBVar arg6, KBVar arg7, KBVar arg8, KBVar arg9);
	void cellCall(FString methodName, KBVar arg1, KBVar arg2, KBVar arg3, KBVar arg4, KBVar arg5, KBVar arg6, KBVar arg7, KBVar arg8, KBVar arg9, KBVar arg10);
	void cellCall(FString methodName, KBVar arg1, KBVar arg2, KBVar arg3, KBVar arg4, KBVar arg5, KBVar arg6, KBVar arg7, KBVar arg8, KBVar arg9, KBVar arg10,
		KBVar arg11);
	void cellCall(FString methodName, KBVar arg1, KBVar arg2, KBVar arg3, KBVar arg4, KBVar arg5, KBVar arg6, KBVar arg7, KBVar arg8, KBVar arg9, KBVar arg10,
		KBVar arg11, KBVar arg12);
	void cellCall(FString methodName, KBVar arg1, KBVar arg2, KBVar arg3, KBVar arg4, KBVar arg5, KBVar arg6, KBVar arg7, KBVar arg8, KBVar arg9, KBVar arg10,
		KBVar arg11, KBVar arg12, KBVar arg13);
	void cellCall(FString methodName, KBVar arg1, KBVar arg2, KBVar arg3, KBVar arg4, KBVar arg5, KBVar arg6, KBVar arg7, KBVar arg8, KBVar arg9, KBVar arg10,
		KBVar arg11, KBVar arg12, KBVar arg13, KBVar arg14);
	void cellCall(FString methodName, KBVar arg1, KBVar arg2, KBVar arg3, KBVar arg4, KBVar arg5, KBVar arg6, KBVar arg7, KBVar arg8, KBVar arg9, KBVar arg10,
		KBVar arg11, KBVar arg12, KBVar arg13, KBVar arg14, KBVar arg15);
	void cellCall(FString methodName, KBVar arg1, KBVar arg2, KBVar arg3, KBVar arg4, KBVar arg5, KBVar arg6, KBVar arg7, KBVar arg8, KBVar arg9, KBVar arg10,
		KBVar arg11, KBVar arg12, KBVar arg13, KBVar arg14, KBVar arg15, KBVar arg16);
	void cellCall(FString methodName, KBVar arg1, KBVar arg2, KBVar arg3, KBVar arg4, KBVar arg5, KBVar arg6, KBVar arg7, KBVar arg8, KBVar arg9, KBVar arg10,
		KBVar arg11, KBVar arg12, KBVar arg13, KBVar arg14, KBVar arg15, KBVar arg16, KBVar arg17);
	void cellCall(FString methodName, KBVar arg1, KBVar arg2, KBVar arg3, KBVar arg4, KBVar arg5, KBVar arg6, KBVar arg7, KBVar arg8, KBVar arg9, KBVar arg10,
		KBVar arg11, KBVar arg12, KBVar arg13, KBVar arg14, KBVar arg15, KBVar arg16, KBVar arg17, KBVar arg18);
	void cellCall(FString methodName, KBVar arg1, KBVar arg2, KBVar arg3, KBVar arg4, KBVar arg5, KBVar arg6, KBVar arg7, KBVar arg8, KBVar arg9, KBVar arg10,
		KBVar arg11, KBVar arg12, KBVar arg13, KBVar arg14, KBVar arg15, KBVar arg16, KBVar arg17, KBVar arg18, KBVar arg19);
	void cellCall(FString methodName, KBVar arg1, KBVar arg2, KBVar arg3, KBVar arg4, KBVar arg5, KBVar arg6, KBVar arg7, KBVar arg8, KBVar arg9, KBVar arg10,
		KBVar arg11, KBVar arg12, KBVar arg13, KBVar arg14, KBVar arg15, KBVar arg16, KBVar arg17, KBVar arg18, KBVar arg19, KBVar arg20);

protected:
	ENTITY_ID id_;
	FString className_;

	bool isOnGround_;

	Mailbox* base_;
	Mailbox* cell_;

	// enterworld之后设置为true
	bool inWorld_;

	// 对于玩家自身来说，它表示是否自己被其它玩家控制了；
	// 对于其它entity来说，表示我本机是否控制了这个entity
	bool isControlled_;

	bool inited_;

	float velocity_;

public:
	FVector position;
	FVector direction;
	uint32 spaceID;
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

	virtual FString parentClasses()
	{	
		return FString(TEXT("Entity"));	
	}	
};

/*
	实体创建工厂类
*/
class KBENGINEPLUGINS_API EntityFactory
{
public:
	static void initialize();
	static void finishDefs(const FString& scriptName, const FString& parentScriptName);

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

	virtual void callMethod(Entity* pEntity, const KBVar& oldVal) = 0;
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

	virtual void setPropertyValue(Entity* pEntity, KBVar* val) = 0;
	virtual KBVar* getPropertyValue(Entity* pEntity) = 0;

protected:
	void setPropertyValue_(int8* out, KBVar* val) { *out = (int8)(*val); }
	void setPropertyValue_(int16* out, KBVar* val) { *out = (int16)(*val); }
	void setPropertyValue_(int32* out, KBVar* val) { *out = (int32)(*val); }
	void setPropertyValue_(int64* out, KBVar* val) { *out = (int64)(*val); }
	void setPropertyValue_(uint8* out, KBVar* val) { *out = (uint8)(*val); }
	void setPropertyValue_(uint16* out, KBVar* val) { *out = (uint16)(*val); }
	void setPropertyValue_(uint32* out, KBVar* val) { *out = (uint32)(*val); }
	void setPropertyValue_(uint64* out, KBVar* val) { *out = (uint64)(*val); }
	void setPropertyValue_(FString* out, KBVar* val) { *out = (FString)(*val); }
	void setPropertyValue_(float* out, KBVar* val) { *out = (float)(*val); }
	void setPropertyValue_(double* out, KBVar* val) { *out = (double)(*val); }
	void setPropertyValue_(bool* out, KBVar* val) { *out = (bool)(*val); }
	void setPropertyValue_(FVector* out, KBVar* val) { *out = (*val); }
	void setPropertyValue_(FVector2D* out, KBVar* val) { *out = (*val); }
	void setPropertyValue_(FVector4* out, KBVar* val) { *out = (*val); }
	void setPropertyValue_(ByteArray* out, KBVar* val) { *out = val->GetValue<ByteArray>(); }
	void setPropertyValue_(KBVar::KBVarMap* out, KBVar* val) { *out = (*val); }
	void setPropertyValue_(KBVar::KBVarArray* out, KBVar* val) { *out = val->GetValue<KBVar::KBVarArray>(); }
	void setPropertyValue_(KBVar* out, KBVar* val) { *out = (*val); }
};

class KBENGINEPLUGINS_API EntityDefPropertyHandles
{
public:
	EntityDefPropertyHandle* add(const FString& scriptName, const FString& defPropertyName, EntityDefPropertyHandle* pEntityDefPropertyHandle);
	static EntityDefPropertyHandle* find(const FString& scriptName, const FString& defPropertyName);

	TMap<FString, TMap<FString, EntityDefPropertyHandle*>> defPropertyHandles;
};


// 注册定义的实体类
#define ENTITYDEF_CLASS_REGISTER(ENTITY_SCRIPTMODULE_NAME, .../*The name of the parent classes*/)	\
	class _##ENTITY_SCRIPTMODULE_NAME##Creator : public EntityCreator {	\
		public:	\
			_##ENTITY_SCRIPTMODULE_NAME##Creator(const FString& scriptName):	\
			EntityCreator(scriptName)	\
			{	\
			}	\
			virtual ~_##ENTITY_SCRIPTMODULE_NAME##Creator()	\
			{	\
			}	\
			virtual Entity* create() override	\
			{	\
				return (Entity*)(new ENTITY_SCRIPTMODULE_NAME());	\
			}	\
			virtual FString parentClasses() override	\
			{	\
				return FString(#__VA_ARGS__);	\
			}	\
	};\
	_##ENTITY_SCRIPTMODULE_NAME##Creator g_ENTITY_SCRIPTMODULE_NAME##Creator(FString(TEXT(#ENTITY_SCRIPTMODULE_NAME)));	\


// 注册定义的方法
#define ENTITYDEF_METHOD_REGISTER(ENTITY_SCRIPTMODULE_NAME, DEF_METHOD_NAME)	\
	class _##ENTITY_SCRIPTMODULE_NAME##_##DEF_METHOD_NAME##DefMethodHandle : public EntityDefMethodHandle {	\
		public:	\
			_##ENTITY_SCRIPTMODULE_NAME##_##DEF_METHOD_NAME##DefMethodHandle(const FString& scriptName, const FString& defMethodName):	\
			EntityDefMethodHandle(scriptName, defMethodName)	\
			{	\
			}	\
			virtual ~_##ENTITY_SCRIPTMODULE_NAME##_##DEF_METHOD_NAME##DefMethodHandle()	\
			{	\
			}	\
			virtual void callMethod(Entity* pEntity, const KBVar& val) override	\
			{	\
				static_cast<ENTITY_SCRIPTMODULE_NAME*>(pEntity)->DEF_METHOD_NAME(val);	\
			}	\
	};\
	_##ENTITY_SCRIPTMODULE_NAME##_##DEF_METHOD_NAME##DefMethodHandle g_ENTITY_SCRIPTMODULE_NAME##_##DEF_METHOD_NAME##DefMethodHandle(FString(TEXT(#ENTITY_SCRIPTMODULE_NAME)), FString(TEXT(#DEF_METHOD_NAME)));	\


// 注册定义的属性
#define ENTITYDEF_PROPERTY_REGISTER(ENTITY_SCRIPTMODULE_NAME, DEF_PROPERTY_NAME)	\
	class _##ENTITY_SCRIPTMODULE_NAME##_##DEF_PROPERTY_NAME##DefPropertyHandle : public EntityDefPropertyHandle {	\
		public:	\
			_##ENTITY_SCRIPTMODULE_NAME##_##DEF_PROPERTY_NAME##DefPropertyHandle(const FString& scriptName, const FString& defPropertyName):	\
			EntityDefPropertyHandle(scriptName, defPropertyName)	\
			{	\
			}	\
			virtual ~_##ENTITY_SCRIPTMODULE_NAME##_##DEF_PROPERTY_NAME##DefPropertyHandle()	\
			{	\
			}	\
			virtual void setPropertyValue(Entity* pEntity, KBVar* val) override	\
			{	\
				setPropertyValue_(&static_cast<ENTITY_SCRIPTMODULE_NAME*>(pEntity)->DEF_PROPERTY_NAME, val);	\
			}	\
			virtual KBVar* getPropertyValue(Entity* pEntity) override	\
			{	\
				return new KBVar(static_cast<ENTITY_SCRIPTMODULE_NAME*>(pEntity)->DEF_PROPERTY_NAME);	\
			}	\
	};\
	_##ENTITY_SCRIPTMODULE_NAME##_##DEF_PROPERTY_NAME##DefPropertyHandle g_##ENTITY_SCRIPTMODULE_NAME##_##DEF_PROPERTY_NAME##DefPropertyHandle(FString(TEXT(#ENTITY_SCRIPTMODULE_NAME)), FString(TEXT(#DEF_PROPERTY_NAME)));	\

// 注册定义的属性, 使用一个别名替代
#define ENTITYDEF_PROPERTY_ALIAS_REGISTER(ENTITY_SCRIPTMODULE_NAME, DEF_PROPERTY_NAME, PROPERTY_NAME)	\
	class _##ENTITY_SCRIPTMODULE_NAME##_##DEF_PROPERTY_NAME##DefPropertyHandle : public EntityDefPropertyHandle {	\
		public:	\
			_##ENTITY_SCRIPTMODULE_NAME##_##DEF_PROPERTY_NAME##DefPropertyHandle(const FString& scriptName, const FString& defPropertyName):	\
			EntityDefPropertyHandle(scriptName, defPropertyName)	\
			{	\
			}	\
			virtual ~_##ENTITY_SCRIPTMODULE_NAME##_##DEF_PROPERTY_NAME##DefPropertyHandle()	\
			{	\
			}	\
			virtual void setPropertyValue(Entity* pEntity, KBVar* val) override	\
			{	\
				setPropertyValue_(&static_cast<ENTITY_SCRIPTMODULE_NAME*>(pEntity)->PROPERTY_NAME, val);	\
			}	\
			virtual KBVar* getPropertyValue(Entity* pEntity) override	\
			{	\
				return new KBVar(static_cast<ENTITY_SCRIPTMODULE_NAME*>(pEntity)->PROPERTY_NAME);	\
			}	\
	};\
	_##ENTITY_SCRIPTMODULE_NAME##_##DEF_PROPERTY_NAME##DefPropertyHandle g_##ENTITY_SCRIPTMODULE_NAME##_##DEF_PROPERTY_NAME##DefPropertyHandle(FString(TEXT(#ENTITY_SCRIPTMODULE_NAME)), FString(TEXT(#DEF_PROPERTY_NAME)));	\

// 注册定义的属性，并且属性包含一个set_*方法，属性被更新后改方法被调用
#define ENTITYDEF_PROPERTY_WITH_SETMETHOD_REGISTER(ENTITY_SCRIPTMODULE_NAME, DEF_PROPERTY_NAME)	\
	ENTITYDEF_PROPERTY_REGISTER(ENTITY_SCRIPTMODULE_NAME, DEF_PROPERTY_NAME)	\
	ENTITYDEF_METHOD_REGISTER(ENTITY_SCRIPTMODULE_NAME, set_##DEF_PROPERTY_NAME)	\

	






