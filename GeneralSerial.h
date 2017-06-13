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
	void changeBaud(QAction* act);
	void changePort(QAction* act);


private:
	Ui::GeneralSerialClass ui;
	QActionGroup* m_portActionGroup;
	QActionGroup* m_baudActionGroup;
	
	int m_currentPortIndex = 0;
	CSerialPort m_serialPort;
};
