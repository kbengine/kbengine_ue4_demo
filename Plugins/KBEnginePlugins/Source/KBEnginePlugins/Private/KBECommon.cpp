// Fill out your copyright notice in the Description page of Project Settings.

#include "KBEnginePluginsPrivatePCH.h"
#include "KBECommon.h"

DEFINE_LOG_CATEGORY(LogKBEngine);


float getTimeSeconds()
{
	return FPlatformTime::Seconds();
}


// Sets default values
AKBECommon::AKBECommon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

