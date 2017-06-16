#include "stdafx.h"
#include "SerialPortSettings.h"

const vector<string> CSerialPortSettings::parityStrings = { "No parity", "Odd parity", "Even parity", "Mark parity", "Space parity" };
const vector<wstring> CSerialPortSettings::parityStringsW = { L"No parity", L"Odd parity", L"Even parity", L"Mark parity", L"Space parity" };
const vector<string> CSerialPortSettings::parityStringsAlt = { "None", "Odd", "Even", "Mark", "Space" };
const vector<wstring> CSerialPortSettings::parityStringsAltW = { L"None", L"Odd", L"Even", L"Mark", L"Space" };
const vector<string> CSerialPortSettings::stopBitsStrings = { "1 stop bit", "1.5 stop bits", "2 stop bits" };
const vector<wstring> CSerialPortSettings::stopBitsStringsW = { L"1 stop bit", L"1.5 stop bits", L"2 stop bits" };
const vector<string> CSerialPortSettings::stopBitsStringsAlt = { "1", "2", "1.5" };
const vector<wstring> CSerialPortSettings::stopBitsStringsAltW = { L"1", L"2", L"1.5" };
const vector<string> CSerialPortSettings::flowControlStrings = { "No Flow Control", "Software Control", "DTR(data - terminal - ready) / DSR(data - set - ready) supported", 
"RTS(request - to - send) / CTS(clear - to - send) supported", "RLSD(receive - line - signal - detect) supported", "Parity checking supported", "XON / XOFF flow control supported",
"Settable XON / XOFF supported", "The total(elapsed) time - outs supported", "Interval time - outs supported", "Special character support provided", "Special 16 - bit mode supported" };
const vector<wstring> CSerialPortSettings::flowControlStringsW = { L"No Flow Control", L"Software Control", L"DTR(data - terminal - ready) / DSR(data - set - ready) supported",
L"RTS(request - to - send) / CTS(clear - to - send) supported", L"RLSD(receive - line - signal - detect) supported", L"Parity checking supported", L"XON / XOFF flow control supported",
L"Settable XON / XOFF supported", L"The total(elapsed) time - outs supported", L"Interval time - outs supported", L"Special character support provided", L"Special 16 - bit mode supported" };
const vector<string> CSerialPortSettings::flowControlStringsAlt = { "None", "Software", "DTR/DSR","RTS/CTS", "RLSD", "Parity checking", "XON/XOFF","Settable XON/XOFF", "Total time-outs",
"Interval time-outs", "Special character", "Special 16-bit" };
const vector<wstring> CSerialPortSettings::flowControlStringsAltW = { L"None", L"Software", L"DTR/DSR", L"RTS/CTS", L"RLSD", L"Parity checking", L"XON/XOFF", L"Settable XON/XOFF", L"Total time-outs",
L"Interval time-outs", L"Special character", L"Special 16-bit" };
const vector<string> CSerialPortSettings::dataBitsStrings = {"5 data bits", "6 data bits", "7 data bits", "8 data bits", "16 data bits", "Special wide path through serial hardware lines"};
const vector<wstring> CSerialPortSettings::dataBitsStringsW = { L"5 data bits", L"6 data bits", L"7 data bits", L"8 data bits", L"16 data bits", L"Special wide path through serial hardware lines" };
const vector<string> CSerialPortSettings::dataBitsStringsAlt = { "5", "6", "7", "8", "16", "Special" };
const vector<wstring> CSerialPortSettings::dataBitsStringsAltW = { L"5", L"6", L"7", L"8", L"16", L"Special" };
const vector<wstring> CSerialPortSettings::baudRatesStrW = { L"BAUD_075", L"BAUD_110",L"BAUD_134_5",L"BAUD_150",L"BAUD_300",L"BAUD_600",L"BAUD_1200",
L"BAUD_1800",L"BAUD_2400",L"BAUD_4800",L"BAUD_7200",L"BAUD_9600",L"BAUD_14400",L"BAUD_19200",
L"BAUD_38400",L"BAUD_56K",L"BAUD_128K",L"BAUD_115200",L"BAUD_57600",L"BAUD_USER" };
const vector<string> CSerialPortSettings::baudRatesStr = { "BAUD_075", "BAUD_110","BAUD_134_5","BAUD_150","BAUD_300","BAUD_600","BAUD_1200",
"BAUD_1800","BAUD_2400","BAUD_4800","BAUD_7200","BAUD_9600","BAUD_14400","BAUD_19200",
"BAUD_38400","BAUD_56K","BAUD_128K","BAUD_115200","BAUD_57600","BAUD_USER" };

CSerialPortSettings::CSerialPortSettings()
{
	m_propertiesIndex[BAUD_RATE] = 11;
	m_propertiesIndex[PARITY] = 0;
	m_propertiesIndex[STOP_BITS] = 0;
	m_propertiesIndex[FLOW_CONTROL] = 0;
	m_propertiesIndex[DATA_BITS] = 4;
}

CSerialPortSettings::~CSerialPortSettings()
{
}

int CSerialPortSettings::setSettables(_COMMPROP& comProp)
{
	int ret = 0;
	ret = setSettableFlowControls(comProp.dwProvCapabilities);
	if (ret < 0)
	{
		return ret;
	}
	ret = setSettableBaudRates(comProp.dwSettableBaud);
	if (ret < 0)
	{
		return ret;
	}
	ret = setSettableDataBits(comProp.wSettableData);
	if (ret < 0)
	{
		return ret;
	}
	ret = setSettableParities(comProp.wSettableStopParity);
	if (ret < 0)
	{
		return ret;
	}
	ret = setSettableStopBits(comProp.wSettableStopParity);
	return ret;
}

void CSerialPortSettings::setPropIndex(SerialProps prop, unsigned char index)
{
	m_propertiesIndex[prop] = index;
}

unsigned char CSerialPortSettings::getPropIndex(SerialProps prop)
{
	return m_propertiesIndex[prop];
}

int CSerialPortSettings::copyUCHARVector(vector<unsigned char>& src, vector<unsigned char>& dst)
{
	dst.clear();
	for (int i = 0; i < (int)src.size(); ++i)
	{
		dst.push_back(src[i]);
	}
	return OK;
}

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

int CSerialPortSettings::setSettableBaudRates(DWORD SettableBaud)
{
	int num = 0;
	for (unsigned int mask = 0x1; mask <= 0x00040000; mask <<= 1)
	{
		if ((SettableBaud & mask) == mask)
		{
			m_settablePropIndex[BAUD_RATE].push_back(num);
		}
		num++;
	}
	if ((SettableBaud & 0x10000000) == 0x10000000)
	{
		m_settablePropIndex[BAUD_RATE].push_back(19);
	}
	return OK;
}

//#define PARITY_NONE       ((WORD)0x0100)
//#define PARITY_ODD        ((WORD)0x0200)
//#define PARITY_EVEN       ((WORD)0x0400)
//#define PARITY_MARK       ((WORD)0x0800)
//#define PARITY_SPACE      ((WORD)0x1000)

int CSerialPortSettings::setSettableParities(WORD SettableStopParity)
{
	int num = 0;
	for (unsigned short mask = 0x0100; mask <= 0x1000; mask <<= 1)
	{
		if ((SettableStopParity & mask) == mask)
		{
			m_settablePropIndex[PARITY].push_back(num);
		}
		num++;
	}
	return OK;
}

//#define STOPBITS_10       ((WORD)0x0001)
//#define STOPBITS_15       ((WORD)0x0002)
//#define STOPBITS_20       ((WORD)0x0004)

int CSerialPortSettings::setSettableStopBits(WORD SettableStopParity)
{
	int num = 0;
	for (unsigned short mask = 0x0001; mask <= 0x0004; mask <<= 1)
	{
		if ((SettableStopParity & mask) == mask)
		{
			m_settablePropIndex[STOP_BITS].push_back(num);
		}
		num++;
	}
	return OK;
}

//#define PCF_DTRDSR        ((DWORD)0x0001)
//#define PCF_RTSCTS        ((DWORD)0x0002)
//#define PCF_RLSD          ((DWORD)0x0004)
//#define PCF_PARITY_CHECK  ((DWORD)0x0008)
//#define PCF_XONXOFF       ((DWORD)0x0010)
//#define PCF_SETXCHAR      ((DWORD)0x0020)
//#define PCF_TOTALTIMEOUTS ((DWORD)0x0040)
//#define PCF_INTTIMEOUTS   ((DWORD)0x0080)
//#define PCF_SPECIALCHARS  ((DWORD)0x0100)
//#define PCF_16BITMODE     ((DWORD)0x0200)

int CSerialPortSettings::setSettableFlowControls(DWORD ProvCapabilities)
{
	m_settablePropIndex[FLOW_CONTROL].push_back(0);
	m_settablePropIndex[FLOW_CONTROL].push_back(1);
	int num = 2;
	for (unsigned int mask = 0x0001; mask <= 0x0200; mask <<= 1)
	{
		if ((ProvCapabilities & mask) == mask)
		{
			m_settablePropIndex[FLOW_CONTROL].push_back(num);
		}
		num++;
	}
	return OK;
}

//#define DATABITS_5        ((WORD)0x0001)
//#define DATABITS_6        ((WORD)0x0002)
//#define DATABITS_7        ((WORD)0x0004)
//#define DATABITS_8        ((WORD)0x0008)
//#define DATABITS_16       ((WORD)0x0010)
//#define DATABITS_16X      ((WORD)0x0020)

int CSerialPortSettings::setSettableDataBits(WORD SettableData)
{
	int num = 0;
	for (unsigned short mask = 0x0001; mask <= 0x0020; mask <<= 1)
	{
		if ((SettableData & mask) == mask)
		{
			m_settablePropIndex[DATA_BITS].push_back(num);
		}
		num++;
	}
	return OK;
}