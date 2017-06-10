#include "stdafx.h"
#include "GeneralSerial.h"


GeneralSerial::GeneralSerial(QWidget *parent)
	: QMainWindow(parent)
{
	std::vector<UINT> ports;
	std::vector<std::wstring> friendlyNames;
	std::vector<std::wstring> settableBaudrates;
	ui.setupUi(this);
	CJsonSettings& s = CJsonSettings::getInstance();
	s.createDefaultConfig();
	int ret = sp.scanPorts();
	if (ret == TRUE)
	{
		sp.getPorts(ports, friendlyNames);
	}
	for (int i = 0; i < ports.size(); ++i)
	{
		QString portName = "COM" + QString::number(ports[i]) + " " + QString::fromStdWString(friendlyNames[i]);
		QAction* act = new QAction(portName);
		act->setData(i);
		ui.menuPort->addAction(act);
		_tprintf(_T("COM%u <%s>\n"), ports[i], friendlyNames[i].c_str());
	}
	connect(ui.menuPort, &QMenu::triggered, this, &GeneralSerial::changePort);
	sp.getSettableBaudrate(0, settableBaudrates);
	for (int i = 0; i < settableBaudrates.size(); ++i)
	{
		ui.menuBaudRate->addAction(QString::fromStdWString(settableBaudrates[i]));
	}
	connect(ui.menuBaudRate, &QMenu::triggered, this, &GeneralSerial::changeBaud);
}

void GeneralSerial::changePort(QAction* act)
{
	wprintf_s(L"port n: %d\n", act->data().toInt());
	int newPort = act->data().toInt();
	std::vector<std::wstring> settableBaudrates;
	if (m_currentPort != newPort)
	{
		ui.menuBaudRate->clear();
		sp.getSettableBaudrate(newPort, settableBaudrates);
		for (int i = 0; i < settableBaudrates.size(); ++i)
		{
			ui.menuBaudRate->addAction(QString::fromStdWString(settableBaudrates[i]));
		}
	}
	//wprintf_s(L"port: %s\n", act->text().toStdWString().c_str());
}

void GeneralSerial::changeBaud(QAction* act)
{
	wprintf_s(L"baud: %s\n", act->text().toStdWString().c_str());
}
