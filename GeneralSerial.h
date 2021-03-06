#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GeneralSerial.h"
#include "SerialPortsMngt.h"

enum eFileOperations
{
	SAVE_PORT_CONF = 0,
	LOAD_PORT_CONF = 1
};

class GeneralSerial : public QMainWindow
{
	Q_OBJECT
public:
	std::vector<QAction*> m_baudratesActs;
public:
	GeneralSerial(QWidget *parent = Q_NULLPTR);
private slots:
	void fileOperation(QAction* act);
	void update();
	void changePort(QAction* act);
	void changeBaud(QAction* act);
	void changeParity(QAction* act);
	void changeStopBits(QAction* act);
	void changeFlowControl(QAction* act);
	void changeDataBits(QAction* act);
private:
	Ui::GeneralSerialClass ui;
	QActionGroup* m_fileActionGroup;
	QActionGroup* m_portActionGroup;
	QActionGroup* m_baudActionGroup;
	QActionGroup* m_parityActionGroup;
	QActionGroup* m_stopActionGroup;
	QActionGroup* m_flowActionGroup;
	QActionGroup* m_dataActionGroup;
	QMenu* fileMenu;
	QMenu* connectMenu;
	QMenu* portMenu;
	QMenu* baudMenu;
	QMenu* parityMenu;
	QMenu* stopMenu;
	QMenu* flowMenu; 
	QMenu* dataMenu;
	CSerialPortsMngt m_ports;
	int m_currentPortnumber = 0;
	CSerialPortSettings* m_currentPort;
	QTimer *timer;
private:
	int createMenus();
	int setUpFileMenu();
	int createActionGroups();
	QActionGroup* makeActionGroup(const std::vector<std::wstring>& strs);
	int putActionsInMenu(QActionGroup* ag, QMenu* menu, SerialProps prop);
	int getSetabbles();
};
