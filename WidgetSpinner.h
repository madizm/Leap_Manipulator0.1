#pragma once

#include <QObject>
#include <QtWidgets>
#include "servospinner.h"
#include "FrameListener.h"

class WidgetSpinner : public QWidget
{
	Q_OBJECT

public:
	WidgetSpinner(FrameListener * listener = nullptr, QWidget *parent = 0);
	~WidgetSpinner();

	

private:
	FrameListener* m_pListener;

	ServoSpinner* m_pSer0;
	ServoSpinner* m_pSer1;
	ServoSpinner* m_pSer2;
	ServoSpinner* m_pSer3;
	ServoSpinner* m_pSer4;
	ServoSpinner* m_pSer5;

signals:
	void valuesChanged(const VectorXf info);

public slots:
	void setValues(const VectorXf deg);
	void vaulesChanged();
};
