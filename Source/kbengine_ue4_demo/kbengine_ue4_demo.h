// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#ifndef __KBENGINE_UE4_DEMO_H__
#define __KBENGINE_UE4_DEMO_H__

#include "EngineMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(KBEScriptLog, Log, All);

#define INFO_MSG(Format, ...) \
{ \
	SET_WARN_COLOR(COLOR_CYAN); \
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	UE_LOG(KBEScriptLog, Log, TEXT("%s"),  *Msg); \
	CLEAR_WARN_COLOR(); \
}

#define DEBUG_MSG(Format, ...) \
{ \
	SET_WARN_COLOR(COLOR_CYAN); \
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	UE_LOG(KBEScriptLog, Log, TEXT("**DEBUG** %s"), *Msg); \
	CLEAR_WARN_COLOR(); \
}

#define WARNING_MSG(Format, ...) \
{ \
	SET_WARN_COLOR(COLOR_YELLOW); \
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	UE_LOG(KBEScriptLog, Log, TEXT("**WARNING** %s"), *Msg); \
	CLEAR_WARN_COLOR(); \
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, Msg); \
}

#define ERROR_MSG(Format, ...) \
{ \
	SET_WARN_COLOR(COLOR_RED); \
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	UE_LOG(KBEScriptLog, Log, TEXT("**ERROR** %s"), *Msg); \
	CLEAR_WARN_COLOR(); \
	GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, Msg); \
}

#define SCREENDEBUG(Format, ...) \
{ \
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	GEngine->AddOnScreenDebugMessage(-1, 10000.f, FColor::White, Msg); \
}

#endif
