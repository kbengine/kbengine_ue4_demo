// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

class Entity;

/*
	对应entity_defs/interfaces/*
*/
class Motion
{
public:
	Motion() {}
	Motion(Entity* entity);
	virtual ~Motion();

	void set_moveSpeed(uint8 old);

public:
	Entity* self;

	// def中定义的客户端涉及属性和方法都需要包含在ENTITYDEF_BEGIN和ENTITYDEF_END之间
	ENTITYDEF_BEGIN()
	uint8 moveSpeed;
	ENTITYDEF_END()
};
