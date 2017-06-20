#pragma once
#include <Windows.h>
#include <setupapi.h>
#include <atlbase.h>
#include <vector>
#include <string>
#include "SerialPortSettings.h"

using namespace std;

class CSerialPort
{
public:
	CSerialPort(unsigned int number, wstring friendlyName);
	CSerialPort(unsigned int number, string friendlyName);
	~CSerialPort();
	bool isEqual(CSerialPort& other);
	bool isEqual(CSerialPort* other);
	bool isSmaller(CSerialPort& other);
	bool isSmaller(CSerialPort* other);
	int getPortNumber();
	wstring getFriendlyNameW();
	int getPortCapabilities();
	CSerialPortSettings& getPortSettingsRef();
	CSerialPortSettings* getPortSettingsPtr();
private:
	UINT m_portNumber;
	wstring m_friendlyName;
	CSerialPortSettings m_portSettings;
};

