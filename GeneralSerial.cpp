#include "stdafx.h"
#include "GeneralSerial.h"

GeneralSerial::GeneralSerial(QWidget *parent)
	: QMainWindow(parent)
{
	std::vector<UINT> ports;
	std::vector<std::wstring> friendlyNames;
	std::vector<unsigned char> settableBaudratesIndex;
	ui.setupUi(this);
	CJsonSettings& s = CJsonSettings::getInstance();
	s.createDefaultConfig();
	int ret = CSerialPort::scanPorts0();
	if (ret == TRUE)
	{
		m_serialPort.getPorts(ports, friendlyNames);
	}
	m_portActionGroup = new QActionGroup(this);
	m_portActionGroup->setExclusive(true);
	for (int i = 0; i < ports.size(); ++i)
	{
		QString portName = "COM" + QString::number(ports[i]) + " " + QString::fromStdWString(friendlyNames[i]);
		QAction* act = new QAction(portName);
		act->setData(i);
		act->setCheckable(true);
		m_portActionGroup->addAction(act);
		ui.menuPort->addAction(act);
		_tprintf(_T("COM%u <%s>\n"), ports[i], friendlyNames[i].c_str());
	}
	m_baudActionGroup = new QActionGroup(this);
	for (int i = 0; i < CSerialPortSettings::baudRatesStrW.size(); ++i)
	{
		QAction* act = new QAction(QString::fromStdWString(CSerialPortSettings::baudRatesStrW[i]));
		act->setData(i);
		act->setCheckable(true);
		m_baudActionGroup->addAction(act);
	}
	ret = CSerialPort::getPortsCapabilities();


	ret = CSerialPort::getSettableBaudRates(0, settableBaudratesIndex);
	for (int i = 0; i < settableBaudratesIndex.size(); ++i)
	{
		ui.menuBaudRate->addAction(m_baudActionGroup->actions().at(settableBaudratesIndex[i]));
	}
	
	connect(ui.menuPort, &QMenu::triggered, this, &GeneralSerial::changePort);
	connect(ui.menuBaudRate, &QMenu::triggered, this, &GeneralSerial::changeBaud);
}

void GeneralSerial::changePort(QAction* act)
{
	int newPort = act->data().toInt();
	//wprintf_s(L"port %d: COM%d\n", newPort, m_serialPort.getPortNumber(newPort));
	std::vector<unsigned char> settableBaudratesIndex;
	if (m_currentPortIndex != newPort)
	{
		m_currentPortIndex = newPort;
		ui.menuBaudRate->clear();
		if (m_baudActionGroup->checkedAction() != NULL)
		{
			m_baudActionGroup->checkedAction()->setChecked(false);
		}
		CSerialPort::getSettableBaudRates(newPort, settableBaudratesIndex);
		for (int i = 0; i < settableBaudratesIndex.size(); ++i)
		{
			ui.menuBaudRate->addAction(m_baudActionGroup->actions().at(settableBaudratesIndex[i]));
		}
	}
	//wprintf_s(L"port: %s\n", act->text().toStdWString().c_str());
}

void GeneralSerial::changeBaud(QAction* act)
{
	wprintf_s(L"baud: %s\n", act->text().toStdWString().c_str());
}
