#include "ShowAPic.h"
using namespace cv;

ShowAPic::ShowAPic(QImage img, QObject *parent)
	: QThread(parent)
{
	m_bRunning = false;
	m_img = img;
}

ShowAPic::~ShowAPic()
{
}

int ShowAPic::H = 0;
int ShowAPic::S = 0;
int ShowAPic::V = 0;
//char ShowAPic::windowname[21] = "click to chose a HSV";

void ShowAPic::on_mouse(int EVENT, int x, int y, int flags, void* userdata)
{
	Mat rgb, hsv;
	rgb = *(Mat*)userdata;
	Mat temp;
	cvtColor(*(Mat*)userdata, hsv, CV_BGR2HSV);
	Point p(x, y);
	switch (EVENT)
	{
	case EVENT_LBUTTONDOWN:
	{
		//printf("b=%d\t", rgb.at<Vec3b>(p)[0]);
		//printf("g=%d\t", rgb.at<Vec3b>(p)[1]);
		//printf("r=%d\n", rgb.at<Vec3b>(p)[2]);
		H = hsv.at<Vec3b>(p)[0];
		S = hsv.at<Vec3b>(p)[1];
		V = hsv.at<Vec3b>(p)[2];
		printf("H=%d\t", H);
		printf("S=%d\t", S);
		printf("V=%d\n", V);
		circle(rgb, p, 2, Scalar(255), 3);
	}
	break;
	}
	
}

void ShowAPic::stop()
{
	m_bRunning = false;
	cv::destroyWindow(WINDOWNAME);
}

void ShowAPic::run()
{
	m_bRunning = true;
	cv::namedWindow(WINDOWNAME);
	cv::Mat src;
	ImgProcessor::QImage2Mat(m_img, src);
	setMouseCallback(WINDOWNAME, on_mouse, &src);
	while (m_bRunning) {
		imshow(WINDOWNAME, src);
		if (waitKey(40) == 27) {
			break;
		}
		emit sig_HSV(H, S, V);
	}
	m_bRunning = false;
}
