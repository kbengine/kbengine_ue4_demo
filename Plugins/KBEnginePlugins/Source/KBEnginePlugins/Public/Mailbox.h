// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "KBECommon.h"

/*
	实体的Mailbox
	关于Mailbox请参考API手册中对它的描述
	https://github.com/kbengine/kbengine/tree/master/docs/api
*/
class KBENGINEPLUGINS_API Mailbox
{
public:
	Mailbox();
	virtual ~Mailbox();

	enum MAILBOX_TYPE
	{
		MAILBOX_TYPE_CELL = 0,		// CELL_MAILBOX
		MAILBOX_TYPE_BASE = 1		// BASE_MAILBOX
	};

public:
	bool isBase()
	{
		return type == MAILBOX_TYPE_BASE;
	}

	bool isCell()
	{
		return type == MAILBOX_TYPE_CELL;
	}

public:
	ENTITY_ID id;
	FString className;
	MAILBOX_TYPE type;
};
