// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "KBECommon.h"
#include "KBVar.h"

class MemoryStream;

/*
	entitydef所支持的基本数据类型
	改模块中的类抽象出了所有的支持类型并提供了这些类型的数据序列化成二进制数据与反序列化操作（主要用于网络通讯的打包与解包）
*/
class KBENGINEPLUGINS_API KBEDATATYPE_BASE
{
public:
		virtual void bind()
		{
		}

		static bool isNumeric(KBVar& v)
		{
			return v.GetType() == EKBVarTypes::Bool || 
				v.GetType() == EKBVarTypes::Double ||
				v.GetType() == EKBVarTypes::Float ||
				v.GetType() == EKBVarTypes::Int8 ||
				v.GetType() == EKBVarTypes::Int16 ||
				v.GetType() == EKBVarTypes::Int32 ||
				v.GetType() == EKBVarTypes::Int64 ||
				v.GetType() == EKBVarTypes::UInt8 ||
				v.GetType() == EKBVarTypes::UInt16 ||
				v.GetType() == EKBVarTypes::UInt32 ||
				v.GetType() == EKBVarTypes::UInt64;
		}

		virtual KBVar* createFromStream(MemoryStream& stream)
		{
			return NULL;
		}
		
		virtual void addToStream(Bundle& stream, KBVar& v)
		{
		}
		
		virtual KBVar* parseDefaultValStr(const FString& v)
		{
			return NULL;
		}
		
		virtual bool isSameType(KBVar& v)
		{
			return v == NULL;
		}
		
protected:

};

class KBENGINEPLUGINS_API KBEDATATYPE_INT8 : public KBEDATATYPE_BASE
{
public:
	virtual KBVar* createFromStream(MemoryStream& stream) override;
	virtual void addToStream(Bundle& stream, KBVar& v) override;

	virtual KBVar* parseDefaultValStr(const FString& v) override;

	virtual bool isSameType(KBVar& v) override;
};

class KBENGINEPLUGINS_API KBEDATATYPE_INT16 : public KBEDATATYPE_BASE
{
public:
	virtual KBVar* createFromStream(MemoryStream& stream) override;
	virtual void addToStream(Bundle& stream, KBVar& v) override;

	virtual KBVar* parseDefaultValStr(const FString& v) override;

	virtual bool isSameType(KBVar& v) override;
};

class KBENGINEPLUGINS_API KBEDATATYPE_INT32 : public KBEDATATYPE_BASE
{
public:
	virtual KBVar* createFromStream(MemoryStream& stream) override;
	virtual void addToStream(Bundle& stream, KBVar& v) override;

	virtual KBVar* parseDefaultValStr(const FString& v) override;

	virtual bool isSameType(KBVar& v) override;
};

class KBENGINEPLUGINS_API KBEDATATYPE_INT64 : public KBEDATATYPE_BASE
{
public:
	virtual KBVar* createFromStream(MemoryStream& stream) override;
	virtual void addToStream(Bundle& stream, KBVar& v) override;

	virtual KBVar* parseDefaultValStr(const FString& v) override;

	virtual bool isSameType(KBVar& v) override;
};

class KBENGINEPLUGINS_API KBEDATATYPE_UINT8 : public KBEDATATYPE_BASE
{
public:
	virtual KBVar* createFromStream(MemoryStream& stream) override;
	virtual void addToStream(Bundle& stream, KBVar& v) override;

	virtual KBVar* parseDefaultValStr(const FString& v) override;

	virtual bool isSameType(KBVar& v) override;
};

class KBENGINEPLUGINS_API KBEDATATYPE_UINT16 : public KBEDATATYPE_BASE
{
public:
	virtual KBVar* createFromStream(MemoryStream& stream) override;
	virtual void addToStream(Bundle& stream, KBVar& v) override;

	virtual KBVar* parseDefaultValStr(const FString& v) override;

	virtual bool isSameType(KBVar& v) override;
};

class KBENGINEPLUGINS_API KBEDATATYPE_UINT32 : public KBEDATATYPE_BASE
{
public:
	virtual KBVar* createFromStream(MemoryStream& stream) override;
	virtual void addToStream(Bundle& stream, KBVar& v) override;

	virtual KBVar* parseDefaultValStr(const FString& v) override;

	virtual bool isSameType(KBVar& v) override;
};

class KBENGINEPLUGINS_API KBEDATATYPE_UINT64 : public KBEDATATYPE_BASE
{
public:
	virtual KBVar* createFromStream(MemoryStream& stream) override;
	virtual void addToStream(Bundle& stream, KBVar& v) override;

	virtual KBVar* parseDefaultValStr(const FString& v) override;

	virtual bool isSameType(KBVar& v) override;
};

class KBENGINEPLUGINS_API KBEDATATYPE_FLOAT : public KBEDATATYPE_BASE
{
public:
	virtual KBVar* createFromStream(MemoryStream& stream) override;
	virtual void addToStream(Bundle& stream, KBVar& v) override;

	virtual KBVar* parseDefaultValStr(const FString& v) override;

	virtual bool isSameType(KBVar& v) override;
};

class KBENGINEPLUGINS_API KBEDATATYPE_DOUBLE : public KBEDATATYPE_BASE
{
public:
	virtual KBVar* createFromStream(MemoryStream& stream) override;
	virtual void addToStream(Bundle& stream, KBVar& v) override;

	virtual KBVar* parseDefaultValStr(const FString& v) override;

	virtual bool isSameType(KBVar& v) override;
};

class KBENGINEPLUGINS_API KBEDATATYPE_STRING : public KBEDATATYPE_BASE
{
public:
	virtual KBVar* createFromStream(MemoryStream& stream) override;
	virtual void addToStream(Bundle& stream, KBVar& v) override;

	virtual KBVar* parseDefaultValStr(const FString& v) override;

	virtual bool isSameType(KBVar& v) override;
};

class KBENGINEPLUGINS_API KBEDATATYPE_VECTOR2 : public KBEDATATYPE_BASE
{
public:
	virtual KBVar* createFromStream(MemoryStream& stream) override;
	virtual void addToStream(Bundle& stream, KBVar& v) override;

	virtual KBVar* parseDefaultValStr(const FString& v) override;

	virtual bool isSameType(KBVar& v) override;
};

class KBENGINEPLUGINS_API KBEDATATYPE_VECTOR3 : public KBEDATATYPE_BASE
{
public:
	virtual KBVar* createFromStream(MemoryStream& stream) override;
	virtual void addToStream(Bundle& stream, KBVar& v) override;

	virtual KBVar* parseDefaultValStr(const FString& v) override;

	virtual bool isSameType(KBVar& v) override;
};

class KBENGINEPLUGINS_API KBEDATATYPE_VECTOR4 : public KBEDATATYPE_BASE
{
public:
	virtual KBVar* createFromStream(MemoryStream& stream) override;
	virtual void addToStream(Bundle& stream, KBVar& v) override;

	virtual KBVar* parseDefaultValStr(const FString& v) override;

	virtual bool isSameType(KBVar& v) override;
};

class KBENGINEPLUGINS_API KBEDATATYPE_PYTHON : public KBEDATATYPE_BASE
{
public:
	virtual KBVar* createFromStream(MemoryStream& stream) override;
	virtual void addToStream(Bundle& stream, KBVar& v) override;

	virtual KBVar* parseDefaultValStr(const FString& v) override;

	virtual bool isSameType(KBVar& v) override;
};

class KBENGINEPLUGINS_API KBEDATATYPE_UNICODE : public KBEDATATYPE_BASE
{
public:
	virtual KBVar* createFromStream(MemoryStream& stream) override;
	virtual void addToStream(Bundle& stream, KBVar& v) override;

	virtual KBVar* parseDefaultValStr(const FString& v) override;

	virtual bool isSameType(KBVar& v) override;
};

class KBENGINEPLUGINS_API KBEDATATYPE_MAILBOX : public KBEDATATYPE_BASE
{
public:
	virtual KBVar* createFromStream(MemoryStream& stream) override;
	virtual void addToStream(Bundle& stream, KBVar& v) override;

	virtual KBVar* parseDefaultValStr(const FString& v) override;

	virtual bool isSameType(KBVar& v) override;
};

class KBENGINEPLUGINS_API KBEDATATYPE_BLOB : public KBEDATATYPE_BASE
{
public:
	virtual KBVar* createFromStream(MemoryStream& stream) override;
	virtual void addToStream(Bundle& stream, KBVar& v) override;

	virtual KBVar* parseDefaultValStr(const FString& v) override;

	virtual bool isSameType(KBVar& v) override;
};

class KBENGINEPLUGINS_API KBEDATATYPE_ARRAY : public KBEDATATYPE_BASE
{
public:
	KBEDATATYPE_ARRAY() :
		vtype(NULL),
		tmpset_uitemtype(-1)
	{

	}

	virtual void bind() override;

	virtual KBVar* createFromStream(MemoryStream& stream) override;
	virtual void addToStream(Bundle& stream, KBVar& v) override;

	virtual KBVar* parseDefaultValStr(const FString& v) override;

	virtual bool isSameType(KBVar& v) override;

public:
	KBEDATATYPE_BASE* vtype;
	int tmpset_uitemtype;
};

class KBENGINEPLUGINS_API KBEDATATYPE_FIXED_DICT : public KBEDATATYPE_BASE
{
public:
	KBEDATATYPE_FIXED_DICT() :
		implementedBy(),
		dicttype(),
		dicttype_map()
	{

	}

	virtual void bind() override;

	virtual KBVar* createFromStream(MemoryStream& stream) override;
	virtual void addToStream(Bundle& stream, KBVar& v) override;

	virtual KBVar* parseDefaultValStr(const FString& v) override;

	virtual bool isSameType(KBVar& v) override;

public:
	FString implementedBy;
	TMap<FString, KBEDATATYPE_BASE*> dicttype;
	TMap<FString, uint16> dicttype_map;
};













