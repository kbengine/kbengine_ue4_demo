// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "Engine/KBECommon.h"

#include "Engine/NPCBase.h"

namespace KBEngine
{

class NPC : public NPCBase
{
public:
	NPC();
	virtual ~NPC();

public:
	virtual void onEntityNOChanged(uint32 oldValue) override;
	virtual void onModelIDChanged(uint32 oldValue) override;
	virtual void onModelScaleChanged(uint8 oldValue) override;
	virtual void onMoveSpeedChanged(uint8 oldValue) override;
	virtual void onNameChanged(const FString& oldValue) override;
	virtual void onUidChanged(uint32 oldValue) override;
	virtual void onUtypeChanged(uint32 oldValue) override;

};

}

