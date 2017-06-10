#pragma once
#include <Windows.h>
#include <setupapi.h>
#include <atlbase.h>
#include <vector>
#include <string>


//#define BAUD_075          ((DWORD)0x00000001)
//#define BAUD_110          ((DWORD)0x00000002)
//#define BAUD_134_5        ((DWORD)0x00000004)
//#define BAUD_150          ((DWORD)0x00000008)
//#define BAUD_300          ((DWORD)0x00000010)
//#define BAUD_600          ((DWORD)0x00000020)
//#define BAUD_1200         ((DWORD)0x00000040)
//#define BAUD_1800         ((DWORD)0x00000080)
//#define BAUD_2400         ((DWORD)0x00000100)
//#define BAUD_4800         ((DWORD)0x00000200)
//#define BAUD_7200         ((DWORD)0x00000400)
//#define BAUD_9600         ((DWORD)0x00000800)
//#define BAUD_14400        ((DWORD)0x00001000)
//#define BAUD_19200        ((DWORD)0x00002000)
//#define BAUD_38400        ((DWORD)0x00004000)
//#define BAUD_56K          ((DWORD)0x00008000)
//#define BAUD_128K         ((DWORD)0x00010000)
//#define BAUD_115200       ((DWORD)0x00020000)
//#define BAUD_57600        ((DWORD)0x00040000)
//#define BAUD_USER         ((DWORD)0x10000000)




class CSerialPort
{
public:
	const std::vector<std::wstring> baudRatesStrW = { L"BAUD_075", L"BAUD_110",L"BAUD_134_5",L"BAUD_150",L"BAUD_300",L"BAUD_600",L"BAUD_1200",
												L"BAUD_1800",L"BAUD_2400",L"BAUD_4800",L"BAUD_7200",L"BAUD_9600",L"BAUD_14400",L"BAUD_19200",
												L"BAUD_38400",L"BAUD_56K",L"BAUD_128K",L"BAUD_115200",L"BAUD_57600",L"BAUD_USER"};
	const std::vector<std::string> baudRatesStr = { "BAUD_075", "BAUD_110","BAUD_134_5","BAUD_150","BAUD_300","BAUD_600","BAUD_1200",
		"BAUD_1800","BAUD_2400","BAUD_4800","BAUD_7200","BAUD_9600","BAUD_14400","BAUD_19200",
		"BAUD_38400","BAUD_56K","BAUD_128K","BAUD_115200","BAUD_57600","BAUD_USER" };
public:
	CSerialPort();
	~CSerialPort();
	int scanPorts();
	int getPorts(std::vector<UINT>& ports, std::vector<std::wstring>& friendlyNames);
	int getSettableBaudrate(int portIndex, std::vector<std::wstring>& settableBaudrates);
private:
	int QueryRegistryPortName(ATL::CRegKey& deviceKey, int& nPort);
	int RegQueryValueString(ATL::CRegKey& key, LPCTSTR lpValueName, LPTSTR& pszValue);
	int QueryDeviceDescription(HDEVINFO hDevInfoSet, SP_DEVINFO_DATA& devInfo, ATL::CHeapPtr<BYTE>& byFriendlyName);
	int IsNumeric(LPCWSTR pszString, BOOL bIgnoreColon);
private:
	std::vector<UINT> m_ports;
	std::vector<std::wstring> m_friendlyNames;
};

