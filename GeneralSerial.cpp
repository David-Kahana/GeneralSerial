#include "stdafx.h"
#include "GeneralSerial.h"
#include "SerialPort.h"

GeneralSerial::GeneralSerial(QWidget *parent)
	: QMainWindow(parent)
{
	std::vector<UINT> ports;
	std::vector<std::wstring> friendlyNames;
	ui.setupUi(this);
	CJsonSettings& s = CJsonSettings::getInstance();
	s.createDefaultConfig();
	CSerialPort sp;
	int ret = sp.scanPorts();
	if (ret == TRUE)
	{
		sp.getPorts(ports, friendlyNames);
	}
	for (int i = 0; i < ports.size(); i++)
	{
		_tprintf(_T("COM%u <%s>\n"), ports[i], friendlyNames[i].c_str());
	}
}
