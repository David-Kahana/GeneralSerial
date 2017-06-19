#include "stdafx.h"
#include "SerialPort.h"

//vector<CSerialPort> CSerialPort::m_ports;

CSerialPort::CSerialPort(unsigned int number, wstring friendlyName): m_portNumber(number), m_friendlyName(friendlyName)
{
}

CSerialPort::CSerialPort(unsigned int number, string friendlyName) : m_portNumber(number)
{
	CA2W ca2w(friendlyName.c_str());
	m_friendlyName = ca2w;
}

CSerialPort::~CSerialPort()
{
}

bool CSerialPort::isEqual(CSerialPort& other)
{
	return ((m_portNumber == other.m_portNumber) && (m_friendlyName.compare(other.m_friendlyName) == 0));
}

bool CSerialPort::isEqual(CSerialPort* other)
{
	return ((m_portNumber == other->m_portNumber) && (m_friendlyName.compare(other->m_friendlyName) == 0));
}

//int CSerialPort::scanPorts0()
//{
//	m_ports.clear();
//	//DWORD dwFlags = DIGCF_PRESENT | DIGCF_DEVICEINTERFACE;
//	//GUID guid = GUID_DEVINTERFACE_COMPORT;
//	DWORD dwFlags = DIGCF_PRESENT;
//	GUID guid = GUID_DEVINTERFACE_SERENUM_BUS_ENUMERATOR;
//	//Create a "device information set" for the specified GUID
//	HDEVINFO hDevInfoSet = SetupDiGetClassDevs(&guid, NULL, NULL, dwFlags);
//	if (hDevInfoSet == INVALID_HANDLE_VALUE)
//	{
//		return -1;
//	}
//	//Finally do the enumeration
//	BOOL bMoreItems = TRUE;
//	int nIndex = 0;
//	SP_DEVINFO_DATA devInfo;
//	while (bMoreItems)
//	{
//		//Enumerate the current device
//		devInfo.cbSize = sizeof(SP_DEVINFO_DATA);
//		bMoreItems = SetupDiEnumDeviceInfo(hDevInfoSet, nIndex, &devInfo);
//		if (bMoreItems)
//		{
//			//Did we find a serial port for this device
//			BOOL bAdded = FALSE;
//			//Get the registry key which stores the ports settings
//			ATL::CRegKey deviceKey;
//			deviceKey.Attach(SetupDiOpenDevRegKey(hDevInfoSet, &devInfo, DICS_FLAG_GLOBAL, 0, DIREG_DEV, KEY_QUERY_VALUE));
//			if (deviceKey != INVALID_HANDLE_VALUE)
//			{
//				int nPort = 0;
//				if (QueryRegistryPortName(deviceKey, nPort))
//				{
//					CSerialPort* newPort = new CSerialPort;
//					newPort->m_portNumber = (UINT)nPort;
//					ATL::CHeapPtr<BYTE> byFriendlyName;
//					if (QueryDeviceDescription(hDevInfoSet, devInfo, byFriendlyName))
//					{
//						newPort->m_friendlyName = reinterpret_cast<LPCTSTR>(byFriendlyName.m_pData);
//					}
//					else
//					{
//						newPort->m_friendlyName = L"";
//					}
//					m_ports.push_back(*newPort);
//					bAdded = TRUE;
//				}
//			}
//		}
//		++nIndex;
//	}
//	//Free up the "device information set" now that we are finished with it
//	SetupDiDestroyDeviceInfoList(hDevInfoSet);
//	//for (int i = 0; i < ports.size(); i++)
//	//{
//	//	_tprintf(_T("COM%u <%s>\n"), ports[i], friendlyNames[i].c_str());
//	//}
//	//Return the success indicator
//	return TRUE;
//}
//
//int CSerialPort::rescanPorts()
//{
//	int changes = 0;
//	vector<UINT> newPortNumbers;
//	vector<UINT> addPorts;
//	vector<UINT> removePorts;
//	vector<wstring> newFriendlyNames;
//	DWORD dwFlags = DIGCF_PRESENT;
//	GUID guid = GUID_DEVINTERFACE_SERENUM_BUS_ENUMERATOR;
//	//Create a "device information set" for the specified GUID
//	HDEVINFO hDevInfoSet = SetupDiGetClassDevs(&guid, NULL, NULL, dwFlags);
//	if (hDevInfoSet == INVALID_HANDLE_VALUE)
//	{
//		return -1;
//	}
//	//Finally do the enumeration
//	BOOL bMoreItems = TRUE;
//	int nIndex = 0;
//	SP_DEVINFO_DATA devInfo;
//	newPortNumbers.clear();
//	newFriendlyNames.clear();
//	addPorts.clear(); 
//	removePorts.clear();
//	while (bMoreItems)
//	{
//		//Enumerate the current device
//		devInfo.cbSize = sizeof(SP_DEVINFO_DATA);
//		bMoreItems = SetupDiEnumDeviceInfo(hDevInfoSet, nIndex, &devInfo);
//		if (bMoreItems)
//		{
//			//Did we find a serial port for this device
//			//Get the registry key which stores the ports settings
//			ATL::CRegKey deviceKey;
//			deviceKey.Attach(SetupDiOpenDevRegKey(hDevInfoSet, &devInfo, DICS_FLAG_GLOBAL, 0, DIREG_DEV, KEY_QUERY_VALUE));
//			if (deviceKey != INVALID_HANDLE_VALUE)
//			{
//				int nPort = 0;
//				if (QueryRegistryPortName(deviceKey, nPort))
//				{
//					newPortNumbers.push_back((UINT)nPort);
//					ATL::CHeapPtr<BYTE> byFriendlyName;
//					if (QueryDeviceDescription(hDevInfoSet, devInfo, byFriendlyName))
//					{
//						newFriendlyNames.push_back(reinterpret_cast<LPCTSTR>(byFriendlyName.m_pData));
//					}
//					else
//					{
//						newFriendlyNames.push_back(L"");
//					}
//				}
//			}
//		}
//		++nIndex;
//	}
//	//Free up the "device information set" now that we are finished with it
//	SetupDiDestroyDeviceInfoList(hDevInfoSet);
//	for (int i = 0; i < (int)newPortNumbers.size(); ++i)
//	{
//		bool found = false;
//		int j = -1;
//		while(!found && j < (int)m_ports.size())
//		{
//			j++;
//			found |= (newPortNumbers[i] == m_ports[j].m_portNumber);
//		}
//		if (found)
//		{
//			if (newFriendlyNames[i].compare(m_ports[j].m_friendlyName) != 0) //name has changed
//			{//update port
//				m_ports[j].m_friendlyName = newFriendlyNames[i];
//				m_ports[j].m_portSettings.clearSettables();
//				m_ports[j].getPortCapabilities();
//				changes++;
//			}
//		}
//		else
//		{ //new port
//			addPorts.push_back(i);
//		}
//	}
//	for (int i = 0; i < (int)m_ports.size(); ++i)
//	{
//		bool found = false;
//		int j = -1;
//		while (!found && j < (int)newPortNumbers.size())
//		{
//			j++;
//			found |= (m_ports[i].m_portNumber == newPortNumbers[j]);
//		}
//		if (!found)
//		{ //port to removed
//			removePorts.push_back(m_ports[i].m_portNumber);
//			changes++;
//		}
//	}
//	for (int i = 0; i < (int)removePorts.size(); ++i) //remove ports
//	{//find the port to remove	
//		vector <CSerialPort>::iterator iter;
//		for (iter = m_ports.begin(); iter != m_ports.end() && (removePorts[i] != iter->m_portNumber); iter++);
//		if (iter == m_ports.end())
//		{
//			//somthing is wrong
//		}
//		else
//		{
//			m_ports.erase(iter); //remove the port
//		}
//	}
//	//for (int i = 0; i < (int)addPorts.size(); ++i)
//	//{
//	//	vector <CSerialPort>::iterator iter;
//	//	for (iter = m_ports.begin(); iter != m_ports.end() && (newPortNumbers[addPorts[i]] >= iter->m_portNumber); iter++);
//	//	CSerialPort* newPort = new CSerialPort;
//	//	newPort->m_portNumber = (UINT)newPortNumbers[addPorts[i]];
//	//	newPort->m_friendlyName = newFriendlyNames[addPorts[i]];
//	//	m_ports.insert(iter, *newPort);
//	//	newPort->getPortCapabilities();
//	//}
//	return changes;
//}

int CSerialPort::getPorts(vector<UINT>& ports, vector<wstring>& friendlyNames)
{
	ports.clear();
	friendlyNames.clear();
	for (int i = 0; i < m_ports.size(); ++i)
	{
		ports.push_back(m_ports[i].m_portNumber);
		friendlyNames.push_back(m_ports[i].m_friendlyName);
	}
	return (int)m_ports.size();
}

int CSerialPort::getPortNumber(int index)
{
	if (index < 0 || index >= (int)m_ports.size())
	{
		return -1;
	}
	return (int)m_ports[index].m_portNumber;
}

int CSerialPort::getPortsCapabilities()
{
	for (int i = 0; i < m_ports.size(); ++i)
	{
		m_ports[i].getPortCapabilities();
	}
	return OK; //todo: return real 
}

CSerialPortSettings& CSerialPort::getPortRef(int index)
{
	if (index >= m_ports.size())
	{
		return m_ports[0].m_portSettings;
	}
	return m_ports[index].m_portSettings;
}

CSerialPortSettings* CSerialPort::getPortPtr(int index)
{
	if (index >= m_ports.size() || index < 0)
	{
		return nullptr;
	}
	return &(m_ports[index].m_portSettings);
}

int CSerialPort::getPortCapabilities()
{
	int ret = 0;
	_COMMPROP comProp;
	HANDLE hComm;
	std::wstring portName = L"\\\\.\\COM";
	portName += std::to_wstring(m_portNumber);
	//port name //Read/Write // No Sharing // No Security// Open existing port only// Non Overlapped I/O// Null for Comm Devices
	hComm = CreateFile(portName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hComm == INVALID_HANDLE_VALUE)
	{
		return -1;
	}
	ret = GetCommProperties(hComm, &comProp);
	if (ret == 0)
	{
		CloseHandle(hComm);//Closing the Serial Port
		return -2;
	}
	ret = m_portSettings.setSettables(comProp);
	CloseHandle(hComm);//Closing the Serial Port
	return ret;
}

//int CSerialPort::QueryRegistryPortName(ATL::CRegKey& deviceKey, int& nPort)
//{
//	//What will be the return value from the method (assume the worst)
//	BOOL bAdded = FALSE;
//	//Read in the name of the port
//	LPTSTR pszPortName = NULL;
//	if (RegQueryValueString(deviceKey, _T("PortName"), pszPortName))
//	{
//		//If it looks like "COMX" then
//		//add it to the array which will be returned
//		size_t nLen = _tcslen(pszPortName);
//		if (nLen > 3)
//		{
//			if ((_tcsnicmp(pszPortName, _T("COM"), 3) == 0) && IsNumeric((pszPortName + 3), FALSE))
//			{
//				//Work out the port number
//				nPort = _ttoi(pszPortName + 3);
//				bAdded = TRUE;
//			}
//		}
//		LocalFree(pszPortName);
//	}
//	return bAdded;
//}
//
//int CSerialPort::RegQueryValueString(ATL::CRegKey& key, LPCTSTR lpValueName, LPTSTR& pszValue)
//{
//	//Initialize the output parameter
//	pszValue = NULL;
//	//First query for the size of the registry value 
//	ULONG nChars = 0;
//	LSTATUS nStatus = key.QueryStringValue(lpValueName, NULL, &nChars);
//	if (nStatus != ERROR_SUCCESS)
//	{
//		SetLastError(nStatus);
//		return -1;
//	}
//	//Allocate enough bytes for the return value
//	DWORD dwAllocatedSize = ((nChars + 1) * sizeof(TCHAR)); //+1 is to allow us to NULL terminate the data if required
//	pszValue = reinterpret_cast<LPTSTR>(LocalAlloc(LMEM_FIXED, dwAllocatedSize));
//	if (pszValue == NULL)
//	{
//		return -2;
//	}
//	//We will use RegQueryValueEx directly here because ATL::CRegKey::QueryStringValue does not handle non-Null terminated data 
//	DWORD dwType = 0;
//	ULONG nBytes = dwAllocatedSize;
//	pszValue[0] = _T('\0');
//	nStatus = RegQueryValueEx(key, lpValueName, NULL, &dwType, reinterpret_cast<LPBYTE>(pszValue), &nBytes);
//	if (nStatus != ERROR_SUCCESS)
//	{
//		LocalFree(pszValue);
//		pszValue = NULL;
//		SetLastError(nStatus);
//		return -3;
//	}
//	if ((dwType != REG_SZ) && (dwType != REG_EXPAND_SZ))
//	{
//		LocalFree(pszValue);
//		pszValue = NULL;
//		SetLastError(ERROR_INVALID_DATA);
//		return -4;
//	}
//	if ((nBytes % sizeof(TCHAR)) != 0)
//	{
//		LocalFree(pszValue);
//		pszValue = NULL;
//		SetLastError(ERROR_INVALID_DATA);
//		return -5;
//	}
//	if (pszValue[(nBytes / sizeof(TCHAR)) - 1] != _T('\0'))
//	{
//		//Forcibly NULL terminate the data ourselves
//		pszValue[(nBytes / sizeof(TCHAR))] = _T('\0');
//	}
//	return TRUE;
//}
//
//int CSerialPort::QueryDeviceDescription(HDEVINFO hDevInfoSet, SP_DEVINFO_DATA& devInfo, ATL::CHeapPtr<BYTE>& byFriendlyName)
//{
//	DWORD dwType = 0;
//	DWORD dwSize = 0;
//	//Query initially to get the buffer size required
//	if (!SetupDiGetDeviceRegistryProperty(hDevInfoSet, &devInfo, SPDRP_DEVICEDESC, &dwType, NULL, 0, &dwSize))
//	{
//		if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
//		{
//			return FALSE;
//		}
//	}
//	if (!byFriendlyName.Allocate(dwSize))
//	{
//		SetLastError(ERROR_OUTOFMEMORY);
//		{
//			return FALSE;
//		}
//	}
//	return SetupDiGetDeviceRegistryProperty(hDevInfoSet, &devInfo, SPDRP_DEVICEDESC, &dwType, byFriendlyName.m_pData, dwSize, &dwSize) && (dwType == REG_SZ);
//}
//
//int CSerialPort::IsNumeric(LPCWSTR pszString, BOOL bIgnoreColon)
//{
//	size_t nLen = wcslen(pszString);
//	if (nLen == 0)
//	{
//		return FALSE;
//	}
//	//What will be the return value from this function (assume the best)
//	BOOL bNumeric = TRUE;
//	for (size_t i = 0; i < nLen && bNumeric; i++)
//	{
//		bNumeric = (iswdigit(pszString[i]) != 0);
//		if (bIgnoreColon && (pszString[i] == L':'))
//		{
//			bNumeric = TRUE;
//		}
//	}
//	return bNumeric;
//}