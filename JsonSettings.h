#pragma once
#include <Windows.h>
#include "..\rapidjson\document.h"
#include "..\rapidjson\writer.h"
#include "..\rapidjson\stringbuffer.h"

using namespace std;
using namespace rapidjson;

class CJsonSettings
{
public:
	static CJsonSettings& getInstance()
	{
		static CJsonSettings instance; // Guaranteed to be destroyed.
									   // Instantiated on first use.
		return instance;
	}
public:
	~CJsonSettings();
	//void saveConfig(wstring configFileName);
	//int LoadConfig(wstring configFileName);
	void createDefaultConfig();
private:
	CJsonSettings();
};

