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
	CSerialPort();
	~CSerialPort();
	//CSerialPort(const CSerialPort&) = default;
	//CSerialPort& operator=(const CSerialPort&) 
	//{

	//};
	static int scanPorts0();
	static int rescanPorts();
	static int getPorts(vector<UINT>& ports, vector<wstring>& friendlyNames);
	static int getPortNumber(int index);
	static int getPortsCapabilities();
	static CSerialPortSettings& getPortRef(int index);
	static CSerialPortSettings* getPortPtr(int index);
private:
	int getPortCapabilities();
	static int QueryRegistryPortName(ATL::CRegKey& deviceKey, int& nPort);
	static int RegQueryValueString(ATL::CRegKey& key, LPCTSTR lpValueName, LPTSTR& pszValue);
	static int QueryDeviceDescription(HDEVINFO hDevInfoSet, SP_DEVINFO_DATA& devInfo, ATL::CHeapPtr<BYTE>& byFriendlyName);
	static int IsNumeric(LPCWSTR pszString, BOOL bIgnoreColon);
private:
	static vector<CSerialPort> m_ports;
	UINT m_portNumber;
	wstring m_friendlyName;
	CSerialPortSettings m_portSettings;
};

