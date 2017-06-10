#pragma once
#include <vector>
#include <string>
using namespace std;
class CSerialPortSettings
{
	const vector<string> parityStrings = { "None", " ", "Even", "Odd", "Space", "Mark" };
	const vector<string> parityStringsAlt = { "NoParity", " ", "EvenParity", "OddParity", "SpaceParity", "MarkParity" };
	const vector<string> stopBitsStrings = { " ", "OneStop", "TwoStop", "OneAndHalfStop" };
	const vector<string> stopBitsStringsAlt = { " ", "1", "2", "1.5" };
	const vector<string> flowControlStrings = { "NoFlowControl", "HardwareControl", "SoftwareControl" };
	const vector<string> flowControlStringsAlt = { "None", "RTS/CTS", "XON/XOFF" };
	const vector<wstring> parityStringsW = { L"None", L" ", L"Even", L"Odd", L"Space", L"Mark" };
	const vector<wstring> parityStringsAltW = { L"NoParity", L" ", L"EvenParity", L"OddParity", L"SpaceParity", L"MarkParity" };
	const vector<wstring> stopBitsStringsW = { L" ", L"OneStop", L"TwoStop", L"OneAndHalfStop" };
	const vector<wstring> stopBitsStringsAltW = { L" ", L"1", L"2", L"1.5" };
	const vector<wstring> flowControlStringsW = { L"NoFlowControl", L"HardwareControl", L"SoftwareControl" };
	const vector<wstring> flowControlStringsAltW = { L"None", L"RTS/CTS", L"XON/XOFF" };
	const vector<int> baudRates = { 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200 };
	bool localEchoEnabled;
public:
	CSerialPortSettings();
	~CSerialPortSettings();
};

