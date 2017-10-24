#pragma once

#include <QThread>
#include <QQueue>
//#include <QTcpServer>
#include <QtNetwork>
#include "ImgProcessor.h"
#include <QImageReader>
class ImgReceiver : public QThread
{
	Q_OBJECT

public:
	ImgReceiver(QObject *parent);
	~ImgReceiver();
	void stopReceiving();
protected:
	void run();
private:
	void saveImg();

private slots:
	void slt_acceptConnection();
	void slt_receiveImage();

public:
	QQueue<QImage> imgQue;
private:
	QTcpServer *m_pTcpServer;
	QTcpSocket *m_pTcpConnection;

	const quint8 HEADSIZE = 16;
	quint32 m_nImageSize;
	quint32 m_numBytesRecved;
	QByteArray m_bufImage;

	ImgProcessor* m_pImgProc;
	const int FREQUENCY = 10;
	bool m_bRunning;
	int cnt = FREQUENCY;
};
