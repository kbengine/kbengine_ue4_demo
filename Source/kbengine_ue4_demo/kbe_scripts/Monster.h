// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "KBECommon.h"

class GameObject;
class NPCObject;
class Combat;
class Motion;
class State;
class Flags;
class Spell;

/*
	对应entity_defs/*
*/
class Monster : public GameObject, public NPCObject, public Combat, public Motion, public State, public Flags, public Spell
{
public:
	Monster();
	virtual ~Monster();

public:
	// def中定义的客户端涉及属性和方法都需要包含在ENTITYDEF_BEGIN和ENTITYDEF_END之间
	ENTITYDEF_BEGIN()
	ENTITYDEF_END()
};
