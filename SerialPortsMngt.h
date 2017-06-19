#pragma once
#include "SerialPort.h"

class CSerialPortsMngt
{
public:
	CSerialPortsMngt();
	~CSerialPortsMngt();
	int scanPorts();
	static int scanForAllPorts(vector<CSerialPort*>& newPorts);
private:
	static int QueryRegistryPortName(ATL::CRegKey& deviceKey, int& nPort);
	static int RegQueryValueString(ATL::CRegKey& key, LPCTSTR lpValueName, LPTSTR& pszValue);
	static int QueryDeviceDescription(HDEVINFO hDevInfoSet, SP_DEVINFO_DATA& devInfo, ATL::CHeapPtr<BYTE>& byFriendlyName);
	static int IsNumeric(LPCWSTR pszString, BOOL bIgnoreColon);
	int findInVect(CSerialPort* port, vector<CSerialPort*> portVect);
private:
	vector<CSerialPort*> m_currentPorts;
	vector<CSerialPort*> m_removedPorts;
};

