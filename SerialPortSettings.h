#pragma once
#include <Windows.h>
#include <setupapi.h>
#include <atlbase.h>
#include <vector>
#include <string>

#define OK 1

using namespace std;
class CSerialPortSettings
{
public:
	static const vector<string> parityStrings;
	static const vector<wstring> parityStringsW;
	static const vector<string> parityStringsAlt;
	static const vector<wstring> parityStringsAltW;
	static const vector<string> stopBitsStrings;
	static const vector<wstring> stopBitsStringsW;
	static const vector<string> stopBitsStringsAlt;
	static const vector<wstring> stopBitsStringsAltW;
	static const vector<string> flowControlStrings;
	static const vector<string> flowControlStringsAlt;
	static const vector<wstring> flowControlStringsW;
	static const vector<wstring> flowControlStringsAltW;
	static const vector<wstring> baudRatesStrW;
	static const vector<string> baudRatesStr; 
	static const vector<string> dataBitsStrings;
	static const vector<wstring> dataBitsStringsW;
	static const vector<string> dataBitsStringsAlt;
	static const vector<wstring> dataBitsStringsAltW;
	const vector<int> baudRates = { 75, 110, 135, 150, 300, 600, 1200, 1800, 2400, 4800, 7200, 9600, 14400, 19200, 38400, 56000, 128000, 115200, 57600, -1 };
	bool localEchoEnabled;
public:
	CSerialPortSettings();
	~CSerialPortSettings();
	int setSettables(_COMMPROP& comProp);
	const vector<unsigned char>& settableBaud() const { return m_settableBaudRatesIndex; }
	const vector<unsigned char>& settableParity() const { return m_settableParitiesIndex; }
	const vector<unsigned char>& settableStop() const { return m_settableStopBitsIndex; }
	const vector<unsigned char>& settableFlow() const { return m_settableFlowControlsIndex; }
	const vector<unsigned char>& settableDataBits() const { return m_settableDataBitsIndex; }
	//int getSettableBaudRates(vector<unsigned char>& settableBaud);
	//int getSettableParities(vector<unsigned char>& settableParity);
	//int getSettableStopBits(vector<unsigned char>& settableStop);
	//int getSettableFlowControls(vector<unsigned char>& settableFlow);
	//int getSettableDataBits(vector<unsigned char>& settableDataBits);
private:
	static int copyUCHARVector(vector<unsigned char>& src, vector<unsigned char>& dst);
	int setSettableBaudRates(DWORD SettableBaud);
	int setSettableParities(WORD SettableStopParity);
	int setSettableStopBits(WORD SettableStopParity);
	int setSettableFlowControls(DWORD ProvCapabilities);
	int setSettableDataBits(WORD SettableData);
private:
	vector<unsigned char> m_settableBaudRatesIndex;
	vector<unsigned char> m_settableParitiesIndex;
	vector<unsigned char> m_settableStopBitsIndex;
	vector<unsigned char> m_settableFlowControlsIndex;
	vector<unsigned char> m_settableDataBitsIndex;
	
};

