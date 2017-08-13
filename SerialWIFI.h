#pragma once

#include <QtNetwork>
#include <QTcpServer>
#include "SerialUtil.h"

class SerialWIFI : public QTcpServer, public SerialUtil
{
	Q_OBJECT

public:
	SerialWIFI(QObject *parent = 0);
	~SerialWIFI();
	bool IsConnected();
	int WriteData(const char *buffer, unsigned int nbChar);
	int ReadData(char *buffer, unsigned int nbChar);
private:
	bool m_bConnected;
	QTcpSocket* m_pSocket;
private slots:
	void acceptConnection();
};
