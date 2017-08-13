#pragma once

#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include "FrameListener.h"

class ControlPanel : public QWidget
{
	Q_OBJECT

public:
	ControlPanel(FrameListener * listener = nullptr, QWidget *parent = 0);
	~ControlPanel();
	void autoScroll();
private:
	QPushButton *m_btnStopContinue;
	QPushButton *m_btnUp;
	QPushButton *m_btnDown;
	QPushButton *m_btnForward;
	QPushButton *m_btnBackward;
	QPushButton *m_btnReset;
	QString m_strOutput;
	QLabel *m_label;
	QTextEdit *m_editDisplay;

	FrameListener *m_listener;

private slots:
	void clickedStopContinue();
	void clickedUp();
	void clickedDown();
	void clickedForward();
	void clickedBackward();
	void clickedReset();

	void showError(Model::ERROR_TYPE error);
	void showNextInfo(VectorXf info);
	void showNextDeg(VectorXf deg);
};
