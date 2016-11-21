
#include "KBEnginePluginsPrivatePCH.h"
#include "NetworkInterface.h"
#include "PacketReceiver.h"
#include "PacketSender.h"
#include "MemoryStream.h"
#include "Event.h"

NetworkInterface::NetworkInterface():
	socket_(NULL),
	pPacketSender_(NULL),
	pPacketReceiver_(NULL),
	connectCB_(NULL),
	connectIP_(TEXT("")),
	connectPort_(0),
	connectUserdata_(0),
	startTime_(0.0),
	isDestroyed_(false)
{
}

NetworkInterface::~NetworkInterface()
{
	close();
}

void NetworkInterface::reset()
{
	close();
}

void NetworkInterface::close()
{
	if (socket_)
	{
		socket_->Close();
		INFO_MSG("network closed!");
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(socket_);
		KBENGINE_EVENT_FIRE("onDisableConnect", FKEventData_onDisableConnect());
	}

	socket_ = NULL;

	SAFE_RELEASE(pPacketSender_);
	SAFE_RELEASE(pPacketReceiver_);

	connectCB_ = NULL;
	connectIP_ = TEXT("");
	connectPort_ = 0;
	connectUserdata_ = 0;
	startTime_ = 0.0;
}

bool NetworkInterface::valid()
{
	return socket_ != NULL;
}

bool NetworkInterface::connectTo(FString ip, uint16 port, InterfaceLogin* callback, int userdata)
{
	INFO_MSG("will connect to %s:%d ...", *ip, port);

	reset();

	FIPv4Address ip1;
	FIPv4Address::Parse(ip, ip1);

	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(ip1.Value);
	addr->SetPort(port);

	socket_ = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);

	if (!valid())
	{
		ERROR_MSG("socket could't be created!");
		return false;
	}
	
	if (!socket_->SetNonBlocking(true))
	{
		ERROR_MSG("socket->SetNonBlocking error(%d)!", *ip, port,
			(int32)ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetLastErrorCode());
	}

	bool didConnect = socket_->Connect(*addr);

	if (didConnect)
	{
		connectCB_ = callback;
		connectIP_ = ip;
		connectPort_ = port;
		connectUserdata_ = userdata;
		startTime_ = getTimeSeconds();
	}
	else
	{
		ERROR_MSG("connect %s:%d error(%d)!", *ip, port,
			(int32)ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetLastErrorCode());

		callback->onLoginCallback(ip, port, false, userdata);
	}

	return didConnect;
}

bool NetworkInterface::send(MemoryStream* pMemoryStream)
{
	if (!valid())
	{
		return false;
	}

	if (!pPacketSender_)
		pPacketSender_ = new PacketSender(this);

	return pPacketSender_->send(pMemoryStream);
}

void NetworkInterface::process()
{
	if (!valid())
		return;

	if (connectCB_)
	{
		tickConnecting();
		return;
	}

	if (!pPacketReceiver_)
		pPacketReceiver_ = new PacketReceiver(this);

	pPacketReceiver_->process();

	if (isDestroyed_)
	{
		delete this;
		return;
	}
}

void NetworkInterface::tickConnecting()
{
	ESocketConnectionState state = socket_->GetConnectionState();

	if (state == SCS_Connected)
	{
		TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
		socket_->GetPeerAddress(*addr);

		INFO_MSG("connect to %s success!", *addr->ToString(true));
		connectCB_->onLoginCallback(connectIP_, connectPort_, true, connectUserdata_);
		connectCB_ = NULL;

		KBENGINE_EVENT_FIRE("onConnectStatus", FKEventData_onConnectStatus(true));
	}
	else
	{
		// 如果连接超时则回调失败
		float currTime = getTimeSeconds();
		if (currTime - startTime_ > 3)
		{
			ERROR_MSG("connect to %s:%d timeout!", *connectIP_, connectPort_);
			connectCB_->onLoginCallback(connectIP_, connectPort_, false, connectUserdata_);
			connectCB_ = NULL;
			KBENGINE_EVENT_FIRE("onConnectStatus", FKEventData_onConnectStatus(false));
		}
	}
}