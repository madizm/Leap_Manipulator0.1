#pragma once

#include <QThread>
#include "ImgReceiver.h"
class ImgDeliverer : public QThread
{
	Q_OBJECT

public:
	ImgDeliverer(QObject *parent);
	~ImgDeliverer();
	void stopDelivering();
	ImgProcessor* getImgProcessor();
protected:
	void run();
signals:
	void sig_aFrame(QImage img);
private:
	ImgReceiver *m_pImgRceiver;
	float m_fFps;
	bool m_bRunning;
};
