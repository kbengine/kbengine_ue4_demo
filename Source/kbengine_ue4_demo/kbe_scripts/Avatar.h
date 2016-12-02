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

public:
	virtual void onDestroy() override;
	virtual void onEnterWorld() override;
	virtual void onLeaveWorld() override;
	virtual void onEnterSpace() override;
	virtual void onLeaveSpace() override;

public:
	// def中定义的客户端涉及属性和方法都需要包含在ENTITYDEF_BEGIN和ENTITYDEF_END之间
	ENTITYDEF_BEGIN()
	uint16 level;
	uint16 own_val;
	ENTITYDEF_END()
};
