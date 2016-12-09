// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

class Entity;

/*
	对应entity_defs/interfaces/*
*/
class Combat
{
public:
	Combat() {}
	Combat(Entity* entity);
	virtual ~Combat();

	void set_HP(int32 old);
	void set_HP_Max(int32 old);
	void set_MP(int32 old);
	void set_MP_Max(int32 old);

	void recvDamage(int32 attackerID, int32 skillID, int32 damageType, int32 damage);

public:
	Entity* self;

	// def中定义的客户端涉及属性
	int32 HP;
	int32 HP_Max;
	int32 MP;
	int32 MP_Max;
};

/*
Declare all of the properties and methods of the KBE-Entity

Example:
	#define ENTITYDEF_DECLARE_[module name of Entity](PARENT_MODULE)	\
		ENTITYDEF_PROPERTY_*(PARENT_MODULE, xx_property)	\
		ENTITYDEF_METHOD_ARGS[0~20]_REGISTER(PARENT_MODULE, xx_method)
*/

#define ENTITYDEF_DECLARE_Combat(PARENT_MODULE)	\
	ENTITYDEF_PROPERTY_WITH_SETMETHOD_REGISTER(PARENT_MODULE, HP)	\
	ENTITYDEF_PROPERTY_WITH_SETMETHOD_REGISTER(PARENT_MODULE, HP_Max)	\
	ENTITYDEF_PROPERTY_WITH_SETMETHOD_REGISTER(PARENT_MODULE, MP)	\
	ENTITYDEF_PROPERTY_WITH_SETMETHOD_REGISTER(PARENT_MODULE, MP_Max)	\
	ENTITYDEF_METHOD_ARGS4_REGISTER(PARENT_MODULE, recvDamage)
