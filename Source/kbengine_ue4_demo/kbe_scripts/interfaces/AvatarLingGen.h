// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

class Entity;

/*
	对应entity_defs/interfaces/
*/
class AvatarLingGen
{
public:
	AvatarLingGen() {}
	AvatarLingGen(Entity* entity);
	virtual ~AvatarLingGen();

	void req_generate_linggen();
	void rsp_generate_linggen(uint8 result);

public:
	Entity* self;

	// def中定义的客户端涉及属性
	uint8 is_inited;
	uint8 j;
	uint8 m;
	uint8 s;
	uint8 h;
	uint8 t;
};

/*
Declare all of the properties and methods of the KBE-Entity

Example:
	#define ENTITYDEF_DECLARE_[module name of Entity](PARENT_MODULE)	\
		ENTITYDEF_PROPERTY_*(PARENT_MODULE, xx_property)	\
		ENTITYDEF_METHOD_ARGS[0~20]_REGISTER(PARENT_MODULE, xx_method)
*/

#define ENTITYDEF_DECLARE_AvatarLingGen(PARENT_MODULE)	\
	ENTITYDEF_PROPERTY_REGISTER(PARENT_MODULE, is_inited)		\
	ENTITYDEF_PROPERTY_REGISTER(PARENT_MODULE, j)				\
	ENTITYDEF_PROPERTY_REGISTER(PARENT_MODULE, m)				\
	ENTITYDEF_PROPERTY_REGISTER(PARENT_MODULE, s)				\
	ENTITYDEF_PROPERTY_REGISTER(PARENT_MODULE, h)				\
	ENTITYDEF_PROPERTY_REGISTER(PARENT_MODULE, t)				\
	ENTITYDEF_METHOD_ARGS1_REGISTER(PARENT_MODULE, rsp_generate_linggen)
