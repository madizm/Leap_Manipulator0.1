#include "ImgDeliverer.h"

ImgDeliverer::ImgDeliverer(QObject *parent)
	: QThread(parent)
{
	m_fFps = 40;
	m_bRunning = true;
	m_pImgRceiver = new ImgReceiver(this);
}

ImgDeliverer::~ImgDeliverer()
{
	delete m_pImgRceiver;
}

void ImgDeliverer::stopDelivering()
{
	m_bRunning = false;
	m_pImgRceiver->stopReceiving();
	m_pImgRceiver->wait();
}

void ImgDeliverer::run()
{
	m_pImgRceiver->start();
	qDebug() << "enter imgDeliverer";
	QQueue<QImage> *queue = &(m_pImgRceiver->imgQue);
	while(m_bRunning)
	{
		//qDebug() << "imgDeliverer running";
		if (!queue->isEmpty()) {
			emit sig_aFrame(queue->dequeue());
			//qDebug() << "emit a frame";
		}
		msleep(1000 / m_fFps);
	}
	qDebug() << "exit imgDeliverer";
}
