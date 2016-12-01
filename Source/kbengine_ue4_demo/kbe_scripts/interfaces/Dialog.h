// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

class Entity;

/*
	对应entity_defs/interfaces/*
*/
class Dialog
{
public:
	Dialog() {}
	Dialog(Entity* entity);
	virtual ~Dialog();

public:
	Entity* self;

	// def中定义的客户端涉及属性
};
