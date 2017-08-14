#include "ImgProcessor.h"
using namespace cv;
using namespace std;
ImgProcessor::ImgProcessor(QObject *parent)
	: QObject(parent)
{
	m_nTimerId = startTimer(800);
	if (m_nTimerId == 0) {
		cout << "Failed to initialize timer" << endl;
	}
	namedWindow("Control", WINDOW_NORMAL| WINDOW_FREERATIO| WINDOW_GUI_NORMAL);
	resizeWindow("Control", 300, 300);
	cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
	cvCreateTrackbar("HighH", "Control", &iHighH, 179);

	cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
	cvCreateTrackbar("HighS", "Control", &iHighS, 255);

	cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
	cvCreateTrackbar("HighV", "Control", &iHighV, 255);
}

ImgProcessor::~ImgProcessor()
{
	if (m_nTimerId != 0) {
		killTimer(m_nTimerId);
	}
}

QImage ImgProcessor::processImg(QImage & image)
{
	m_bDetected = false;
	//convert QImage to Mat
	Mat imgOriginal = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());

	Mat imgHSV;
	vector<Mat> hsvSplit;
	cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV);
	Mat imgThresholded;

	inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded);

	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);
	morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);

	vector<vector<Point> > contours;
	findContours(imgThresholded, contours, RETR_LIST, CHAIN_APPROX_NONE);

	Mat cimage = Mat::zeros(imgThresholded.size(), CV_8UC4);

	for (size_t i = 0; i < contours.size(); i++)
	{
		size_t count = contours[i].size();
		if (count < 6)
			continue;

		Mat pointsf;
		Mat(contours[i]).convertTo(pointsf, CV_32F);
		RotatedRect box = fitEllipse(pointsf);

		if (MAX(box.size.width, box.size.height) > MIN(box.size.width, box.size.height) * 30)
			continue;

		if (box.size.width < cimage.size().width / 4)
			continue;

		Point2f vtx[4];
		box.points(vtx);
		m_bDetected = true;
		m_rx = box.center.x;
		m_ry = box.center.y;
		m_R = box.angle;
		for (int j = 0; j < 4; j++)
			line(cimage, vtx[j], vtx[(j + 1) % 4], Scalar(255, 255, 255), 1, LINE_AA);
		QString str = QString("(%1, %2, %3)").arg((int)m_rx).arg((int)m_ry).arg((int)m_R);
		putText(cimage, str.toStdString(), Point2f(m_rx, m_ry), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1, LINE_AA);
	}
	if (!m_bDetected) {
		m_rx = 640 / 2;
		m_ry = 480 / 2;
		m_R = 90;
	}
	imgOriginal |= cimage;
	//convert Mat to QImage
	const uchar *pSrc = (const uchar*)imgOriginal.data;
	// Create QImage with same dimensions as input Mat    
	QImage nimage(pSrc, imgOriginal.cols, imgOriginal.rows, imgOriginal.step, QImage::Format_ARGB32);
	return nimage.copy();
}

void ImgProcessor::timerEvent(QTimerEvent * e)
{
	if (abs(m_rx-320)>10 || abs(m_ry - 240)>10 || abs(m_R - 90)>10)
		cout << QString("x: %1  y: %2  R: %3").arg((int)m_rx).arg((int)m_ry).arg((int)m_R).toStdString() << endl; ;
}
