#pragma once

#include <QThread>
#include <QImage>
#include "ImgProcessor.h"

#define WINDOWNAME "click to chose a HSV"
class ShowAPic : public QThread
{
	Q_OBJECT

public:
	ShowAPic(QImage img, QObject *parent = 0);
	~ShowAPic();
	void stop();
signals:
	void sig_HSV(int H, int S, int V);
protected:
	void run();
private:
	//char const windowname[21] = "click to chose a HSV";
	static void on_mouse(int EVENT, int x, int y, int flags, void* userdata);
	bool m_bRunning;
	QImage m_img;
	static int H, S, V;

};
