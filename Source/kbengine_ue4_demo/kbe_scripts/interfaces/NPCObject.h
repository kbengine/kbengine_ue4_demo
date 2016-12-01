// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

class Entity;

/*
	对应entity_defs/interfaces/*
*/
class NPCObject
{
public:
	NPCObject() {}
	NPCObject(Entity* entity);
	virtual ~NPCObject();

	void set_entityNO(int32 old);

public:
	Entity* self;

	// def中定义的客户端涉及属性
	uint32 entityNO;
};
