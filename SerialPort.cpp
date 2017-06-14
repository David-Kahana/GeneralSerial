#include "stdafx.h"
#include "SerialPort.h"

CSerialPort::CSerialPort()
{
}

CSerialPort::~CSerialPort()
{
}

int CSerialPort::scanPorts()
{
	m_ports.clear();
	m_friendlyNames.clear();
	//DWORD dwFlags = DIGCF_PRESENT | DIGCF_DEVICEINTERFACE;
	//GUID guid = GUID_DEVINTERFACE_COMPORT;
	DWORD dwFlags = DIGCF_PRESENT;
	GUID guid = GUID_DEVINTERFACE_SERENUM_BUS_ENUMERATOR;
	//Create a "device information set" for the specified GUID
	HDEVINFO hDevInfoSet = SetupDiGetClassDevs(&guid, NULL, NULL, dwFlags);
	if (hDevInfoSet == INVALID_HANDLE_VALUE)
	{
		return -1;
	}
	//Finally do the enumeration
	BOOL bMoreItems = TRUE;
	int nIndex = 0;
	SP_DEVINFO_DATA devInfo;
	while (bMoreItems)
	{
		//Enumerate the current device
		devInfo.cbSize = sizeof(SP_DEVINFO_DATA);
		bMoreItems = SetupDiEnumDeviceInfo(hDevInfoSet, nIndex, &devInfo);
		if (bMoreItems)
		{
			//Did we find a serial port for this device
			BOOL bAdded = FALSE;
			//Get the registry key which stores the ports settings
			ATL::CRegKey deviceKey;
			deviceKey.Attach(SetupDiOpenDevRegKey(hDevInfoSet, &devInfo, DICS_FLAG_GLOBAL, 0, DIREG_DEV, KEY_QUERY_VALUE));
			if (deviceKey != INVALID_HANDLE_VALUE)
			{
				int nPort = 0;
				if (QueryRegistryPortName(deviceKey, nPort))
				{
					m_ports.push_back(nPort);
					bAdded = TRUE;
				}
			}
			//If the port was a serial port, then also try to get its friendly name
			if (bAdded)
			{
				ATL::CHeapPtr<BYTE> byFriendlyName;
				if (QueryDeviceDescription(hDevInfoSet, devInfo, byFriendlyName))
				{
					m_friendlyNames.push_back(reinterpret_cast<LPCTSTR>(byFriendlyName.m_pData));
				}
				else
				{
					m_friendlyNames.push_back(_T(""));
				}
			}
		}
		++nIndex;
	}
	//Free up the "device information set" now that we are finished with it
	SetupDiDestroyDeviceInfoList(hDevInfoSet);
	//for (int i = 0; i < ports.size(); i++)
	//{
	//	_tprintf(_T("COM%u <%s>\n"), ports[i], friendlyNames[i].c_str());
	//}
	//Return the success indicator
	return TRUE;
}

int CSerialPort::getPorts(std::vector<UINT>& ports, std::vector<std::wstring>& friendlyNames)
{
	ports.clear();
	friendlyNames.clear();
	for (int i = 0; i < m_ports.size(); ++i)
	{
		ports.push_back(m_ports[i]);
		friendlyNames.push_back(m_friendlyNames[i]);
	}
	return (int)m_ports.size();
}

int CSerialPort::getPortNumber(int index)
{
	if (index < 0 || index >= (int)m_ports.size())
	{
		return -1;
	}
	return (int)m_ports[index];
}

int CSerialPort::getSettableBaudrate(int portIndex, std::vector<std::wstring>& settableBaudrates)
{
	int number = 0;
	settableBaudrates.clear();
	_COMMPROP comProp;
	HANDLE hComm;
	if (m_ports.size() <= portIndex)
	{
		return -1;
	}
	std::wstring portName = L"\\\\.\\COM";
	portName += std::to_wstring(m_ports[portIndex]);
    //port name //Read/Write // No Sharing // No Security// Open existing port only// Non Overlapped I/O// Null for Comm Devices
	hComm = CreateFile(portName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);        
	if (hComm == INVALID_HANDLE_VALUE)
	{
		return -2;
	}
	//LPCOMMPROP lpCommProp;
	BOOL ret = GetCommProperties(hComm, &comProp);
	//DWORD br = comProp.dwMaxBaud;
	DWORD br = comProp.dwSettableBaud;
	std::wstring brStr = L"";
	DWORD mask = 1;
	for (int i = 0; i < 19; ++i)
	{
		mask = 1 << i;
		if ((br & mask) == mask)
		{
			brStr += CSerialPortSettings::baudRatesStrW[i] + L",";
			settableBaudrates.push_back(CSerialPortSettings::baudRatesStrW[i]);
			number++;
		}
		mask = 1<<i;
	}
	//wprintf_s(L"settable baudrates for port COM%d: %s\n", m_ports[portIndex], brStr.c_str());
	CloseHandle(hComm);//Closing the Serial Port
	return number;
}

int CSerialPort::getSettableBaudrateIndex(int portIndex, std::vector<int>& settableBaudratesIndex)
{
	int number = 0;
	settableBaudratesIndex.clear();
	_COMMPROP comProp;
	HANDLE hComm;
	if (m_ports.size() <= portIndex)
	{
		return -1;
	}
	std::wstring portName = L"\\\\.\\COM";
	portName += std::to_wstring(m_ports[portIndex]);
	//port name //Read/Write // No Sharing // No Security// Open existing port only// Non Overlapped I/O// Null for Comm Devices
	hComm = CreateFile(portName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hComm == INVALID_HANDLE_VALUE)
	{
		return -2;
	}
	//LPCOMMPROP lpCommProp;
	BOOL ret = GetCommProperties(hComm, &comProp);
	//DWORD br = comProp.dwMaxBaud;
	DWORD br = comProp.dwSettableBaud;
	std::wstring brStr = L"";
	DWORD mask = 1;
	for (int i = 0; i < 19; ++i)
	{
		mask = 1 << i;
		if ((br & mask) == mask)
		{
			brStr += CSerialPortSettings::baudRatesStrW[i] + L",";
			settableBaudratesIndex.push_back(i);
			number++;
		}
		mask = 1 << i;
	}
	//wprintf_s(L"settable baudrates for port COM%d: %s\n", m_ports[portIndex], brStr.c_str());
	CloseHandle(hComm);//Closing the Serial Port
	return number;
}

int CSerialPort::QueryRegistryPortName(ATL::CRegKey& deviceKey, int& nPort)
{
	//What will be the return value from the method (assume the worst)
	BOOL bAdded = FALSE;
	//Read in the name of the port
	LPTSTR pszPortName = NULL;
	if (RegQueryValueString(deviceKey, _T("PortName"), pszPortName))
	{
		//If it looks like "COMX" then
		//add it to the array which will be returned
		size_t nLen = _tcslen(pszPortName);
		if (nLen > 3)
		{
			if ((_tcsnicmp(pszPortName, _T("COM"), 3) == 0) && IsNumeric((pszPortName + 3), FALSE))
			{
				//Work out the port number
				nPort = _ttoi(pszPortName + 3);
				bAdded = TRUE;
			}
		}
		LocalFree(pszPortName);
	}
	return bAdded;
}

int CSerialPort::RegQueryValueString(ATL::CRegKey& key, LPCTSTR lpValueName, LPTSTR& pszValue)
{
	//Initialize the output parameter
	pszValue = NULL;
	//First query for the size of the registry value 
	ULONG nChars = 0;
	LSTATUS nStatus = key.QueryStringValue(lpValueName, NULL, &nChars);
	if (nStatus != ERROR_SUCCESS)
	{
		SetLastError(nStatus);
		return -1;
	}
	//Allocate enough bytes for the return value
	DWORD dwAllocatedSize = ((nChars + 1) * sizeof(TCHAR)); //+1 is to allow us to NULL terminate the data if required
	pszValue = reinterpret_cast<LPTSTR>(LocalAlloc(LMEM_FIXED, dwAllocatedSize));
	if (pszValue == NULL)
	{
		return -2;
	}
	//We will use RegQueryValueEx directly here because ATL::CRegKey::QueryStringValue does not handle non-Null terminated data 
	DWORD dwType = 0;
	ULONG nBytes = dwAllocatedSize;
	pszValue[0] = _T('\0');
	nStatus = RegQueryValueEx(key, lpValueName, NULL, &dwType, reinterpret_cast<LPBYTE>(pszValue), &nBytes);
	if (nStatus != ERROR_SUCCESS)
	{
		LocalFree(pszValue);
		pszValue = NULL;
		SetLastError(nStatus);
		return -3;
	}
	if ((dwType != REG_SZ) && (dwType != REG_EXPAND_SZ))
	{
		LocalFree(pszValue);
		pszValue = NULL;
		SetLastError(ERROR_INVALID_DATA);
		return -4;
	}
	if ((nBytes % sizeof(TCHAR)) != 0)
	{
		LocalFree(pszValue);
		pszValue = NULL;
		SetLastError(ERROR_INVALID_DATA);
		return -5;
	}
	if (pszValue[(nBytes / sizeof(TCHAR)) - 1] != _T('\0'))
	{
		//Forcibly NULL terminate the data ourselves
		pszValue[(nBytes / sizeof(TCHAR))] = _T('\0');
	}
	return TRUE;
}

int CSerialPort::QueryDeviceDescription(HDEVINFO hDevInfoSet, SP_DEVINFO_DATA& devInfo, ATL::CHeapPtr<BYTE>& byFriendlyName)
{
	DWORD dwType = 0;
	DWORD dwSize = 0;
	//Query initially to get the buffer size required
	if (!SetupDiGetDeviceRegistryProperty(hDevInfoSet, &devInfo, SPDRP_DEVICEDESC, &dwType, NULL, 0, &dwSize))
	{
		if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
		{
			return FALSE;
		}
	}
	if (!byFriendlyName.Allocate(dwSize))
	{
		SetLastError(ERROR_OUTOFMEMORY);
		{
			return FALSE;
		}
	}
	return SetupDiGetDeviceRegistryProperty(hDevInfoSet, &devInfo, SPDRP_DEVICEDESC, &dwType, byFriendlyName.m_pData, dwSize, &dwSize) && (dwType == REG_SZ);
}

int CSerialPort::IsNumeric(LPCWSTR pszString, BOOL bIgnoreColon)
{
	size_t nLen = wcslen(pszString);
	if (nLen == 0)
	{
		return FALSE;
	}
	//What will be the return value from this function (assume the best)
	BOOL bNumeric = TRUE;
	for (size_t i = 0; i < nLen && bNumeric; i++)
	{
		bNumeric = (iswdigit(pszString[i]) != 0);
		if (bIgnoreColon && (pszString[i] == L':'))
		{
			bNumeric = TRUE;
		}
	}
	return bNumeric;
}