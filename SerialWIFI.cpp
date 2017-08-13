#include "SerialWIFI.h"

SerialWIFI::SerialWIFI(QObject *parent)
	: QTcpServer(parent)
{
	if (!listen(QHostAddress::Any, 8003))
	{
		qDebug() << errorString();
		close();
	}
	connect(this, &SerialWIFI::newConnection, this, &SerialWIFI::acceptConnection);
	m_bConnected = false;
	m_pSocket = nullptr;
}

SerialWIFI::~SerialWIFI()
{
}

bool SerialWIFI::IsConnected()
{
	return m_bConnected;
}

//write length+data
int SerialWIFI::WriteData(const char * buffer, unsigned int nbChar)
{
	int a = m_pSocket->write(QByteArray::number(nbChar).data(), 2);
	return a + m_pSocket->write(buffer, nbChar);
}

int SerialWIFI::ReadData(char * buffer, unsigned int nbChar)
{
	return 0;
}


void SerialWIFI::acceptConnection()
{
	qDebug() << "accept new connection";
	m_pSocket = nextPendingConnection();
	m_bConnected = true;
}

