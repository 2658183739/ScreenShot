/********************************************************************************
** Form generated from reading UI file 'screenshot.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCREENSHOT_H
#define UI_SCREENSHOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScreenShot
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ScreenShot)
    {
        if (ScreenShot->objectName().isEmpty())
            ScreenShot->setObjectName(QString::fromUtf8("ScreenShot"));
        ScreenShot->resize(800, 600);
        centralwidget = new QWidget(ScreenShot);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(130, 150, 151, 81));
        ScreenShot->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ScreenShot);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        ScreenShot->setMenuBar(menubar);
        statusbar = new QStatusBar(ScreenShot);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ScreenShot->setStatusBar(statusbar);

        retranslateUi(ScreenShot);

        QMetaObject::connectSlotsByName(ScreenShot);
    } // setupUi

    void retranslateUi(QMainWindow *ScreenShot)
    {
        ScreenShot->setWindowTitle(QCoreApplication::translate("ScreenShot", "ScreenShot", nullptr));
        pushButton->setText(QCoreApplication::translate("ScreenShot", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ScreenShot: public Ui_ScreenShot {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCREENSHOT_H
