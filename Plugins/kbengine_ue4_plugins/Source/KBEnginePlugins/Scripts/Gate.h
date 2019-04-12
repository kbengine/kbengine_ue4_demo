// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "Engine/KBECommon.h"

#include "Engine/GateBase.h"

namespace KBEngine
{

class Gate : public GateBase
{
public:
	Gate();
	virtual ~Gate();

public:
	void onModelIDChanged(uint32 oldValue) override;
	void onModelScaleChanged(uint8 oldValue) override;
	void onNameChanged(const FString& oldValue) override;
	void onEntityNOChanged(uint32 oldValue) override;
};

}