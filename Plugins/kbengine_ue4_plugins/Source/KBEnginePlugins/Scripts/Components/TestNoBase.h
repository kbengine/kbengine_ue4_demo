// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "Engine/KBECommon.h"
#include "Engine/TestNoBaseBase.h"

namespace KBEngine
{

class TestNoBase : public TestNoBaseBase
{
public:
	TestNoBase();
	virtual ~TestNoBase();


	virtual void onAttached(Entity* pOwnerEntity) override;
	virtual void onDetached(Entity* pOwnerEntity) override;

public:
	virtual void onOwnChanged(int32 oldValue) override;
	virtual void onStateChanged(int32 oldValue) override;
	virtual void helloCB(int32 arg1) override;
};


}