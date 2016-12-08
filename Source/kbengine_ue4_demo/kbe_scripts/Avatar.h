// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "KBECommon.h"

class GameObject;
class Combat;
class Motion;
class State;
class Flags;
class Spell;
class SkillBox;
class Teleport;

/*
	对应entity_defs/*
*/
class Avatar : public GameObject, public Combat, public Motion, public State, public Flags, public Spell, public SkillBox, public Teleport
{
public:
	Avatar();
	virtual ~Avatar();

	virtual void __init__() override;

public:
	virtual void onDestroy() override;
	virtual void onEnterWorld() override;
	virtual void onLeaveWorld() override;
	virtual void onEnterSpace() override;
	virtual void onLeaveSpace() override;

	void reqRelive(uint8 reliveType);

public:
	// def中定义的客户端涉及属性
	uint16 level;
	uint16 own_val;
};


/*
Declare all of the properties and methods of the KBE-Entity

Example:
	#define ENTITYDEF_DECLARE_[module name of Entity](PARENT_MODULE)	\
		ENTITYDEF_PROPERTY_*(PARENT_MODULE, xx_property)	\
		ENTITYDEF_METHOD_ARGS[0~20]_REGISTER(PARENT_MODULE, xx_method)
*/

#define ENTITYDEF_DECLARE_Avatar(PARENT_MODULE)	\
	ENTITYDEF_PROPERTY_REGISTER(PARENT_MODULE, level)	\
	ENTITYDEF_PROPERTY_REGISTER(PARENT_MODULE, own_val)
