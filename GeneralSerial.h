#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GeneralSerial.h"
#include "JsonSettings.h"

class GeneralSerial : public QMainWindow
{
	Q_OBJECT

public:
	GeneralSerial(QWidget *parent = Q_NULLPTR);

private:
	Ui::GeneralSerialClass ui;
};
