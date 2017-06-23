#include "stdafx.h"
#include "JsonSettings.h"

CJsonSettings::CJsonSettings()
{
}

CJsonSettings::~CJsonSettings()
{
}

void CJsonSettings::createDefaultConfig()
{
	const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
	Document d;
	d.Parse(json);
	 
	d.AddMember("Name", "david k.", d.GetAllocator());
	// 2. Modify it by DOM.
	Value& s = d["stars"];
	s.SetInt(s.GetInt() + 1);

	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	d.Accept(writer);

	printf_s("%s\n", buffer.GetString());
	//enum Type {
	//	kNullType = 0,      //!< null
	//	kFalseType = 1,     //!< false
	//	kTrueType = 2,      //!< true
	//	kObjectType = 3,    //!< object
	//	kArrayType = 4,     //!< array 
	//	kStringType = 5,    //!< string
	//	kNumberType = 6     //!< number
	//};
	for (Value::ConstMemberIterator itr = d.MemberBegin();
		itr != d.MemberEnd(); ++itr)
	{
		printf_s("Type of member %s is %d\n",itr->name.GetString(), (int)itr->value.GetType());
	}
	Value::ConstMemberIterator itr = d.FindMember("Name");
	if (itr != d.MemberEnd())
		printf_s("%s\n", itr->value.GetString());
}