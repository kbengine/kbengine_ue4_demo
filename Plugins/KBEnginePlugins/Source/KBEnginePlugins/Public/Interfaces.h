// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "KBECommon.h"

/*
接口模块
用于声明和实现某些回调统一接口
*/
class KBENGINEPLUGINS_API InterfaceLogin
{
public:

	virtual void onLoginCallback(FString ip, uint16 port, bool success, int userdata) = 0;

};

class KBENGINEPLUGINS_API InterfaceXX
{
public:

	virtual void onXX(FString ip, uint16 port, bool success, int userdata) = 0;

};