// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Entity.h"

/*
	对应entity_defs/interfaces/
*/
class GameObject : public Entity
{
public:
	GameObject();
	virtual ~GameObject();

	void set_name(FString old);
	void set_modelID(uint32 old);
	void set_modelScale(uint8 old);

public:
	// def中定义的客户端涉及属性
	FString name;
	uint32 uid;
	uint32 utype;
	uint32 modelID;
	uint8 modelScale;
};

/*
Declare all of the properties and methods of the KBE-Entity

Example:
	#define ENTITYDEF_DECLARE_[module name of Entity](PARENT_MODULE)	\
		ENTITYDEF_PROPERTY_*(PARENT_MODULE, xx_property)	\
		ENTITYDEF_METHOD_ARGS[0~20]_REGISTER(PARENT_MODULE, xx_method)
*/

#define ENTITYDEF_DECLARE_GameObject(PARENT_MODULE)	\
	ENTITYDEF_PROPERTY_WITH_SETMETHOD_REGISTER(PARENT_MODULE, name)	\
	ENTITYDEF_PROPERTY_REGISTER(PARENT_MODULE, uid)	\
	ENTITYDEF_PROPERTY_REGISTER(PARENT_MODULE, utype)	\
	ENTITYDEF_PROPERTY_WITH_SETMETHOD_REGISTER(PARENT_MODULE, modelID)	\
	ENTITYDEF_PROPERTY_WITH_SETMETHOD_REGISTER(PARENT_MODULE, modelScale)
