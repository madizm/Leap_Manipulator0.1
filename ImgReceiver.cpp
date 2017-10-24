#include "ImgReceiver.h"

ImgReceiver::ImgReceiver(QObject *parent)
	: QThread(parent)
{
	m_bRunning = true;
	m_pTcpServer = new QTcpServer(this);
	m_pImgProc = new ImgProcessor(this);
	m_numBytesRecved = 0;
	m_nImageSize = 0;
	if (!m_pTcpServer->listen(QHostAddress::Any, 8002))
	{
		qDebug() << m_pTcpServer->errorString();
		//close();
	}
	qDebug() << "ready to receive";
}

ImgReceiver::~ImgReceiver()
{
	imgQue.clear();
	delete m_pTcpServer;
	delete m_pImgProc;
}

void ImgReceiver::stopReceiving()
{
	m_bRunning = false;
	
}

void ImgReceiver::run()
{
	connect(m_pTcpServer, &QTcpServer::newConnection, this, &ImgReceiver::slt_acceptConnection);
	while(m_bRunning){}
	qDebug() << "exit imgReceiver";
}

void ImgReceiver::saveImg()
{
	//qDebug() << "save a img";
	//socket�����㹻������� Ҳ����˵socket���͵���һ��ͼƬ������ �ͱ���
	QByteArray data = m_pTcpConnection->read(m_nImageSize);
	QBuffer buf(&data);
	buf.open(QIODevice::ReadOnly);

	QImageReader reader(&buf, "jpg");
	QImage image = reader.read();
	static QImage box;
	if (++cnt > FREQUENCY) {
		//����ͼƬ
		//QImage nImg = m_pImgProc->processImg(image);
		//imgQue.enqueue(nImg);
		m_pImgProc->processImg(image, box);
		imgQue.enqueue(image);
		cnt = 0;
	}
	else {
		if(!box.isNull())
			m_pImgProc->orQImage(image, box);
		imgQue.enqueue(image);
	}
	
	//���½�����һ��ͼƬ
	m_nImageSize = 0;
}

void ImgReceiver::slt_receiveImage()
{
	if (m_nImageSize == 0) {
		//����HEADSIZE���ֽڵ����� ������ݼ�¼��ͼƬ�Ĵ�С��Image Size��
		if (m_pTcpConnection->bytesAvailable() < HEADSIZE)//socket��û���㹻������ ֱ��return
			return;
		QByteArray buf = m_pTcpConnection->read(HEADSIZE);
		//   qDebug()<<"buf: "<<buf;
		m_nImageSize = buf.toUInt();
		//    qDebug()<<"buf.toint() :"<<m_nImageSize;
	}

	if (m_pTcpConnection->bytesAvailable() < m_nImageSize) {//socket��û���㹻�����ݣ�һ��ͼƬ�� ֱ��return
		return;
	}
	saveImg();
}

void ImgReceiver::slt_acceptConnection()
{
	qDebug() << "accept new connection";
	//ui->statusBar->showMessage(tr("accept new connection"), 2000);
	m_pTcpConnection = m_pTcpServer->nextPendingConnection();
	connect(m_pTcpConnection, &QTcpSocket::readyRead, this, &ImgReceiver::slt_receiveImage);
}
