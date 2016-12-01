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

/*
	对应entity_defs/*
*/
class Avatar : public GameObject, public Combat, public Motion, public State, public Flags, public Spell, public SkillBox
{
public:
	Avatar();
	virtual ~Avatar();

public:
	// def中定义的客户端涉及属性
	uint16 level;
	uint16 own_val;
};
