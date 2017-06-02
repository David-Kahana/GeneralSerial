#include "stdafx.h"
#include "GeneralSerial.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GeneralSerial w;
	w.show();
	return a.exec();
}
