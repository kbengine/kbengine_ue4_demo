// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#include "Engine.h"
#include "KBEnginePlugins.h"

// You should place include statements to your module's private header files here.  You only need to
// add includes for headers that are used in most of your module's source files though.

#define NETMODE_WORLD TEXT("")

#define FUNC_NAME TEXT(__func__)

#if PLATFORM_WINDOWS
#define FUNC_NAME TEXT(__FUNCTION__)
#endif

#if PLATFORM_ANDROID
#define  FUNC_NAME __func__
#endif

#define INFO_MSG(Format, ...) \
{ \
	SET_WARN_COLOR(COLOR_CYAN); \
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	if (Msg == "") \
	{ \
		UE_LOG(LogKBEngine, Log, TEXT("%s%s()"), NETMODE_WORLD, FUNC_NAME); \
	} \
		else \
	{ \
		UE_LOG(LogKBEngine, Log, TEXT("%s%s() : %s"), NETMODE_WORLD, FUNC_NAME, *Msg); \
	} \
	CLEAR_WARN_COLOR(); \
}

#define DEBUG_MSG(Format, ...) \
{ \
	SET_WARN_COLOR(COLOR_CYAN); \
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	UE_LOG(LogKBEngine, Log, TEXT("**DEBUG** %s() : %s"), FUNC_NAME, *Msg); \
	CLEAR_WARN_COLOR(); \
}

#define WARNING_MSG(Format, ...) \
{ \
	SET_WARN_COLOR(COLOR_YELLOW); \
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	UE_LOG(LogKBEngine, Log, TEXT("**WARNING** %s%s() : %s"), NETMODE_WORLD, FUNC_NAME, *Msg); \
	CLEAR_WARN_COLOR(); \
}

#define SCREEN_WARNING_MSG(Format, ...) \
{ \
	SET_WARN_COLOR(COLOR_YELLOW); \
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	UE_LOG(LogKBEngine, Log, TEXT("**WARNING** %s%s() : %s"), NETMODE_WORLD, FUNC_NAME, *Msg); \
	CLEAR_WARN_COLOR(); \
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, Msg); \
}

#define ERROR_MSG(Format, ...) \
{ \
	SET_WARN_COLOR(COLOR_RED); \
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	UE_LOG(LogKBEngine, Log, TEXT("**ERROR** %s%s() : %s"), NETMODE_WORLD, FUNC_NAME, *Msg); \
	CLEAR_WARN_COLOR(); \
}

#define SCREEN_ERROR_MSG(Format, ...) \
{ \
	SET_WARN_COLOR(COLOR_RED); \
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	UE_LOG(LogKBEngine, Log, TEXT("**ERROR** %s%s() : %s"), NETMODE_WORLD, FUNC_NAME, *Msg); \
	CLEAR_WARN_COLOR(); \
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, Msg); \
}

#define SCREENDEBUG(Format, ...) \
{ \
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	if (Msg == "") \
	{ \
		TCHAR StdMsg[MAX_SPRINTF] = TEXT(""); \
		FCString::Sprintf(StdMsg, TEXT("%s%s()"), NETMODE_WORLD, FUNC_NAME); \
		GEngine->AddOnScreenDebugMessage(-1, 10000.f, FColor::White, StdMsg); \
	} \
	else \
	{ \
		GEngine->AddOnScreenDebugMessage(-1, 10000.f, FColor::White, Msg); \
	} \
}