// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

class Entity;

/*
	对应entity_defs/interfaces/*
*/
class State
{
public:
	State() {}
	State(Entity* entity);
	virtual ~State();

	void set_state(int8 old);
	void set_subState(uint8 old);
	void set_forbids(int32 old);

public:
	Entity* self;

	// def中定义的客户端涉及属性
	int8 state;
	uint8 subState;
	int32 forbids;
};

/*
Declare all of the properties and methods of the KBE-Entity

Example:
	#define ENTITYDEF_DECLARE_[module name of Entity](PARENT_MODULE)	\
		ENTITYDEF_PROPERTY_*(PARENT_MODULE, xx_property)	\
		ENTITYDEF_METHOD_ARGS[0~20]_REGISTER(PARENT_MODULE, xx_method)
*/

#define ENTITYDEF_DECLARE_State(PARENT_MODULE)	\
	ENTITYDEF_PROPERTY_WITH_SETMETHOD_REGISTER(PARENT_MODULE, state)	\
	ENTITYDEF_PROPERTY_WITH_SETMETHOD_REGISTER(PARENT_MODULE, subState)	\
	ENTITYDEF_PROPERTY_WITH_SETMETHOD_REGISTER(PARENT_MODULE, forbids)
