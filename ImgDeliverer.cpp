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

ImgProcessor * ImgDeliverer::getImgProcessor()
{
	return m_pImgRceiver->m_pImgProc;
}

void ImgDeliverer::run()
{
	m_pImgRceiver->start();
	QQueue<QImage> *queue = &(m_pImgRceiver->imgQue);
	while(m_bRunning)
	{
		if (!queue->empty()) {
			emit sig_aFrame(queue->dequeue());
		}
		msleep(1000 / m_fFps);
	}
}
