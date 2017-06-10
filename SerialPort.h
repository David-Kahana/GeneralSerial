#pragma once
#include <Windows.h>
#include <setupapi.h>
#include <atlbase.h>
#include <vector>
#include <string>

class CSerialPort
{
public:
	CSerialPort();
	~CSerialPort();
	int scanPorts();
	int getPorts(std::vector<UINT>& ports, std::vector<std::wstring>& friendlyNames);
	private:
	int QueryRegistryPortName(ATL::CRegKey& deviceKey, int& nPort);
	int RegQueryValueString(ATL::CRegKey& key, LPCTSTR lpValueName, LPTSTR& pszValue);
	int QueryDeviceDescription(HDEVINFO hDevInfoSet, SP_DEVINFO_DATA& devInfo, ATL::CHeapPtr<BYTE>& byFriendlyName);
	int IsNumeric(LPCWSTR pszString, BOOL bIgnoreColon);
private:
	std::vector<UINT> m_ports;
	std::vector<std::wstring> m_friendlyNames;
};

