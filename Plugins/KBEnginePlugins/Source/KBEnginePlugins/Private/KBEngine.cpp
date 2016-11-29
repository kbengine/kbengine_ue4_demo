
#include "KBEnginePluginsPrivatePCH.h"
#include "KBEngine.h"
#include "KBEngineArgs.h"
#include "Entity.h"
#include "NetworkInterface.h"
#include "Bundle.h"
#include "MemoryStream.h"
#include "PersistentInfos.h"
#include "DataTypes.h"
#include "ScriptModule.h"
#include "Property.h"
#include "Method.h"
#include "Mailbox.h"
#include "Regex.h"

TMap<uint16, FKServerErr> KBEngineApp::serverErrs_;

bool KBEngineApp::loadingLocalMessages_ = false;


bool KBEngineApp::loginappMessageImported_ = false;
bool KBEngineApp::baseappMessageImported_ = false;
bool KBEngineApp::entitydefImported_ = false;
bool KBEngineApp::isImportServerErrorsDescr_ = false;

KBEngineApp::KBEngineApp() :
	pArgs_(NULL),
	pNetworkInterface_(NULL),
	username_(TEXT("")),
	password_(TEXT("")),
	baseappIP_(TEXT("")),
	baseappPort_(0),
	currserver_(TEXT("")),
	currstate_(TEXT("")),
	serverdatas_(),
	clientdatas_(),
	encryptedKey_(),
	serverVersion_(TEXT("")),
	clientVersion_(TEXT("")),
	serverScriptVersion_(TEXT("")),
	clientScriptVersion_(TEXT("")),
	serverProtocolMD5_(TEXT("")),
	serverEntitydefMD5_(TEXT("")),
	persistentInfos_(NULL),
	entity_uuid_(0),
	entity_id_(0),
	entity_type_(TEXT("")),
	entityServerPos_(),
	spacedatas_(),
	entities_(),
	entityIDAliasIDList_(),
	bufferedCreateEntityMessage_(),
	lastTickTime_(0.0),
	lastTickCBTime_(0.0),
	lastUpdateToServerTime_(0.0),
	spaceID_(0),
	spaceResPath_(TEXT("")),
	isLoadedGeometry_(false),
	component_(TEXT("client"))
{
	INFO_MSG("hello!");
}

KBEngineApp::KBEngineApp(KBEngineArgs* pArgs):
	pArgs_(NULL),
	pNetworkInterface_(NULL),
	username_(TEXT("")),
	password_(TEXT("")),
	baseappIP_(TEXT("")),
	baseappPort_(0),
	currserver_(TEXT("")),
	currstate_(TEXT("")),
	serverdatas_(),
	clientdatas_(),
	encryptedKey_(),
	serverVersion_(TEXT("")),
	clientVersion_(TEXT("")),
	serverScriptVersion_(TEXT("")),
	clientScriptVersion_(TEXT("")),
	serverProtocolMD5_(TEXT("")),
	serverEntitydefMD5_(TEXT("")),
	persistentInfos_(NULL),
	entity_uuid_(0),
	entity_id_(0),
	entity_type_(TEXT("")),
	entityServerPos_(),
	spacedatas_(),
	entities_(),
	entityIDAliasIDList_(),
	bufferedCreateEntityMessage_(),
	lastTickTime_(0.0),
	lastTickCBTime_(0.0),
	lastUpdateToServerTime_(0.0),
	spaceID_(0),
	spaceResPath_(TEXT("")),
	isLoadedGeometry_(false),
	component_(TEXT("client"))
{
	INFO_MSG("hello!");
	initialize(pArgs);
}

KBEngineApp::~KBEngineApp()
{
	destroy();
	INFO_MSG("destructed!");
}

KBEngineApp& KBEngineApp::getSingleton() 
{
	static KBEngineApp* pKBEngineApp = NULL;

	if (!pKBEngineApp)
		pKBEngineApp = new KBEngineApp();

	return *pKBEngineApp;
}

bool KBEngineApp::initialize(KBEngineArgs* pArgs)
{
	if (isInitialized())
		return false;

	EntityDef::initialize();

	// 允许持久化KBE(例如:协议，entitydef等)
	if (pArgs->persistentDataPath != TEXT(""))
	{
		SAFE_RELEASE(persistentInfos_);
		persistentInfos_ = new PersistentInfos(pArgs->persistentDataPath);
	}

	// 注册事件
	installEvents();

	pArgs_ = pArgs;
	reset();
	return true;
}

void KBEngineApp::installEvents()
{
	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("login", "login", [this](const UKBEventData* pEventData)
	{
		const UKBEventData_login& data = static_cast<const UKBEventData_login&>(*pEventData);
		login(data.username, data.password, data.datas);
	});

	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("createAccount", "createAccount", [this](const UKBEventData* pEventData)
	{
		const UKBEventData_createAccount& data = static_cast<const UKBEventData_createAccount&>(*pEventData);
		createAccount(data.username, data.password, data.datas);
	});

	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("reLoginBaseapp", "reLoginBaseapp", [this](const UKBEventData* pEventData)
	{
		reLoginBaseapp();
	});

	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("resetPassword", "resetPassword", [this](const UKBEventData* pEventData)
	{
		const UKBEventData_resetPassword& data = static_cast<const UKBEventData_resetPassword&>(*pEventData);
		resetPassword(data.username);
	});

	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("bindAccountEmail", "bindAccountEmail", [this](const UKBEventData* pEventData)
	{
		const UKBEventData_bindAccountEmail& data = static_cast<const UKBEventData_bindAccountEmail&>(*pEventData);
		bindAccountEmail(data.email);
	});

	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("newPassword", "newPassword", [this](const UKBEventData* pEventData)
	{
		const UKBEventData_newPassword& data = static_cast<const UKBEventData_newPassword&>(*pEventData);
		newPassword(data.old_password, data.new_password);
	});

	// 内部事件
	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("_closeNetwork", "_closeNetwork", [this](const UKBEventData* pEventData)
	{
		_closeNetwork();
	});
}

void KBEngineApp::destroy()
{
	reset();
	KBENGINE_DEREGISTER_ALL_EVENT();
	resetMessages();

	SAFE_RELEASE(pArgs_);
	SAFE_RELEASE(pNetworkInterface_);
	SAFE_RELEASE(persistentInfos_);
}

void KBEngineApp::resetMessages()
{
	loadingLocalMessages_ = false;
	loginappMessageImported_ = false;
	baseappMessageImported_ = false;
	entitydefImported_ = false;
	isImportServerErrorsDescr_ = false;

	serverErrs_.Empty();

	Messages::getSingleton().clear();
	EntityDef::clear();
	Entity::clear();

	INFO_MSG("done!");
}

void KBEngineApp::reset()
{
	KBEvent::clearFiredEvents();

	clearEntities(true);

	currserver_ = TEXT("");
	currstate_ = TEXT("");

	serverdatas_.Empty();

	serverVersion_ = TEXT("");
	clientVersion_ = TEXT("0.9.0");
	serverScriptVersion_ = TEXT("");
	clientScriptVersion_ = TEXT("0.1.0");

	entity_uuid_ = 0;
	entity_id_ = 0;
	entity_type_ = TEXT("");

	entityIDAliasIDList_.Empty();
	bufferedCreateEntityMessage_.Empty();

	lastTickTime_ = getTimeSeconds();
	lastTickCBTime_ = getTimeSeconds();
	lastUpdateToServerTime_ = getTimeSeconds();

	spacedatas_.Empty();

	spaceID_ = 0;
	spaceResPath_ = TEXT("");
	isLoadedGeometry_ = false;
	
	initNetwork();
}

bool KBEngineApp::initNetwork()
{
	if (pNetworkInterface_)
		delete pNetworkInterface_;

	pNetworkInterface_ = new NetworkInterface();
	return true;
}

void KBEngineApp::_closeNetwork()
{
	if (pNetworkInterface_)
		pNetworkInterface_->close();
}

bool KBEngineApp::validEmail(const FString& strEmail)
{
	const FRegexPattern spattern(FString(TEXT("[a-z0-9._%+-]+@[a-z0-9.-]+\\.[a-z]{2,4}")));

	FRegexMatcher fMatcher(spattern, strEmail);

	if (fMatcher.FindNext()) {
		return true;
	}

	return false;
}

void KBEngineApp::process()
{
	// 处理网络
	if (pNetworkInterface_)
		pNetworkInterface_->process();

	// 处理外层抛入的事件
	KBEvent::processInEvents();

	// 向服务端发送心跳以及同步角色信息到服务端
	sendTick();
}

void KBEngineApp::sendTick()
{
	if (!pNetworkInterface_ || !pNetworkInterface_->valid())
		return;

	if (!loginappMessageImported_ && !baseappMessageImported_)
		return;

	double span = getTimeSeconds() - lastTickTime_;

	// 更新玩家的位置与朝向到服务端
	updatePlayerToServer();

	if (span > 15)
	{
		span = lastTickCBTime_ - lastTickTime_;

		// 如果心跳回调接收时间小于心跳发送时间，说明没有收到回调
		// 此时应该通知客户端掉线了
		if (span < 0)
		{
			SCREEN_ERROR_MSG("Receive appTick timeout!");
			pNetworkInterface_->close();
			return;
		}

		Message** Loginapp_onClientActiveTickMsgFind = Messages::getSingleton().messages.Find("Loginapp_onClientActiveTick");
		Message** Baseapp_onClientActiveTickMsgFind = Messages::getSingleton().messages.Find("Baseapp_onClientActiveTick");

		if (currserver_ == TEXT("loginapp"))
		{
			if (Loginapp_onClientActiveTickMsgFind)
			{
				Bundle* pBundle = Bundle::createObject();
				pBundle->newMessage(*Loginapp_onClientActiveTickMsgFind);
				pBundle->send(pNetworkInterface_);
			}
		}
		else
		{
			if (Baseapp_onClientActiveTickMsgFind)
			{
				Bundle* pBundle = Bundle::createObject();
				pBundle->newMessage(*Baseapp_onClientActiveTickMsgFind);
				pBundle->send(pNetworkInterface_);
			}
		}

		lastTickTime_ = getTimeSeconds();
	}
}

Entity* KBEngineApp::player()
{
	return findEntity(entity_id_);
}

Entity* KBEngineApp::findEntity(int32 entityID)
{
	Entity** pEntity = entities_.Find(entityID);
	if (pEntity == nullptr)
		return NULL;

	return *pEntity;
}

FString KBEngineApp::serverErr(uint16 id)
{
	FKServerErr e = serverErrs_.FindRef(id);
	return FString::Printf(TEXT("%s[%s]"), *e.name, *e.descr);
}

void KBEngineApp::updatePlayerToServer()
{
	if (!pArgs_->syncPlayer || spaceID_ == 0)
		return;

	float tnow = getTimeSeconds();
	double span = tnow - lastUpdateToServerTime_;

	if (span < 0.1)
		return;


}

void KBEngineApp::Client_onAppActiveTickCB()
{
	lastTickCBTime_ = getTimeSeconds();
}

void KBEngineApp::hello()
{
	Bundle* pBundle = Bundle::createObject();
	if (currserver_ == "loginapp")
		pBundle->newMessage(Messages::getSingleton().messages["Loginapp_hello"]);
	else
		pBundle->newMessage(Messages::getSingleton().messages["Baseapp_hello"]);

	(*pBundle) << clientVersion_;
	(*pBundle) << clientScriptVersion_;
	pBundle->appendBlob(encryptedKey_);
	pBundle->send(pNetworkInterface_);
}

void KBEngineApp::Client_onHelloCB(MemoryStream& stream)
{
	stream >> serverVersion_;
	stream >> serverScriptVersion_;
	stream >> serverProtocolMD5_;
	stream >> serverEntitydefMD5_;

	int32 ctype;
	stream >> ctype;

	INFO_MSG("verInfo(%s), scriptVersion(%s), srvProtocolMD5(%s), srvEntitydefMD5(%s), ctype(%d)!", 
		*serverVersion_, *serverScriptVersion_, *serverProtocolMD5_, *serverEntitydefMD5_, ctype);

	onServerDigest();

	if (currserver_ == "baseapp")
	{
		onLogin_baseapp();
	}
	else
	{
		onLogin_loginapp();
	}
}

void KBEngineApp::Client_onVersionNotMatch(MemoryStream& stream)
{
	stream >> serverVersion_;

	ERROR_MSG("verInfo=%s(server: %s)", *clientVersion_, *serverVersion_);

	UKBEventData_onVersionNotMatch* pEventData = NewObject<UKBEventData_onVersionNotMatch>();
	pEventData->clientVersion = clientVersion_;
	pEventData->serverVersion = serverVersion_;
	KBENGINE_EVENT_FIRE("onVersionNotMatch", pEventData);

	if (persistentInfos_)
		persistentInfos_->onVersionNotMatch(clientVersion_, serverVersion_);
}

void KBEngineApp::Client_onScriptVersionNotMatch(MemoryStream& stream)
{
	stream >> serverScriptVersion_;

	ERROR_MSG("verInfo=%s(server: %s)", *clientScriptVersion_, *serverScriptVersion_);

	UKBEventData_onScriptVersionNotMatch* pEventData = NewObject<UKBEventData_onScriptVersionNotMatch>();
	pEventData->clientScriptVersion = clientScriptVersion_;
	pEventData->serverScriptVersion = serverScriptVersion_;
	KBENGINE_EVENT_FIRE("onScriptVersionNotMatch", pEventData);

	if (persistentInfos_)
		persistentInfos_->onScriptVersionNotMatch(clientScriptVersion_, serverScriptVersion_);
}

void KBEngineApp::Client_onKicked(uint16 failedcode)
{
	DEBUG_MSG("failedcode=%d, %s", failedcode, *serverErr(failedcode));

	UKBEventData_onKicked* pEventData = NewObject<UKBEventData_onKicked>();
	pEventData->failedcode = failedcode;
	pEventData->errorStr = serverErr(failedcode);
	KBENGINE_EVENT_FIRE("onKicked", pEventData);
}

void KBEngineApp::Client_onImportServerErrorsDescr(MemoryStream& stream)
{
	TArray<uint8> datas;
	datas.SetNumUninitialized(stream.length());
	memcpy(datas.GetData(), stream.data() + stream.rpos(), stream.length());

	onImportServerErrorsDescr(stream);

	if (persistentInfos_)
		persistentInfos_->onImportServerErrorsDescr(datas);
}

void KBEngineApp::onImportServerErrorsDescr(MemoryStream& stream)
{
	uint16 size = 0;
	stream >> size;

	while (size > 0)
	{
		size -= 1;

		FKServerErr e;
		e.id = stream.read<uint16>();
		stream.readUTF8String(e.name);
		stream.readUTF8String(e.descr);

		serverErrs_.Add(e.id, e);

		DEBUG_MSG("id=%d, name=%s, descr=%s", e.id, *e.name, *e.descr);
	}
}

void KBEngineApp::onServerDigest()
{
	if (persistentInfos_)
		persistentInfos_->onServerDigest(currserver_, serverProtocolMD5_, serverEntitydefMD5_);
}

bool KBEngineApp::login(const FString& username, const FString& password, const TArray<uint8>& datas)
{
	if (username.Len() == 0)
	{
		ERROR_MSG("username is empty!");
		return false;
	}

	if (password.Len() == 0)
	{
		ERROR_MSG("password is empty!");
		return false;
	}

	username_ = username;
	password_ = password;
	clientdatas_ = datas;

	login_loginapp(true);
	return true;
}

void KBEngineApp::onConnectCallback(FString ip, uint16 port, bool success, int userdata)
{
	if (userdata == 0)
	{
		onConnectTo_loginapp_login_callback(ip, port, success);
	}
	else if (userdata == 1)
	{
		onConnectTo_loginapp_create_callback(ip, port, success);
	}
	else
	{
		onConnectTo_baseapp_callback(ip, port, success);
	}
}

void KBEngineApp::login_loginapp(bool noconnect)
{
	if (noconnect)
	{
		reset();
		pNetworkInterface_->connectTo(pArgs_->ip, pArgs_->port, this, 0);
	}
	else
	{
		INFO_MSG("send login! username=%s", *username_);
		Bundle* pBundle = Bundle::createObject();
		pBundle->newMessage(Messages::getSingleton().messages[TEXT("Loginapp_login"]));
		(*pBundle) << (uint8)pArgs_->clientType;
		pBundle->appendBlob(clientdatas_);
		(*pBundle) << username_;
		(*pBundle) << password_;
		pBundle->send(pNetworkInterface_);
	}
}

void KBEngineApp::onConnectTo_loginapp_login_callback(FString ip, uint16 port, bool success)
{
	if (!success)
	{
		ERROR_MSG("connect %s:%d is error!", *ip, port);
		return;
	}

	currserver_ = TEXT("loginapp");
	currstate_ = TEXT("login");

	INFO_MSG("connect %s:%d is success!", *ip, port);

	hello();
}

void KBEngineApp::onLogin_loginapp()
{
	lastTickCBTime_ = getTimeSeconds();

	if (!loginappMessageImported_)
	{
		Bundle* pBundle = Bundle::createObject();
		pBundle->newMessage(Messages::getSingleton().messages[TEXT("Loginapp_importClientMessages"]));
		pBundle->send(pNetworkInterface_);

		DEBUG_MSG("send importClientMessages ...");

		UKBEventData_Loginapp_importClientMessages* pEventData = NewObject<UKBEventData_Loginapp_importClientMessages>();
		KBENGINE_EVENT_FIRE("Loginapp_importClientMessages", pEventData);
	}
	else
	{
		onImportClientMessagesCompleted();
	}
}

void KBEngineApp::Client_onLoginFailed(MemoryStream& stream)
{
	uint16 failedcode = 0;
	stream >> failedcode;
	stream.readBlob(serverdatas_);
	ERROR_MSG("failedcode(%d:%s), datas(%d)!", failedcode, *serverErr(failedcode), serverdatas_.Num());

	UKBEventData_onLoginFailed* pEventData = NewObject<UKBEventData_onLoginFailed>();
	pEventData->failedcode = failedcode;
	pEventData->errorStr = serverErr(failedcode);
	KBENGINE_EVENT_FIRE("onLoginFailed", pEventData);
}

void KBEngineApp::Client_onLoginSuccessfully(MemoryStream& stream)
{
	FString accountName;
	stream >> accountName;
	username_ = accountName;
	stream >> baseappIP_;
	stream >> baseappPort_;

	DEBUG_MSG("accountName(%s), addr("
		 "%s:%d), datas(%d)!", *accountName, *baseappIP_, baseappPort_, serverdatas_.Num());

	stream.readBlob(serverdatas_);
	login_baseapp(true);
}

void KBEngineApp::login_baseapp(bool noconnect)
{
	if (noconnect)
	{
		KBENGINE_EVENT_FIRE("onLoginBaseapp", NewObject<UKBEventData_onLoginBaseapp>());

		pNetworkInterface_->destroy();
		pNetworkInterface_ = NULL;
		initNetwork();
		pNetworkInterface_->connectTo(baseappIP_, baseappPort_, this, 2);
	}
	else
	{
		Bundle* pBundle = Bundle::createObject();
		pBundle->newMessage(Messages::getSingleton().messages[TEXT("Baseapp_loginBaseapp"]));
		(*pBundle) << username_;
		(*pBundle) << password_;
		pBundle->send(pNetworkInterface_);
	}
}

void KBEngineApp::onConnectTo_baseapp_callback(FString ip, uint16 port, bool success)
{
	lastTickCBTime_ = getTimeSeconds();

	if (!success)
	{
		ERROR_MSG("connect %s:%d is error!", *ip, port);
		return;
	}

	currserver_ = TEXT("baseapp");
	currstate_ = TEXT("");

	DEBUG_MSG("connect %s:%d is successfully!", *ip, port);

	hello();
}

void KBEngineApp::onLogin_baseapp()
{
	lastTickCBTime_ = getTimeSeconds();

	if (!baseappMessageImported_)
	{
		Bundle* pBundle = Bundle::createObject();
		pBundle->newMessage(Messages::getSingleton().messages[TEXT("Baseapp_importClientMessages"]));
		pBundle->send(pNetworkInterface_);
		DEBUG_MSG("send importClientMessages ...");
		KBENGINE_EVENT_FIRE("Baseapp_importClientMessages", NewObject<UKBEventData_Baseapp_importClientMessages>());
	}
	else
	{
		onImportClientMessagesCompleted();
	}
}

void KBEngineApp::reLoginBaseapp()
{
	UKBEventData_onReLoginBaseapp* pEventData = NewObject<UKBEventData_onReLoginBaseapp>();
	KBENGINE_EVENT_FIRE("onReLoginBaseapp", pEventData);
	pNetworkInterface_->connectTo(baseappIP_, baseappPort_, this, 1);
}

void KBEngineApp::Client_onLoginBaseappFailed(uint16 failedcode)
{
	ERROR_MSG("failedcode(%d:%s)!", failedcode, *serverErr(failedcode));

	UKBEventData_onLoginBaseappFailed* pEventData = NewObject<UKBEventData_onLoginBaseappFailed>();
	pEventData->failedcode = failedcode;
	pEventData->errorStr = serverErr(failedcode);
	KBENGINE_EVENT_FIRE("onLoginBaseappFailed", pEventData);
}

void KBEngineApp::Client_onReLoginBaseappFailed(uint16 failedcode)
{
	ERROR_MSG("failedcode(%d:%s)!", failedcode, *serverErr(failedcode));

	UKBEventData_onReLoginBaseappFailed* pEventData = NewObject<UKBEventData_onReLoginBaseappFailed>();
	pEventData->failedcode = failedcode;
	pEventData->errorStr = serverErr(failedcode);
	KBENGINE_EVENT_FIRE("onReLoginBaseappFailed", pEventData);
}

void KBEngineApp::Client_onReLoginBaseappSuccessfully(MemoryStream& stream)
{
	stream >> entity_uuid_;
	ERROR_MSG("name(%s)!", *username_);
	UKBEventData_onReLoginBaseappSuccessfully* pEventData = NewObject<UKBEventData_onReLoginBaseappSuccessfully>();
	KBENGINE_EVENT_FIRE("onReLoginBaseappSuccessfully", pEventData);
}

void KBEngineApp::Client_onCreatedProxies(uint64 rndUUID, int32 eid, FString& entityType)
{
	DEBUG_MSG("eid(%d), entityType(%s)!", eid, *entityType);

	if (entities_.Contains(eid))
	{
		// WARNING_MSG("eid(%d) has exist!", eid);
		Client_onEntityDestroyed(eid);
	}

	entity_uuid_ = rndUUID;
	entity_id_ = eid;
	entity_type_ = entityType;

	ScriptModule** pModuleFind = EntityDef::moduledefs.Find(entityType);
	if (!pModuleFind)
	{
		SCREEN_ERROR_MSG("not found module(%s)!", *entityType);
		return;
	}

	ScriptModule* pModule = *pModuleFind;

	EntityCreator* pEntityCreator = pModule->pEntityCreator;
	if (!pEntityCreator)
		return;

	Entity* pEntity = pEntityCreator->create();
	pEntity->id(eid);
	pEntity->className(entityType);

	Mailbox* baseMB = new Mailbox();
	pEntity->base(baseMB);
	baseMB->id = eid;
	baseMB->className = entityType;
	baseMB->type = Mailbox::MAILBOX_TYPE_BASE;

	entities_.Add(eid, pEntity);

	MemoryStream** entityMessageFind = bufferedCreateEntityMessage_.Find(eid);
	if (entityMessageFind)
	{
		MemoryStream* entityMessage = *entityMessageFind;
		Client_onUpdatePropertys(*entityMessage);
		bufferedCreateEntityMessage_.Remove(eid);
		MemoryStream::reclaimObject(entityMessage);
	}

	pEntity->__init__();
	pEntity->inited(true);

	if (pArgs_->isOnInitCallPropertysSetMethods)
		pEntity->callPropertysSetMethods();
}

ENTITY_ID KBEngineApp::getAoiEntityIDFromStream(MemoryStream& stream)
{
	ENTITY_ID id = 0;

	if (!pArgs_->useAliasEntityID)
	{
		stream >> id;
		return id;
	}

	if (entityIDAliasIDList_.Num()> 255)
	{
		stream >> id;
	}
	else
	{
		uint8 aliasID = 0;
		stream >> aliasID;

		// 如果为0且客户端上一步是重登陆或者重连操作并且服务端entity在断线期间一直处于在线状态
		// 则可以忽略这个错误, 因为cellapp可能一直在向baseapp发送同步消息， 当客户端重连上时未等
		// 服务端初始化步骤开始则收到同步信息, 此时这里就会出错。
		if (entityIDAliasIDList_.Num() <= aliasID)
			return 0;

		id = entityIDAliasIDList_[aliasID];
	}

	return id;
}

void KBEngineApp::Client_onUpdatePropertysOptimized(MemoryStream& stream)
{
	ENTITY_ID eid = getAoiEntityIDFromStream(stream);
	onUpdatePropertys_(eid, stream);
}

void KBEngineApp::Client_onUpdatePropertys(MemoryStream& stream)
{
	ENTITY_ID eid;
	stream >> eid;
	onUpdatePropertys_(eid, stream);
}

void KBEngineApp::onUpdatePropertys_(ENTITY_ID eid, MemoryStream& stream)
{
	Entity** pEntityFind = entities_.Find(eid);

	if (!pEntityFind)
	{
		MemoryStream** entityMessageFind = bufferedCreateEntityMessage_.Find(eid);
		if (entityMessageFind)
		{
			ERROR_MSG("entity(%d) not found!", eid);
			return;
		}

		MemoryStream* stream1 = MemoryStream::createObject();
		stream1->append(stream);
		stream1->rpos(stream.rpos() - 4);
		bufferedCreateEntityMessage_.Add(eid, stream1);
		return;
	}
	
	Entity* pEntity = *pEntityFind;

	ScriptModule** smFind = EntityDef::moduledefs.Find(pEntity->className());
	if (!smFind)
	{
		ERROR_MSG("module(%s) not found!", *pEntity->className());
		return;
	}

	ScriptModule* sm = *smFind;
	TMap<uint16, Property*>& pdatas = sm->idpropertys;

	while (stream.length() > 0)
	{
		uint16 utype = 0;

		if (sm->usePropertyDescrAlias)
		{
			utype = stream.read<uint8>();
		}
		else
		{
			utype = stream.read<uint16>();
		}

		Property* propertydata = pdatas[utype];
		utype = propertydata->properUtype;
		EntityDefMethodHandle* pSetMethod = propertydata->pSetMethod;

		KBVar* val = propertydata->pUtype->createFromStream(stream);
		// DEBUG_MSG("entity.className + "(id=" + eid  + " " + 
		// propertydata.name + "=" + val->c_str() + "), hasSetMethod=" + setmethod + "!");

		EntityDefPropertyHandle* pEntityDefPropertyHandle = EntityDefPropertyHandles::find(pEntity->className(), propertydata->name);
		if (!pEntityDefPropertyHandle)
		{
			SCREEN_ERROR_MSG("%s not found property(%s), update error! Please register with ENTITYDEF_PROPERTY_REGISTER(%s, %s) in %s.cpp",
				*pEntity->className(), *propertydata->name,
				*pEntity->className(), *pEntity->className(), *propertydata->name);

			delete val;
			continue;
		}

		KBVar* oldval = pEntityDefPropertyHandle->getPropertyValue(pEntity);
		pEntityDefPropertyHandle->setPropertyValue(pEntity, val);

		if (pSetMethod)
		{
			if (propertydata->isBase())
			{
				if (pEntity->inited())
					pSetMethod->callMethod(pEntity, *oldval);
			}
			else
			{
				if (pEntity->inWorld())
					pSetMethod->callMethod(pEntity, *oldval);
			}
		}

		delete oldval;
		delete val;
	}
}

void KBEngineApp::Client_onEntityDestroyed(int32 eid)
{

}

void KBEngineApp::clearSpace(bool isall)
{

}

void KBEngineApp::clearEntities(bool isall)
{

}

void KBEngineApp::onImportClientMessagesCompleted()
{
	DEBUG_MSG("successfully! currserver=%s, currstate=%s", *currserver_, *currstate_);

	if (currserver_ == TEXT("loginapp"))
	{
		if (!isImportServerErrorsDescr_ && !loadingLocalMessages_)
		{
			DEBUG_MSG("send importServerErrorsDescr!");
			isImportServerErrorsDescr_ = true;
			Bundle* pBundle = Bundle::createObject();
			pBundle->newMessage(Messages::getSingleton().messages[TEXT("Loginapp_importServerErrorsDescr"]));
			pBundle->send(pNetworkInterface_);
		}

		if (currstate_ == TEXT("login"))
		{
			login_loginapp(false);
		}
		else if (currstate_ == TEXT("autoimport"))
		{
		}
		else if (currstate_ == TEXT("resetpassword"))
		{
			resetpassword_loginapp(false);
		}
		else if (currstate_ == TEXT("createAccount"))
		{
			createAccount_loginapp(false);
		}
		else {
		}

		loginappMessageImported_ = true;
	}
	else
	{
		baseappMessageImported_ = true;

		if (!entitydefImported_ && !loadingLocalMessages_)
		{
			DEBUG_MSG("send importEntityDef(%d) ...", entitydefImported_);
			Bundle* pBundle = Bundle::createObject();
			pBundle->newMessage(Messages::getSingleton().messages[TEXT("Baseapp_importClientEntityDef"]));
			pBundle->send(pNetworkInterface_);
			KBENGINE_EVENT_FIRE("Baseapp_importClientEntityDef", NewObject<UKBEventData_Baseapp_importClientEntityDef>());
		}
		else
		{
			onImportEntityDefCompleted();
		}
	}
}

void KBEngineApp::createDataTypeFromStreams(MemoryStream& stream, bool canprint)
{
	uint16 aliassize = 0;
	stream >> aliassize;

	DEBUG_MSG("importAlias(size=%d)!", aliassize);

	while (aliassize > 0)
	{
		aliassize--;
		createDataTypeFromStream(stream, canprint);
	};

	for (auto& item : EntityDef::datatypes)
	{
		if (item.Value)
		{
			item.Value->bind();
		}
	}
}

void KBEngineApp::createDataTypeFromStream(MemoryStream& stream, bool canprint)
{
	uint16 utype = 0;
	stream >> utype;

	FString name;
	stream >> name;

	FString valname;
	stream >> valname;

	/* 有一些匿名类型，我们需要提供一个唯一名称放到datatypes中
		如：
		<onRemoveAvatar>
		<Arg>	ARRAY <of> INT8 </of>		</Arg>
		</onRemoveAvatar>
	*/
	if (valname.Len() == 0)
		valname = FString::Printf(TEXT("Null_%d"), (int)utype);

	if (canprint)
		DEBUG_MSG("importAlias(%s:%s:%d)!", *name, *valname, utype);

	if (name == TEXT("FIXED_DICT"))
	{
		KBEDATATYPE_FIXED_DICT* datatype = new KBEDATATYPE_FIXED_DICT();
		uint8 keysize;
		stream >> keysize;

		stream >> datatype->implementedBy;

		while (keysize > 0)
		{
			keysize--;

			FString keyname;
			stream >> keyname;

			uint16 keyutype;
			stream >> keyutype;

			datatype->dicttype_map.Add(keyname, keyutype);
		};

		EntityDef::datatypes.Add(valname, datatype);
	}
	else if (name == TEXT("ARRAY"))
	{
		uint16 uitemtype;
		stream >> uitemtype;

		KBEDATATYPE_ARRAY* datatype = new KBEDATATYPE_ARRAY();
		datatype->tmpset_uitemtype = (int)uitemtype;
		EntityDef::datatypes.Add(valname, datatype);
	}
	else
	{
		// 可能会重复向map添加基本类型， 此时需要过滤掉
		//if (EntityDef::datatypes.Contains(valname))
		//	return;

		KBEDATATYPE_BASE* val = NULL;
		if (EntityDef::datatypes.Contains(name))
			val = EntityDef::datatypes[name];

		EntityDef::datatypes.Add(valname, val);
	}

	// 可能会重复向map添加基本类型， 此时需要过滤掉
	//if (EntityDef::id2datatypes.Contains(utype))
	//	return;

	EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[valname]);

	// 将用户自定义的类型补充到映射表中
	EntityDef::datatype2id.Add(valname, utype);

}

void KBEngineApp::Client_onImportClientEntityDef(MemoryStream& stream)
{
	TArray<uint8> datas;
	datas.SetNumUninitialized(stream.length());
	memcpy(datas.GetData(), stream.data() + stream.rpos(), stream.length());

	onImportClientEntityDef(stream);

	if (persistentInfos_)
		persistentInfos_->onImportClientEntityDef(datas);
}

void KBEngineApp::onImportClientEntityDef(MemoryStream& stream)
{
	createDataTypeFromStreams(stream, true);

	while (stream.length() > 0)
	{
		FString scriptmodule_name;
		stream >> scriptmodule_name;

		uint16 scriptUtype;
		stream >> scriptUtype;

		uint16 propertysize;
		stream >> propertysize;

		uint16 methodsize;
		stream >> methodsize;

		uint16 base_methodsize;
		stream >> base_methodsize;

		uint16 cell_methodsize;
		stream >> cell_methodsize;

		DEBUG_MSG("import(%s), propertys(%d), "
			"clientMethods(%d), baseMethods(%d), cellMethods(%d)!", *scriptmodule_name,
			propertysize, methodsize, base_methodsize, cell_methodsize);

		ScriptModule* module = new ScriptModule(scriptmodule_name);
		EntityDef::moduledefs.Add(scriptmodule_name, module);
		EntityDef::idmoduledefs.Add(scriptUtype, module);

		EntityCreator* pEntityCreator = module->pEntityCreator;

		while (propertysize > 0)
		{
			propertysize--;

			uint16 properUtype;
			stream >> properUtype;

			uint32 properFlags;
			stream >> properFlags;

			int16 paliasID;
			stream >> paliasID;

			FString pname;
			stream >> pname;

			FString defaultValStr;
			stream >> defaultValStr;

			uint16 iutype;
			stream >> iutype;
			KBEDATATYPE_BASE* utype = EntityDef::id2datatypes[iutype];

			EntityDefMethodHandle* pEntityDefMethodHandle = NULL;

			if (pEntityCreator)
				pEntityDefMethodHandle = EntityDefMethodHandles::find(scriptmodule_name, FString::Printf(TEXT("set_%s"), *pname));

			Property* savedata = new Property();
			savedata->name = pname;
			savedata->pUtype = utype;
			savedata->properUtype = properUtype;
			savedata->properFlags = properFlags;
			savedata->aliasID = paliasID;
			savedata->defaultValStr = defaultValStr;
			savedata->pSetMethod = pEntityDefMethodHandle;
			savedata->pdefaultVal = savedata->pUtype->parseDefaultValStr(savedata->defaultValStr);

			module->propertys.Add(pname, savedata);

			if (paliasID >= 0)
			{
				module->usePropertyDescrAlias = true;
				module->idpropertys.Add(paliasID, savedata);
			}
			else
			{
				module->usePropertyDescrAlias = false;
				module->idpropertys.Add(properUtype, savedata);
			}

			DEBUG_MSG("add(%s), property(%s/%d), hasSetMethod=%s.", *scriptmodule_name, *pname, 
				properUtype, (savedata->pSetMethod ? TEXT("true") : TEXT("false")));
		};

		while (methodsize > 0)
		{
			methodsize--;

			uint16 methodUtype;
			stream >> methodUtype;

			int16 ialiasID;
			stream >> ialiasID;

			FString name;
			stream >> name;

			uint8 argssize;
			stream >> argssize;

			TArray<KBEDATATYPE_BASE*> args;

			while (argssize > 0)
			{
				argssize--;
				uint16 tmpType;
				stream >> tmpType;
				args.Add(EntityDef::id2datatypes[tmpType]);
			};

			Method* savedata = new Method();
			savedata->name = name;
			savedata->methodUtype = methodUtype;
			savedata->aliasID = ialiasID;
			savedata->args = args;

			if (pEntityCreator)
				savedata->pEntityDefMethodHandle = EntityDefMethodHandles::find(scriptmodule_name, name);

			module->methods.Add(name, savedata);

			if (ialiasID >= 0)
			{
				module->useMethodDescrAlias = true;
				module->idmethods.Add(ialiasID, savedata);
			}
			else
			{
				module->useMethodDescrAlias = false;
				module->idmethods.Add(methodUtype, savedata);
			}

			DEBUG_MSG("add(%s), method(%s).", *scriptmodule_name, *name);
		};

		while (base_methodsize > 0)
		{
			base_methodsize--;

			uint16 methodUtype;
			stream >> methodUtype;

			int16 ialiasID;
			stream >> ialiasID;

			FString name;
			stream >> name;

			uint8 argssize;
			stream >> argssize;

			TArray<KBEDATATYPE_BASE*> args;

			while (argssize > 0)
			{
				argssize--;
				uint16 tmpType;
				stream >> tmpType;
				args.Add(EntityDef::id2datatypes[tmpType]);
			};

			Method* savedata = new Method();
			savedata->name = name;
			savedata->methodUtype = methodUtype;
			savedata->aliasID = ialiasID;
			savedata->args = args;

			module->base_methods.Add(name, savedata);
			module->idbase_methods.Add(methodUtype, savedata);

			DEBUG_MSG("add(%s), base_method(%s).", *scriptmodule_name, *name);
		};

		while (cell_methodsize > 0)
		{
			cell_methodsize--;

			uint16 methodUtype;
			stream >> methodUtype;

			int16 ialiasID;
			stream >> ialiasID;

			FString name;
			stream >> name;

			uint8 argssize;
			stream >> argssize;

			TArray<KBEDATATYPE_BASE*> args;

			while (argssize > 0)
			{
				argssize--;
				uint16 tmpType;
				stream >> tmpType;
				args.Add(EntityDef::id2datatypes[tmpType]);
			};

			Method* savedata = new Method();
			savedata->name = name;
			savedata->methodUtype = methodUtype;
			savedata->aliasID = ialiasID;
			savedata->args = args;

			module->cell_methods.Add(name, savedata);
			module->idcell_methods.Add(methodUtype, savedata);

			DEBUG_MSG("add(%s), cell_method(%s).", *scriptmodule_name, *name);
		};

		if (!pEntityCreator)
		{
			SCREEN_ERROR_MSG("module(%s) not found!", *scriptmodule_name);
		}

		for(auto& e : module->methods)
		{
			FString name = e.Key;
			
			if (pEntityCreator && !EntityDefMethodHandles::find(scriptmodule_name, name))
			{
				SCREEN_WARNING_MSG("%s:: method(%s) no implement!", *scriptmodule_name, *name);
			}
		};
	};

	onImportEntityDefCompleted();
}

void KBEngineApp::onImportEntityDefCompleted()
{
	DEBUG_MSG("successfully!");
	entitydefImported_ = true;

	if (!loadingLocalMessages_)
		login_baseapp(false);
}

void KBEngineApp::Client_onImportClientMessages(MemoryStream& stream)
{
	TArray<uint8> datas;
	datas.SetNumUninitialized(stream.length());
	memcpy(datas.GetData(), stream.data() + stream.rpos(), stream.length());

	onImportClientMessages(stream);

	if (persistentInfos_)
		persistentInfos_->onImportClientMessages(currserver_, datas);
}

void KBEngineApp::onImportClientMessages(MemoryStream& stream)
{
	uint16 msgcount = 0;
	stream >> msgcount;

	DEBUG_MSG("start currserver=%s(msgsize=%d)...", *currserver_, msgcount);

	while (msgcount > 0)
	{
		msgcount--;

		MessageID msgid = 0;
		stream >> msgid;

		int16 msglen = 0;
		stream >> msglen;

		FString msgname;
		stream >> msgname;
		
		int8 argstype = 0;
		stream >> argstype;

		uint8 argsize = 0;
		stream >> argsize;

		TArray<uint8> argstypes;

		for (uint8 i = 0; i<argsize; i++)
		{
			uint8 v = 0;
			stream >> v;
			argstypes.Add(v);
		}

		Message* handler = Messages::getSingleton().findMessage(msgname);
		bool isClientMethod = msgname.Contains(TEXT("Client_"), ESearchCase::CaseSensitive, ESearchDir::FromEnd);

		if (isClientMethod)
		{
			if (handler == NULL)
			{
				SCREEN_WARNING_MSG("currserver[%s]: interface(%s/%d/%d) no implement!",
					*currserver_, *msgname, msgid, msglen);
			}
			else
			{
				DEBUG_MSG("imported(%s/%d/%d) successfully!", 
					*msgname, msgid, msglen);
			}
		}

		if (handler)
		{
			FString old_cstr = handler->c_str();
			handler->id = msgid;
			handler->msglen = msglen;

			// 因为握手类ID一开始临时设置为负数， 所以需要重新以正确的ID添加到列表
			if (isClientMethod)
				Messages::getSingleton().add(handler, msgid, msgname, msglen);

			if (handler->id <= 0)
			{
				DEBUG_MSG("currserver[%s]: refreshed(%s => %s)!",
					*currserver_, *old_cstr, *handler->c_str());
			}
		}
		else
		{
			if (msgname != TEXT(""))
			{
				Messages::getSingleton().messages.Add(msgname, new Message(msgid, msgname, msglen));

				if(!isClientMethod)
					DEBUG_MSG("currserver[%s]: imported(%s/%d/%d) successfully!",
						*currserver_, *msgname, msgid, msglen);

				if (isClientMethod)
				{
					Messages::getSingleton().clientMessages.Add(msgid, Messages::getSingleton().messages[msgname]);
				}
				else
				{
					if (currserver_ == TEXT("loginapp"))
						Messages::getSingleton().loginappMessages.Add(msgid, Messages::getSingleton().messages[msgname]);
					else
						Messages::getSingleton().baseappMessages.Add(msgid, Messages::getSingleton().messages[msgname]);
				}
			}
			else
			{
				Message* msg = new Message(msgid, msgname, msglen);

				if(!isClientMethod)
					DEBUG_MSG("currserver[%s]: imported(%s/%d/%d) successfully!",
						*currserver_, *msgname, msgid, msglen);

				if (currserver_ == TEXT("loginapp"))
					Messages::getSingleton().loginappMessages.Add(msgid, msg);
				else
					Messages::getSingleton().baseappMessages.Add(msgid, msg);
			}
		}
	};

	onImportClientMessagesCompleted();
}

void KBEngineApp::resetPassword(const FString& username)
{
	username_ = username;
	resetpassword_loginapp(true);
}

void KBEngineApp::resetpassword_loginapp(bool noconnect)
{

}

bool KBEngineApp::createAccount(const FString& username, const FString& password, const TArray<uint8>& datas)
{
	if (username.Len() == 0)
	{
		ERROR_MSG("username is empty!");
		return false;
	}

	if (password.Len() == 0)
	{
		ERROR_MSG("password is empty!");
		return false;
	}

	username_ = username;
	password_ = password;
	clientdatas_ = datas;

	createAccount_loginapp(true);
	return true;
}

void KBEngineApp::createAccount_loginapp(bool noconnect)
{
	if (noconnect)
	{
		reset();
		pNetworkInterface_->connectTo(pArgs_->ip, pArgs_->port, this, 1);
	}
	else
	{
		INFO_MSG("send create! username=%s", *username_);
		Bundle* pBundle = Bundle::createObject();
		pBundle->newMessage(Messages::getSingleton().messages[TEXT("Loginapp_reqCreateAccount"]));
		(*pBundle) << username_;
		(*pBundle) << password_;
		pBundle->appendBlob(clientdatas_);
		pBundle->send(pNetworkInterface_);
	}
}

void KBEngineApp::onOpenLoginapp_createAccount()
{
	DEBUG_MSG("successfully!");

	currserver_ = TEXT("loginapp");
	currstate_ = TEXT("createAccount");
	lastTickCBTime_ = getTimeSeconds();

	if (!loginappMessageImported_)
	{
		Bundle* pBundle = Bundle::createObject();
		pBundle->newMessage(Messages::getSingleton().messages[TEXT("Loginapp_importClientMessages"]));
		pBundle->send(pNetworkInterface_);
		DEBUG_MSG("send importClientMessages ...");
	}
	else
	{
		onImportClientMessagesCompleted();
	}
}

void KBEngineApp::onConnectTo_loginapp_create_callback(FString ip, uint16 port, bool success)
{
	lastTickCBTime_ = getTimeSeconds();

	if (!success)
	{
		ERROR_MSG("connect %s:%d is error!", *ip, port);
		return;
	}

	INFO_MSG("connect %s:%d is success!", *ip, port);

	onOpenLoginapp_createAccount();
}

void KBEngineApp::Client_onCreateAccountResult(MemoryStream& stream)
{
	uint16 retcode;
	stream >> retcode;

	TArray<uint8> datas;
	stream.readBlob(datas);

	UKBEventData_onCreateAccountResult* pEventData = NewObject<UKBEventData_onCreateAccountResult>();
	pEventData->errorCode = retcode;
	pEventData->errorStr = serverErr(retcode);
	pEventData->datas = datas;
	KBENGINE_EVENT_FIRE("onCreateAccountResult", pEventData);

	if (retcode != 0)
	{
		WARNING_MSG("create(%s) failed! error=%d(%s)!", *username_, retcode, *serverErr(retcode));
		return;
	}

	DEBUG_MSG("create(%s) is successfully!", *username_);
}

void KBEngineApp::bindAccountEmail(const FString& emailAddress)
{

}

void KBEngineApp::newPassword(const FString& old_password, const FString& new_password)
{

}

void KBEngineApp::Client_onRemoteMethodCallOptimized(MemoryStream& stream)
{
	ENTITY_ID eid = getAoiEntityIDFromStream(stream);
	onRemoteMethodCall_(eid, stream);
}

void KBEngineApp::Client_onRemoteMethodCall(MemoryStream& stream)
{
	ENTITY_ID eid = 0;
	stream >> eid;
	onRemoteMethodCall_(eid, stream);
}

void KBEngineApp::onRemoteMethodCall_(ENTITY_ID eid, MemoryStream& stream)
{
	Entity** pEntityFind = entities_.Find(eid);

	if (!pEntityFind)
	{
		ERROR_MSG("entity(%d) not found!", eid);
		return;
	}

	Entity* pEntity = *pEntityFind;

	uint16 methodUtype = 0;

	ScriptModule** pModuleFind = EntityDef::moduledefs.Find(pEntity->className());
	if (!pModuleFind)
	{
		SCREEN_ERROR_MSG("not found ScriptModule(%s)!", *pEntity->className());
		return;
	}

	ScriptModule* pModule = *pModuleFind;

	if (pModule->useMethodDescrAlias)
		methodUtype = stream.read<uint8>();
	else
		methodUtype = stream.read<uint16>();

	Method* pMethodData = pModule->idmethods[methodUtype];

	TArray<KBVar*> args;
	for (int i = 0; i<pMethodData->args.Num(); ++i)
	{
		KBVar* pVar = pMethodData->args[i]->createFromStream(stream);
		args.Add(pVar);
	}

	if (pMethodData->pEntityDefMethodHandle)
	{
		pMethodData->pEntityDefMethodHandle->callMethod(pEntity, args);
	}
	else
	{
		SCREEN_ERROR_MSG("%s(%d), not found method(%s::%s)!\n", *pEntity->className(), eid, *pEntity->className(), *pMethodData->name);
	}

	for (auto& item : args)
		delete item;
}