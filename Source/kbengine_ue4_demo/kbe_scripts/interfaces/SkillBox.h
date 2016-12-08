// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

class Entity;

/*
	对应entity_defs/interfaces/*
*/
class SkillBox
{
public:
	SkillBox() {}
	SkillBox(Entity* entity);
	virtual ~SkillBox();

public:
	Entity* self;

	// def中定义的客户端涉及属性
};

/*
Declare all of the properties and methods of the KBE-Entity

Example:
	#define ENTITYDEF_DECLARE_[module name of Entity](PARENT_MODULE)	\
		ENTITYDEF_PROPERTY_*(PARENT_MODULE, xx_property)	\
		ENTITYDEF_METHOD_ARGS[0~20]_REGISTER(PARENT_MODULE, xx_method)
*/
#define ENTITYDEF_DECLARE_SkillBox(PARENT_MODULE)