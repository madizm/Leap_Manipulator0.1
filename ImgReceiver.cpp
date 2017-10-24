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
	//socket中有足够多的数据 也就是说socket接送到了一张图片的数据 就保存
	QByteArray data = m_pTcpConnection->read(m_nImageSize);
	QBuffer buf(&data);
	buf.open(QIODevice::ReadOnly);

	QImageReader reader(&buf, "jpg");
	QImage image = reader.read();
	static QImage box;
	if (++cnt > FREQUENCY) {
		//处理图片
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
	
	//重新接收下一张图片
	m_nImageSize = 0;
}

void ImgReceiver::slt_receiveImage()
{
	if (m_nImageSize == 0) {
		//接收HEADSIZE个字节的数据 这个数据记录了图片的大小（Image Size）
		if (m_pTcpConnection->bytesAvailable() < HEADSIZE)//socket中没有足够的数据 直接return
			return;
		QByteArray buf = m_pTcpConnection->read(HEADSIZE);
		//   qDebug()<<"buf: "<<buf;
		m_nImageSize = buf.toUInt();
		//    qDebug()<<"buf.toint() :"<<m_nImageSize;
	}

	if (m_pTcpConnection->bytesAvailable() < m_nImageSize) {//socket中没有足够的数据（一张图片） 直接return
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
