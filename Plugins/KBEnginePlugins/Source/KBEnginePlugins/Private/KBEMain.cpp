// Fill out your copyright notice in the Description page of Project Settings.

#include "KBEnginePluginsPrivatePCH.h"
#include "KBEMain.h"
#include "KBEngine.h"
#include "KBEngineArgs.h"
#include "MemoryStream.h"
#include "Bundle.h"

// Sets default values for this component's properties
UKBEMain::UKBEMain(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;

	// ...

	ip = TEXT("127.0.0.1");
	port = 20013;
	syncPlayer = true;
	useAliasEntityID = true;
	isOnInitCallPropertysSetMethods = true;
	clientType = EKCLIENT_TYPE::CLIENT_TYPE_WIN;
	SEND_BUFFER_MAX = TCP_PACKET_MAX;
	RECV_BUFFER_MAX = TCP_PACKET_MAX;
	persistentDataPath = TEXT("");
}

void UKBEMain::InitializeComponent()
{
	Super::InitializeComponent();
}

void UKBEMain::UninitializeComponent()
{
	Super::UninitializeComponent();
}

// Called when the game starts
void UKBEMain::BeginPlay()
{
	Super::BeginPlay();

	KBEngineArgs* pArgs = new KBEngineArgs();
	pArgs->ip = ip;
	pArgs->port = port;
	pArgs->syncPlayer = syncPlayer;
	pArgs->useAliasEntityID = useAliasEntityID;
	pArgs->isOnInitCallPropertysSetMethods = isOnInitCallPropertysSetMethods;
	pArgs->clientType = clientType;
	pArgs->SEND_BUFFER_MAX = SEND_BUFFER_MAX;
	pArgs->RECV_BUFFER_MAX = RECV_BUFFER_MAX;
	pArgs->persistentDataPath = persistentDataPath;
	KBEngineApp::getSingleton().initialize(pArgs);
}

void UKBEMain::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void UKBEMain::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );


	KBEngineApp::getSingleton().process();
}

bool UKBEMain::destroyKBEngine()
{
	if (!KBEngineApp::getSingleton().isInitialized())
		return false;

	KBEngineApp::getSingleton().destroy();
	return true;
}

bool UKBEMain::login(FString& username, FString& password, TArray<uint8>& datas)
{
	if (!KBEngineApp::getSingleton().isInitialized())
		return false;

	return KBEngineApp::getSingleton().login(username, password, datas);
}
