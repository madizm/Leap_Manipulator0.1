#pragma once

#include <QObject>
#include <QImage>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "AS_6DOF.h"

class ImgProcessor : public QObject
{
	Q_OBJECT

public:
	ImgProcessor(QObject *parent);
	~ImgProcessor();
	QImage processImg(QImage &image);
protected:
	void timerEvent(QTimerEvent* e);
	int m_nTimerId;
signals:
	void sig_trans(AS_6DOF::TRANS_TYPE trans, int factor=10);

private:
	int iLowH = 100;
	int iHighH = 140;

	int iLowS = 60;
	int iHighS = 255;

	int iLowV = 40;
	int iHighV = 255;

	float m_rx = 640 / 2;
	float m_ry = 480 / 2;
	float m_R = 90;
	int m_width = 0;
	int m_height = 0;
	bool m_bDetected = false;
	bool m_bGrabed = false;
};
