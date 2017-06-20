#include "stdafx.h"
#include "SerialPort.h"

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

bool CSerialPort::isSmaller(CSerialPort& other)
{
	return (m_portNumber < other.m_portNumber);
}

bool CSerialPort::isSmaller(CSerialPort* other)
{
	return (m_portNumber < other->m_portNumber);
}

int CSerialPort::getPortNumber()
{
	return (int)m_portNumber;
}

wstring CSerialPort::getFriendlyNameW()
{
	return m_friendlyName;
}

CSerialPortSettings& CSerialPort::getPortSettingsRef()
{
	return m_portSettings;
}

CSerialPortSettings* CSerialPort::getPortSettingsPtr()
{
	return &(m_portSettings);
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
