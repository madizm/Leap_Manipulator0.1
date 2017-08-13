#include "servospinner.h"

ServoSpinner::ServoSpinner(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout();
    m_dial = new QDial(parent);
    m_dial->setNotchesVisible (true);
    m_dial->setRange (0, 180);
    m_lcd = new QLCDNumber(parent);
    layout->addWidget (m_dial);
    layout->addWidget (m_lcd);
    setLayout (layout);
}
ServoSpinner::ServoSpinner(QWidget *parent, int min, int max, int value, int No)
{
    m_No = No;
    QVBoxLayout *layout = new QVBoxLayout();
    m_dial = new QDial(parent);
    m_dial->setNotchesVisible (true);
    m_dial->setRange (min, max);
    m_dial->setValue (value);
    m_lcd = new QLCDNumber(parent);
    m_lcd->setDigitCount (3);
    m_lcd->setSegmentStyle (QLCDNumber::Flat);
    m_lcd->display (value);
    layout->addWidget (m_dial);
    layout->addWidget (m_lcd);
    setLayout (layout);
    connect (m_dial, &QDial::valueChanged, this, &ServoSpinner::setDeg);
//	setFocusPolicy(Qt::NoFocus);
}
ServoSpinner::~ServoSpinner()
{
	delete m_dial;
	delete m_lcd;
}

int ServoSpinner::getValue()
{
	return m_lcd->value();
}
void ServoSpinner::setDeg(int deg)
{
	emit valueChanged(deg, m_No);
	m_lcd->display(deg);
}
void ServoSpinner::setValue (int value)
{
	//if (m_dial->isSliderDown()) {
	//	emit valueChanged(value, m_No);
	//}
    m_lcd->display (value);
	m_dial->setValue(value);
}
