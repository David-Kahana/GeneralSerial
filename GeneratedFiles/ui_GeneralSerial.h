/********************************************************************************
** Form generated from reading UI file 'GeneralSerial.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERALSERIAL_H
#define UI_GENERALSERIAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GeneralSerialClass
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GeneralSerialClass)
    {
        if (GeneralSerialClass->objectName().isEmpty())
            GeneralSerialClass->setObjectName(QStringLiteral("GeneralSerialClass"));
        GeneralSerialClass->resize(800, 400);
        centralWidget = new QWidget(GeneralSerialClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        GeneralSerialClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GeneralSerialClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 38));
        GeneralSerialClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GeneralSerialClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        GeneralSerialClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(GeneralSerialClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        GeneralSerialClass->setStatusBar(statusBar);

        retranslateUi(GeneralSerialClass);

        QMetaObject::connectSlotsByName(GeneralSerialClass);
    } // setupUi

    void retranslateUi(QMainWindow *GeneralSerialClass)
    {
        GeneralSerialClass->setWindowTitle(QApplication::translate("GeneralSerialClass", "GeneralSerial", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GeneralSerialClass: public Ui_GeneralSerialClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERALSERIAL_H
