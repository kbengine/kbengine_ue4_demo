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
