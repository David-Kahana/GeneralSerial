#include "stdafx.h"
#include "GeneralSerial.h"

GeneralSerial::GeneralSerial(QWidget *parent)
	: QMainWindow(parent)
{
	std::vector<UINT> ports;
	std::vector<std::wstring> friendlyNames;
	ui.setupUi(this);
	CJsonSettings& s = CJsonSettings::getInstance();
	s.createDefaultConfig();
	int ret = CSerialPort::scanPorts0();
	if (ret == TRUE)
	{
		CSerialPort::getPorts(ports, friendlyNames);
	}
	ret = createMenus();
	m_portActionGroup = new QActionGroup(this);
	m_portActionGroup->setExclusive(true);
	for (int i = 0; i < ports.size(); ++i)
	{
		QString portName = "COM" + QString::number(ports[i]) + " " + QString::fromStdWString(friendlyNames[i]);
		QAction* act = new QAction(portName);
		act->setData(i);
		act->setCheckable(true);
		m_portActionGroup->addAction(act);
		portMenu->addAction(act);
		//ui.menuPort->addAction(act);
		_tprintf(_T("COM%u <%s>\n"), ports[i], friendlyNames[i].c_str());
	}
	ret = createActionGroups();
	ret = CSerialPort::getPortsCapabilities();
	ret = getSetabbles();
	
	//connect(ui.menuPort, &QMenu::triggered, this, &GeneralSerial::changePort);
	//connect(portMenu, &QMenu::triggered, this, &GeneralSerial::changePort);
	//connect(ui.menuBaudRate, &QMenu::triggered, this, &GeneralSerial::changeBaud);
	//connect(baudMenu, &QMenu::triggered, this, &GeneralSerial::changeBaud);
}

int GeneralSerial::createMenus()
{
	portMenu = new QMenu("Port", this);
	ui.menuBar->addMenu(portMenu);
	connect(portMenu, &QMenu::triggered, this, &GeneralSerial::changePort);
	baudMenu = new QMenu("BaudRate", this);
	ui.menuBar->addMenu(baudMenu);
	connect(baudMenu, &QMenu::triggered, this, &GeneralSerial::changeBaud);
	parityMenu = new QMenu("Parity", this);
	ui.menuBar->addMenu(parityMenu);
	connect(parityMenu, &QMenu::triggered, this, &GeneralSerial::changeParity);
	stopMenu = new QMenu("StopBits", this);
	ui.menuBar->addMenu(stopMenu);
	connect(stopMenu, &QMenu::triggered, this, &GeneralSerial::changeStopBits);
	flowMenu = new QMenu("Flow control", this);
	ui.menuBar->addMenu(flowMenu);
	connect(flowMenu, &QMenu::triggered, this, &GeneralSerial::changeFlowControl);
	dataMenu = new QMenu("Data Bits", this);
	ui.menuBar->addMenu(dataMenu);
	connect(dataMenu, &QMenu::triggered, this, &GeneralSerial::changeDataBits);
	return OK;
}

int GeneralSerial::createActionGroups()
{
	//m_baudActionGroup = new QActionGroup(this);
	//for (int i = 0; i < CSerialPortSettings::baudRatesStrW.size(); ++i)
	//{
	//	QAction* act = new QAction(QString::fromStdWString(CSerialPortSettings::baudRatesStrW[i]));
	//	act->setData(i);
	//	act->setCheckable(true);
	//	m_baudActionGroup->addAction(act);
	//}
	m_baudActionGroup = makeActionGroup(CSerialPortSettings::baudRatesStrW);
	//m_parityActionGroup = new QActionGroup(this);
	//for (int i = 0; i < CSerialPortSettings::parityStringsAltW.size(); ++i)
	//{
	//	QAction* act = new QAction(QString::fromStdWString(CSerialPortSettings::parityStringsAltW[i]));
	//	act->setData(i);
	//	act->setCheckable(true);
	//	m_parityActionGroup->addAction(act);
	//}
	m_parityActionGroup = makeActionGroup(CSerialPortSettings::parityStringsAltW);
	m_stopActionGroup = makeActionGroup(CSerialPortSettings::stopBitsStringsAltW);
	m_flowActionGroup = makeActionGroup(CSerialPortSettings::flowControlStringsAltW);
	m_dataActionGroup = makeActionGroup(CSerialPortSettings::dataBitsStringsAltW);
	return OK;
}

QActionGroup* GeneralSerial::makeActionGroup(const std::vector<std::wstring>& strs)
{
	QActionGroup* ag = new QActionGroup(this);
	for (int i = 0; i < strs.size(); ++i)
	{
		QAction* act = new QAction(QString::fromStdWString(strs[i]));
		act->setData(i);
		act->setCheckable(true);
		ag->addAction(act);
	}
	return ag;
}

int GeneralSerial::getSetabbles()
{
	CSerialPortSettings* port = CSerialPort::getPortPtr(m_currentPortIndex);
	if (port == nullptr)
	{
		return -1;
	}
	for (int i = 0; i < port->settableBaud().size(); ++i)
	{
		//ui.menuBaudRate->addAction(m_baudActionGroup->actions().at(port->settableBaud()[i]));
		baudMenu->addAction(m_baudActionGroup->actions().at(port->settableBaud()[i]));
	}
	//for (int i = 0; i < port->settableParity().size(); ++i)
	//{
	//	ui.menuBaudRate->addAction(m_parityActionGroup->actions().at(port->settableParity()[i]));
	//}
	//ret = CSerialPort::getSettableParities(m_currentPortIndex, settableBaudratesIndex);
	//for (int i = 0; i < settableBaudratesIndex.size(); ++i)
	//{
	//	ui.menuBaudRate->addAction(m_baudActionGroup->actions().at(settableBaudratesIndex[i]));
	//}
	return OK;
}

void GeneralSerial::changePort(QAction* act)
{
	int newPort = act->data().toInt();
	//wprintf_s(L"port %d: COM%d\n", newPort, m_serialPort.getPortNumber(newPort));
	std::vector<unsigned char> settableBaudratesIndex;
	if (m_currentPortIndex != newPort)
	{
		m_currentPortIndex = newPort;
		//ui.menuBaudRate->clear();
		baudMenu->clear();
		if (m_baudActionGroup->checkedAction() != NULL)
		{
			m_baudActionGroup->checkedAction()->setChecked(false);
		}
		CSerialPort::getSettableBaudRates(newPort, settableBaudratesIndex);
		for (int i = 0; i < settableBaudratesIndex.size(); ++i)
		{
			//ui.menuBaudRate->addAction(m_baudActionGroup->actions().at(settableBaudratesIndex[i]));
			baudMenu->addAction(m_baudActionGroup->actions().at(settableBaudratesIndex[i]));
		}
	}
	//wprintf_s(L"port: %s\n", act->text().toStdWString().c_str());
}

void GeneralSerial::changeBaud(QAction* act)
{
	wprintf_s(L"baud: %s\n", act->text().toStdWString().c_str());
}

void GeneralSerial::changeParity(QAction* act)
{

}

void GeneralSerial::changeStopBits(QAction* act)
{

}

void GeneralSerial::changeFlowControl(QAction* act)
{

}

void GeneralSerial::changeDataBits(QAction* act)
{

}
