#include "Messages.h"
#include "MemoryStream.h"
#include "KBEngine.h"

namespace KBEngine
{

TMap<MessageID, Message*> Messages::loginappMessages;
TMap<MessageID, Message*> Messages::baseappMessages;
TMap<MessageID, Message*> Messages::clientMessages;
TMap<FString, Message*> Messages::messages;

void Message_Client_onReloginBaseappFailed::handleMessage(MemoryStream& msgstream)
{
	uint16 arg1 = msgstream.readUint16();
	KBEngineApp::getSingleton().Client_onReloginBaseappFailed(arg1);
}

void Message_Client_onEntityLeaveWorldOptimized::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onEntityLeaveWorldOptimized(msgstream);
}

void Message_Client_onRemoteMethodCallOptimized::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onRemoteMethodCallOptimized(msgstream);
}

void Message_Client_onUpdatePropertysOptimized::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdatePropertysOptimized(msgstream);
}

void Message_Client_onSetEntityPosAndDir::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onSetEntityPosAndDir(msgstream);
}

void Message_Client_onUpdateBasePos::handleMessage(MemoryStream& msgstream)
{
	float arg1 = msgstream.readFloat();
	float arg2 = msgstream.readFloat();
	float arg3 = msgstream.readFloat();
	KBEngineApp::getSingleton().Client_onUpdateBasePos(arg1, arg2, arg3);
}

void Message_Client_onUpdateBaseDir::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateBaseDir(msgstream);
}

void Message_Client_onUpdateBasePosXZ::handleMessage(MemoryStream& msgstream)
{
	float arg1 = msgstream.readFloat();
	float arg2 = msgstream.readFloat();
	KBEngineApp::getSingleton().Client_onUpdateBasePosXZ(arg1, arg2);
}

void Message_Client_onUpdateData::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData(msgstream);
}

void Message_Client_onUpdateData_ypr::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_ypr(msgstream);
}

void Message_Client_onUpdateData_yp::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_yp(msgstream);
}

void Message_Client_onUpdateData_yr::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_yr(msgstream);
}

void Message_Client_onUpdateData_pr::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_pr(msgstream);
}

void Message_Client_onUpdateData_y::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_y(msgstream);
}

void Message_Client_onUpdateData_p::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_p(msgstream);
}

void Message_Client_onUpdateData_r::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_r(msgstream);
}

void Message_Client_onUpdateData_xz::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_xz(msgstream);
}

void Message_Client_onUpdateData_xz_ypr::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_xz_ypr(msgstream);
}

void Message_Client_onUpdateData_xz_yp::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_xz_yp(msgstream);
}

void Message_Client_onUpdateData_xz_yr::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_xz_yr(msgstream);
}

void Message_Client_onUpdateData_xz_pr::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_xz_pr(msgstream);
}

void Message_Client_onUpdateData_xz_y::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_xz_y(msgstream);
}

void Message_Client_onUpdateData_xz_p::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_xz_p(msgstream);
}

void Message_Client_onUpdateData_xz_r::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_xz_r(msgstream);
}

void Message_Client_onUpdateData_xyz::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_xyz(msgstream);
}

void Message_Client_onUpdateData_xyz_ypr::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_xyz_ypr(msgstream);
}

void Message_Client_onUpdateData_xyz_yp::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_xyz_yp(msgstream);
}

void Message_Client_onUpdateData_xyz_yr::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_xyz_yr(msgstream);
}

void Message_Client_onUpdateData_xyz_pr::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_xyz_pr(msgstream);
}

void Message_Client_onUpdateData_xyz_y::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_xyz_y(msgstream);
}

void Message_Client_onUpdateData_xyz_p::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_xyz_p(msgstream);
}

void Message_Client_onUpdateData_xyz_r::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_xyz_r(msgstream);
}

void Message_Client_onUpdateData_ypr_optimized::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_ypr_optimized(msgstream);
}

void Message_Client_onUpdateData_yp_optimized::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_yp_optimized(msgstream);
}

void Message_Client_onUpdateData_yr_optimized::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_yr_optimized(msgstream);
}

void Message_Client_onUpdateData_pr_optimized::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_pr_optimized(msgstream);
}

void Message_Client_onUpdateData_y_optimized::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_y_optimized(msgstream);
}

void Message_Client_onUpdateData_p_optimized::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_p_optimized(msgstream);
}

void Message_Client_onUpdateData_r_optimized::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_r_optimized(msgstream);
}

void Message_Client_onUpdateData_xz_optimized::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_xz_optimized(msgstream);
}

void Message_Client_onUpdateData_xz_ypr_optimized::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_xz_ypr_optimized(msgstream);
}

void Message_Client_onUpdateData_xz_yp_optimized::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_xz_yp_optimized(msgstream);
}

void Message_Client_onUpdateData_xz_yr_optimized::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_xz_yr_optimized(msgstream);
}

void Message_Client_onUpdateData_xz_pr_optimized::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_xz_pr_optimized(msgstream);
}

void Message_Client_onUpdateData_xz_y_optimized::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_xz_y_optimized(msgstream);
}

void Message_Client_onUpdateData_xz_p_optimized::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_xz_p_optimized(msgstream);
}

void Message_Client_onUpdateData_xz_r_optimized::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_xz_r_optimized(msgstream);
}

void Message_Client_onUpdateData_xyz_optimized::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_xyz_optimized(msgstream);
}

void Message_Client_onUpdateData_xyz_ypr_optimized::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_xyz_ypr_optimized(msgstream);
}

void Message_Client_onUpdateData_xyz_yp_optimized::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_xyz_yp_optimized(msgstream);
}

void Message_Client_onUpdateData_xyz_yr_optimized::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_xyz_yr_optimized(msgstream);
}

void Message_Client_onUpdateData_xyz_pr_optimized::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_xyz_pr_optimized(msgstream);
}

void Message_Client_onUpdateData_xyz_y_optimized::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_xyz_y_optimized(msgstream);
}

void Message_Client_onUpdateData_xyz_p_optimized::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_xyz_p_optimized(msgstream);
}

void Message_Client_onUpdateData_xyz_r_optimized::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdateData_xyz_r_optimized(msgstream);
}

void Message_Client_onImportServerErrorsDescr::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onImportServerErrorsDescr(msgstream);
}

void Message_Client_onImportClientSDK::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onImportClientSDK(msgstream);
}

void Message_Client_initSpaceData::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_initSpaceData(msgstream);
}

void Message_Client_setSpaceData::handleMessage(MemoryStream& msgstream)
{
	uint32 arg1 = msgstream.readUint32();
	FString arg2 = msgstream.readString();
	FString arg3 = msgstream.readString();
	KBEngineApp::getSingleton().Client_setSpaceData(arg1, arg2, arg3);
}

void Message_Client_delSpaceData::handleMessage(MemoryStream& msgstream)
{
	uint32 arg1 = msgstream.readUint32();
	FString arg2 = msgstream.readString();
	KBEngineApp::getSingleton().Client_delSpaceData(arg1, arg2);
}

void Message_Client_onReqAccountResetPasswordCB::handleMessage(MemoryStream& msgstream)
{
	uint16 arg1 = msgstream.readUint16();
	KBEngineApp::getSingleton().Client_onReqAccountResetPasswordCB(arg1);
}

void Message_Client_onReqAccountBindEmailCB::handleMessage(MemoryStream& msgstream)
{
	uint16 arg1 = msgstream.readUint16();
	KBEngineApp::getSingleton().Client_onReqAccountBindEmailCB(arg1);
}

void Message_Client_onReqAccountNewPasswordCB::handleMessage(MemoryStream& msgstream)
{
	uint16 arg1 = msgstream.readUint16();
	KBEngineApp::getSingleton().Client_onReqAccountNewPasswordCB(arg1);
}

void Message_Client_onReloginBaseappSuccessfully::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onReloginBaseappSuccessfully(msgstream);
}

void Message_Client_onAppActiveTickCB::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onAppActiveTickCB();
}

void Message_Client_onCreateAccountResult::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onCreateAccountResult(msgstream);
}

void Message_Client_onLoginSuccessfully::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onLoginSuccessfully(msgstream);
}

void Message_Client_onLoginFailed::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onLoginFailed(msgstream);
}

void Message_Client_onCreatedProxies::handleMessage(MemoryStream& msgstream)
{
	uint64 arg1 = msgstream.readUint64();
	int32 arg2 = msgstream.readInt32();
	FString arg3 = msgstream.readString();
	KBEngineApp::getSingleton().Client_onCreatedProxies(arg1, arg2, arg3);
}

void Message_Client_onLoginBaseappFailed::handleMessage(MemoryStream& msgstream)
{
	uint16 arg1 = msgstream.readUint16();
	KBEngineApp::getSingleton().Client_onLoginBaseappFailed(arg1);
}

void Message_Client_onRemoteMethodCall::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onRemoteMethodCall(msgstream);
}

void Message_Client_onEntityEnterWorld::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onEntityEnterWorld(msgstream);
}

void Message_Client_onEntityLeaveWorld::handleMessage(MemoryStream& msgstream)
{
	int32 arg1 = msgstream.readInt32();
	KBEngineApp::getSingleton().Client_onEntityLeaveWorld(arg1);
}

void Message_Client_onEntityEnterSpace::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onEntityEnterSpace(msgstream);
}

void Message_Client_onEntityLeaveSpace::handleMessage(MemoryStream& msgstream)
{
	int32 arg1 = msgstream.readInt32();
	KBEngineApp::getSingleton().Client_onEntityLeaveSpace(arg1);
}

void Message_Client_onUpdatePropertys::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onUpdatePropertys(msgstream);
}

void Message_Client_onEntityDestroyed::handleMessage(MemoryStream& msgstream)
{
	int32 arg1 = msgstream.readInt32();
	KBEngineApp::getSingleton().Client_onEntityDestroyed(arg1);
}

void Message_Client_onStreamDataStarted::handleMessage(MemoryStream& msgstream)
{
	int16 arg1 = msgstream.readInt16();
	uint32 arg2 = msgstream.readUint32();
	FString arg3 = msgstream.readString();
	KBEngineApp::getSingleton().Client_onStreamDataStarted(arg1, arg2, arg3);
}

void Message_Client_onStreamDataRecv::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onStreamDataRecv(msgstream);
}

void Message_Client_onStreamDataCompleted::handleMessage(MemoryStream& msgstream)
{
	int16 arg1 = msgstream.readInt16();
	KBEngineApp::getSingleton().Client_onStreamDataCompleted(arg1);
}

void Message_Client_onKicked::handleMessage(MemoryStream& msgstream)
{
	uint16 arg1 = msgstream.readUint16();
	KBEngineApp::getSingleton().Client_onKicked(arg1);
}

void Message_Client_onImportClientMessages::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onImportClientMessages(msgstream);
}

void Message_Client_onImportClientEntityDef::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onImportClientEntityDef(msgstream);
}

void Message_Client_onHelloCB::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onHelloCB(msgstream);
}

void Message_Client_onScriptVersionNotMatch::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onScriptVersionNotMatch(msgstream);
}

void Message_Client_onVersionNotMatch::handleMessage(MemoryStream& msgstream)
{
	KBEngineApp::getSingleton().Client_onVersionNotMatch(msgstream);
}

void Message_Client_onControlEntity::handleMessage(MemoryStream& msgstream)
{
	int32 arg1 = msgstream.readInt32();
	int8 arg2 = msgstream.readInt8();
	KBEngineApp::getSingleton().Client_onControlEntity(arg1, arg2);
}

void Message_Loginapp_reqCreateAccount::handleMessage(MemoryStream& msgstream)
{
}

void Message_Loginapp_login::handleMessage(MemoryStream& msgstream)
{
}

void Message_Loginapp_hello::handleMessage(MemoryStream& msgstream)
{
}

void Message_Loginapp_importClientMessages::handleMessage(MemoryStream& msgstream)
{
}

void Message_Loginapp_reqCreateMailAccount::handleMessage(MemoryStream& msgstream)
{
}

void Message_Loginapp_importClientSDK::handleMessage(MemoryStream& msgstream)
{
}

void Message_Loginapp_importServerErrorsDescr::handleMessage(MemoryStream& msgstream)
{
}

void Message_Loginapp_onClientActiveTick::handleMessage(MemoryStream& msgstream)
{
}

void Message_Loginapp_reqAccountResetPassword::handleMessage(MemoryStream& msgstream)
{
}

void Message_Baseapp_logoutBaseapp::handleMessage(MemoryStream& msgstream)
{
}

void Message_Baseapp_onUpdateDataFromClient::handleMessage(MemoryStream& msgstream)
{
}

void Message_Baseapp_onUpdateDataFromClientForControlledEntity::handleMessage(MemoryStream& msgstream)
{
}

void Message_Baseapp_reqAccountBindEmail::handleMessage(MemoryStream& msgstream)
{
}

void Message_Baseapp_reqAccountNewPassword::handleMessage(MemoryStream& msgstream)
{
}

void Message_Entity_forwardEntityMessageToCellappFromClient::handleMessage(MemoryStream& msgstream)
{
}

void Message_Baseapp_hello::handleMessage(MemoryStream& msgstream)
{
}

void Message_Baseapp_loginBaseapp::handleMessage(MemoryStream& msgstream)
{
}

void Message_Baseapp_reloginBaseapp::handleMessage(MemoryStream& msgstream)
{
}

void Message_Baseapp_onRemoteCallCellMethodFromClient::handleMessage(MemoryStream& msgstream)
{
}

void Message_Baseapp_onClientActiveTick::handleMessage(MemoryStream& msgstream)
{
}

void Message_Baseapp_importClientMessages::handleMessage(MemoryStream& msgstream)
{
}

void Message_Baseapp_importClientEntityDef::handleMessage(MemoryStream& msgstream)
{
}

void Message_Entity_onRemoteMethodCall::handleMessage(MemoryStream& msgstream)
{
}


}