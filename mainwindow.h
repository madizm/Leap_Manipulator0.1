#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QProcess>
#include <QTextCodec>
#include <QtNetwork>
#include "servospinner.h"

#include "FrameListener.h"
#include "ModelFactory.h"
#include "SerialWin.h"
#include "ControlPanel.h"
#include "WidgetSpinner.h"
#include "SerialWIFI.h"
#include "ImgProcessor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QTcpServer *tcpServer;
    QTcpSocket *tcpServerConnection;

    const quint8 HEADSIZE = 16;
    quint32 m_nImageSize;
    quint32 m_numBytesRecved;
    QByteArray m_bufImage;

    QDockWidget *m_dock;
    QProcess *m_process;//for ssh
	QProcess *m_processVApp;//for visulizerapp
	QProcess* m_processSer;//for servoController
    QWidget *m_widgetSpinner;

	ControlPanel* m_pControlPanel;
	SerialUtil* m_pSerial;
	WidgetSpinner* m_pWidgetSpinner;

    const quint8 NUMSERVO = 6;

	Controller controller;
	FrameListener listener;

	ImgProcessor* m_pImgProc;

	QAction* m_pCloseSerial;
private:
    void initServerCamera();
    void initProcess();

    QFrame *createSpinner();
    void createDockSpinner();
    void createWidgetSpinner();
    void displayImage();

private slots:
    //socket
    void receiveImage();
    void acceptConnection();
    void displaySocketError(QAbstractSocket::SocketError socketError);

    void readySend();
	void on_actionAbout_triggered();
    void on_actionTo_Camera_triggered();
	void on_actionVisualizer_triggered();
	void on_actionTo_Serial_triggered();
	void on_actionTo_Servo_Controller_triggered();
	void on_actionControlPanel_triggered();
	void on_actionSpinner_triggered();
    //process
    void showProcessResult();
    void showProcessState(QProcess::ProcessState);
    void showProcessError();
    void showProcessFinished(int, QProcess::ExitStatus);

	void closeSerial();

};

#endif // MAINWINDOW_H
