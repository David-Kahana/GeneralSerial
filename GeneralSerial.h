#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GeneralSerial.h"
#include "JsonSettings.h"
#include "SerialPort.h"

class GeneralSerial : public QMainWindow
{
	Q_OBJECT
public:
	std::vector<QAction*> m_baudratesActs;
public:
	GeneralSerial(QWidget *parent = Q_NULLPTR);
private slots:
	void changePort(QAction* act);
	void changeBaud(QAction* act);
	void changeParity(QAction* act);
	void changeStopBits(QAction* act);
	void changeFlowControl(QAction* act);
	void changeDataBits(QAction* act);
private:
	Ui::GeneralSerialClass ui;
	QActionGroup* m_portActionGroup;
	QActionGroup* m_baudActionGroup;
	QActionGroup* m_parityActionGroup;
	QActionGroup* m_stopActionGroup;
	QActionGroup* m_flowActionGroup;
	QActionGroup* m_dataActionGroup;
	QMenu* portMenu;
	QMenu* baudMenu;
	QMenu* parityMenu;
	QMenu* stopMenu;
	QMenu* flowMenu; 
	QMenu* dataMenu;
	int m_currentPortIndex = 0;
	CSerialPortSettings* m_currentPort;
	
private:
	int createMenus();
	int createActionGroups();
	QActionGroup* makeActionGroup(const std::vector<std::wstring>& strs);
	int putActionsInMenu(QActionGroup* ag, QMenu* menu, const std::vector<unsigned char>& index, unsigned char selected);
	int putActionsInMenu(QActionGroup* ag, QMenu* menu, SerialProps prop);
	int getSetabbles();
};
