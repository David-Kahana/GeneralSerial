#include "stdafx.h"
#include "SerialPortSettings.h"

const vector<wstring> CSerialPortSettings::baudRatesStrW = { L"BAUD_075", L"BAUD_110",L"BAUD_134_5",L"BAUD_150",L"BAUD_300",L"BAUD_600",L"BAUD_1200",
L"BAUD_1800",L"BAUD_2400",L"BAUD_4800",L"BAUD_7200",L"BAUD_9600",L"BAUD_14400",L"BAUD_19200",
L"BAUD_38400",L"BAUD_56K",L"BAUD_128K",L"BAUD_115200",L"BAUD_57600",L"BAUD_USER" };
const vector<string> CSerialPortSettings::baudRatesStr = { "BAUD_075", "BAUD_110","BAUD_134_5","BAUD_150","BAUD_300","BAUD_600","BAUD_1200",
"BAUD_1800","BAUD_2400","BAUD_4800","BAUD_7200","BAUD_9600","BAUD_14400","BAUD_19200",
"BAUD_38400","BAUD_56K","BAUD_128K","BAUD_115200","BAUD_57600","BAUD_USER" };

CSerialPortSettings::CSerialPortSettings()
{
}


CSerialPortSettings::~CSerialPortSettings()
{
}
