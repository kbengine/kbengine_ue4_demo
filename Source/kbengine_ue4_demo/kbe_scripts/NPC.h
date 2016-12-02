// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "KBECommon.h"

class GameObject;
class NPCObject;
class Motion;

/*
	∂‘”¶entity_defs/*
*/
class NPC : public GameObject, public NPCObject, public Motion
{
public:
	NPC();
	virtual ~NPC();

public:
};
