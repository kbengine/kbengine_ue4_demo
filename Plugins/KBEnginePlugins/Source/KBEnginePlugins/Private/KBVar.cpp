
#include "KBEnginePluginsPrivatePCH.h"
#include "KBVar.h"


void KBVar::ErrorLog(const FString& errstr) const
{
	SET_WARN_COLOR(COLOR_RED); 
	const FString NewMsg = FString::Printf(TEXT("**ERROR** %s%s() : %s"), NETMODE_WORLD, FUNC_NAME, *errstr);
	UE_LOG(LogKBEngine, Log, TEXT("%s"), *NewMsg); 
	CLEAR_WARN_COLOR(); 
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, NewMsg); 
}

