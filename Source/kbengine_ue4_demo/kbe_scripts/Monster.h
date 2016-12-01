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
	∂‘”¶entity_defs/*
*/
class Monster : public GameObject, public NPCObject, public Combat, public Motion, public State, public Flags, public Spell
{
public:
	Monster();
	virtual ~Monster();

public:
};
