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

	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	d.Accept(writer);

	printf_s("%s\n", buffer.GetString());
}