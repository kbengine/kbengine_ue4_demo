// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "KBECommon.h"

/*
	事件模块
	KBEngine插件层与Unity3D表现层通过事件来交互
*/
class KBENGINEPLUGINS_API Event
{
public:
	Event();
	virtual ~Event();

public:
		/*
			注册监听由kbe插件抛出的事件。(out = kbe->render)
			通常由渲染表现层来注册, 例如：监听角色血量属性的变化， 如果UI层注册这个事件，
			事件触发后就可以根据事件所附带的当前血量值来改变角色头顶的血条值。
		*/
		static bool registerOut(FString eventname, FString funcname)
		{
			return _register(eventname, funcname);
		}

		/*
			注册监听由渲染表现层抛出的事件(in = render->kbe)
			通常由kbe插件层来注册， 例如：UI层点击登录， 此时需要触发一个事件给kbe插件层进行与服务端交互的处理。
		*/
		static bool registerIn(FString eventname, FString funcname)
		{
			return _register(eventname, funcname);
		}

		static bool _register(FString eventname, FString funcname);
		
protected:
};
