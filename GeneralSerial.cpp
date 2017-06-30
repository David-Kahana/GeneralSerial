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
	int ret = m_ports.scanPorts();
	if (ret == OK)
	{
		ret = m_ports.getPortsNames(ports, friendlyNames);
	}
	ret = createMenus();
	m_portActionGroup = new QActionGroup(this);
	m_portActionGroup->setExclusive(true);
	for (int i = 0; i < ports.size(); ++i)
	{
		QString portName = "COM" + QString::number(ports[i]) + " " + QString::fromStdWString(friendlyNames[i]);
		QAction* act = new QAction(portName);
		act->setData(ports[i]);
		act->setCheckable(true);
		m_portActionGroup->addAction(act);
		portMenu->addAction(act);
		_tprintf(_T("COM%u <%s>\n"), ports[i], friendlyNames[i].c_str());
	}
	ret = createActionGroups();
	m_currentPortnumber = ports[0];
	ret = getSetabbles();
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(200);

	CSerialPort* prt = m_ports.getPortByNumber(1);
	prt->openPort();
	prt->getPortSettings();
	prt->closePort();
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
	m_baudActionGroup = makeActionGroup(CSerialPortSettings::baudRatesStrW);
	m_parityActionGroup = makeActionGroup(CSerialPortSettings::parityStringsAltW);
	m_stopActionGroup = makeActionGroup(CSerialPortSettings::stopBitsStringsAltW);
	m_flowActionGroup = makeActionGroup(CSerialPortSettings::flowControlDCBStringsW);
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
	CSerialPort* p = m_ports.getPortByNumber(m_currentPortnumber);
	if (p == nullptr)
	{
		return -1;
	}
	CSerialPortSettings* port = p->getPortSettingsPtr();
	if (port == nullptr)
	{
		return -2;
	}
	m_currentPort = port;
	int ret = OK;
	ret = putActionsInMenu(m_baudActionGroup, baudMenu, BAUD_RATE);
	ret = putActionsInMenu(m_parityActionGroup, parityMenu, PARITY);
	ret = putActionsInMenu(m_stopActionGroup, stopMenu, STOP_BITS);
	ret = putActionsInMenu(m_flowActionGroup, flowMenu, FLOW_CONTROL);
	ret = putActionsInMenu(m_dataActionGroup, dataMenu, DATA_BITS);
	return ret;
}

int GeneralSerial::putActionsInMenu(QActionGroup* ag, QMenu* menu, SerialProps prop)
{
	menu->clear();
	unsigned char selected = m_currentPort->getPropIndex(prop);
	if (selected < ag->actions().size())
	{
		ag->actions()[selected]->setChecked(true);
	}
	else
	{ //should not happen!!!!
		if (ag->checkedAction() != NULL)
		{
			ag->checkedAction()->setChecked(false);
		}
	}
	std::vector<unsigned char> setable = m_currentPort->settableProps(prop);
	for (int i = 0; i < m_currentPort->settableProps(prop).size(); ++i)
	{
		menu->addAction(ag->actions().at(setable[i]));
	}
	return OK;
}

void GeneralSerial::update()
{
	
}

void GeneralSerial::changePort(QAction* act)
{
	int newPort = act->data().toInt();
	//wprintf_s(L"port %d: COM%d\n", newPort, m_serialPort.getPortNumber(newPort));
	if (m_currentPortnumber != newPort)
	{
		m_currentPortnumber = newPort;
		getSetabbles();
	}
	//wprintf_s(L"port: %s\n", act->text().toStdWString().c_str());
}

void GeneralSerial::changeBaud(QAction* act)
{
	m_currentPort->setPropIndex(BAUD_RATE, (unsigned char)act->data().toInt());
	//wprintf_s(L"baud: %s\n", act->text().toStdWString().c_str());
}

void GeneralSerial::changeParity(QAction* act)
{
	m_currentPort->setPropIndex(PARITY, (unsigned char)act->data().toInt());
}

void GeneralSerial::changeStopBits(QAction* act)
{
	m_currentPort->setPropIndex(STOP_BITS, (unsigned char)act->data().toInt());
}

void GeneralSerial::changeFlowControl(QAction* act)
{
	m_currentPort->setPropIndex(FLOW_CONTROL, (unsigned char)act->data().toInt());
}

void GeneralSerial::changeDataBits(QAction* act)
{
	m_currentPort->setPropIndex(DATA_BITS, (unsigned char)act->data().toInt());
}
