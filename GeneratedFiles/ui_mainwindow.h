/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionVisualizer;
    QAction *actionAbout;
    QAction *actionSpinner;
    QAction *actionTo_Camera;
    QAction *actionTo_Servo_Controller;
    QAction *actionTo_Serial;
    QAction *actionControlPanel;
    QAction *actionTake_A_Pic;
    QWidget *centralWidget;
    QLabel *label_display;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_1;
    QMenu *menuConnect;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(640, 480);
        actionVisualizer = new QAction(MainWindow);
        actionVisualizer->setObjectName(QStringLiteral("actionVisualizer"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionSpinner = new QAction(MainWindow);
        actionSpinner->setObjectName(QStringLiteral("actionSpinner"));
        actionTo_Camera = new QAction(MainWindow);
        actionTo_Camera->setObjectName(QStringLiteral("actionTo_Camera"));
        actionTo_Servo_Controller = new QAction(MainWindow);
        actionTo_Servo_Controller->setObjectName(QStringLiteral("actionTo_Servo_Controller"));
        actionTo_Serial = new QAction(MainWindow);
        actionTo_Serial->setObjectName(QStringLiteral("actionTo_Serial"));
        actionControlPanel = new QAction(MainWindow);
        actionControlPanel->setObjectName(QStringLiteral("actionControlPanel"));
        actionTake_A_Pic = new QAction(MainWindow);
        actionTake_A_Pic->setObjectName(QStringLiteral("actionTake_A_Pic"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label_display = new QLabel(centralWidget);
        label_display->setObjectName(QStringLiteral("label_display"));
        label_display->setGeometry(QRect(0, 0, 640, 480));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(17);
        label_display->setFont(font);
        label_display->setTextFormat(Qt::PlainText);
        label_display->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 640, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_1 = new QMenu(menuBar);
        menu_1->setObjectName(QStringLiteral("menu_1"));
        menuConnect = new QMenu(menuBar);
        menuConnect->setObjectName(QStringLiteral("menuConnect"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuConnect->menuAction());
        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_1->menuAction());
        menu->addAction(actionSpinner);
        menu->addAction(actionControlPanel);
        menu->addSeparator();
        menu->addAction(actionTake_A_Pic);
        menu_1->addAction(actionVisualizer);
        menu_1->addSeparator();
        menu_1->addAction(actionAbout);
        menuConnect->addAction(actionTo_Camera);
        menuConnect->addAction(actionTo_Servo_Controller);
        menuConnect->addAction(actionTo_Serial);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionVisualizer->setText(QApplication::translate("MainWindow", "Visualizer", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0));
        actionSpinner->setText(QApplication::translate("MainWindow", "Spinner", 0));
        actionTo_Camera->setText(QApplication::translate("MainWindow", "to Camera", 0));
#ifndef QT_NO_TOOLTIP
        actionTo_Camera->setToolTip(QApplication::translate("MainWindow", "connect to Camera", 0));
#endif // QT_NO_TOOLTIP
        actionTo_Servo_Controller->setText(QApplication::translate("MainWindow", "to Servo Controller", 0));
#ifndef QT_NO_TOOLTIP
        actionTo_Servo_Controller->setToolTip(QApplication::translate("MainWindow", "connect to Servo Controller", 0));
#endif // QT_NO_TOOLTIP
        actionTo_Serial->setText(QApplication::translate("MainWindow", "to Serial", 0));
#ifndef QT_NO_TOOLTIP
        actionTo_Serial->setToolTip(QApplication::translate("MainWindow", "connect to Serial", 0));
#endif // QT_NO_TOOLTIP
        actionControlPanel->setText(QApplication::translate("MainWindow", "ControlPanel", 0));
        actionTake_A_Pic->setText(QApplication::translate("MainWindow", "Take A Pic", 0));
        label_display->setText(QApplication::translate("MainWindow", "image to display", 0));
        menu->setTitle(QApplication::translate("MainWindow", "Tools", 0));
        menu_1->setTitle(QApplication::translate("MainWindow", "Help", 0));
        menuConnect->setTitle(QApplication::translate("MainWindow", "Connect", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
