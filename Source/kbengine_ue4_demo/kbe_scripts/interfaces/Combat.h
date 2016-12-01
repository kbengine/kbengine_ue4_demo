// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

class Entity;

/*
	对应entity_defs/interfaces/*
*/
class Combat
{
public:
	Combat() {}
	Combat(Entity* entity);
	virtual ~Combat();

	void set_HP(int32 old);
	void set_HP_Max(int32 old);
	void set_MP(int32 old);
	void set_MP_Max(int32 old);

public:
	Entity* self;

	// def中定义的客户端涉及属性
	int32 HP;
	int32 HP_Max;
	int32 MP;
	int32 MP_Max;
};
