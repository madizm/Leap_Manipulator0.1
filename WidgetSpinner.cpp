#include "WidgetSpinner.h"

WidgetSpinner::WidgetSpinner(FrameListener * listener, QWidget *parent)
	: QWidget(parent),
	m_pListener(listener)
{
	setWindowFlags(Qt::Tool);
	setWindowTitle("Spinner");
	m_pSer0 = new ServoSpinner(this, -90, 90, 0);
	m_pSer1 = new ServoSpinner(this, 0, 180, 60);
	m_pSer2 = new ServoSpinner(this, 0, 180, 120);
	m_pSer3 = new ServoSpinner(this, -90, 90, 0);
	m_pSer4 = new ServoSpinner(this, -90, 90, 0);
	m_pSer5 = new ServoSpinner(this, -90, 90, 0);
	QVBoxLayout *vLayout = new QVBoxLayout;
	vLayout->addWidget(m_pSer5);
	vLayout->addWidget(m_pSer4);
	vLayout->addWidget(m_pSer3);
	vLayout->addWidget(m_pSer2);
	vLayout->addWidget(m_pSer1);
	vLayout->addWidget(m_pSer0);
	setLayout(vLayout);
	connect(m_pListener, &FrameListener::nextDeg, this, &WidgetSpinner::setValues);
	connect(m_pSer0, &ServoSpinner::valueChanged, this, &WidgetSpinner::vaulesChanged);
	connect(m_pSer1, &ServoSpinner::valueChanged, this, &WidgetSpinner::vaulesChanged);
	connect(m_pSer2, &ServoSpinner::valueChanged, this, &WidgetSpinner::vaulesChanged);
	connect(m_pSer3, &ServoSpinner::valueChanged, this, &WidgetSpinner::vaulesChanged);
	connect(m_pSer4, &ServoSpinner::valueChanged, this, &WidgetSpinner::vaulesChanged);
	connect(m_pSer5, &ServoSpinner::valueChanged, this, &WidgetSpinner::vaulesChanged);
//	connect(this, &WidgetSpinner::valuesChanged, m_pListener, &FrameListener::handleDegs);
}

WidgetSpinner::~WidgetSpinner()
{
}

void WidgetSpinner::vaulesChanged()
{
	VectorXf deg(6);
	deg << m_pSer0->getValue(), m_pSer1->getValue(), m_pSer2->getValue()
		, m_pSer3->getValue(), m_pSer4->getValue(), (float)m_pSer5->getValue()/180;
	m_pListener->handleDegs(deg);
}

void WidgetSpinner::setValues(VectorXf deg)
{
	m_pSer0->setValue((int)deg(0));
	m_pSer1->setValue((int)deg(1));
	m_pSer2->setValue((int)deg(2));
	m_pSer3->setValue((int)deg(3));
	m_pSer4->setValue((int)deg(4));
	m_pSer5->setValue((int)(deg(5)*180));
}
