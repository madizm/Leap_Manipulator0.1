#include "ControlPanel.h"

ControlPanel::ControlPanel(FrameListener * listener, QWidget *parent)
	: QWidget(parent),
	m_listener(listener)
{
	m_btnBackward = new QPushButton("Backward", this);
	m_btnBackward->setAutoRepeat(true);
	m_btnBackward->setAutoRepeatInterval(500);
	m_btnBackward->setAutoRepeatDelay(1000);
	m_btnDown = new QPushButton("Downward", this);
	m_btnDown->setAutoRepeat(true);
	m_btnDown->setAutoRepeatInterval(500);
	m_btnDown->setAutoRepeatDelay(1000);
	m_btnForward = new QPushButton("Forward", this);
	m_btnForward->setAutoRepeat(true);
	m_btnForward->setAutoRepeatInterval(500);
	m_btnForward->setAutoRepeatDelay(1000);
	m_btnStopContinue = new QPushButton("StartTracking", this);
	m_btnUp = new QPushButton("Upward", this);
	m_btnUp->setAutoRepeat(true);
	m_btnUp->setAutoRepeatInterval(500);
	m_btnUp->setAutoRepeatDelay(1000);
	m_btnReset = new QPushButton("Reset", this);
	m_editDisplay = new QTextEdit(this);
	m_editDisplay->setReadOnly(true);
	m_label = new QLabel("infomations:", this);
	QVBoxLayout *layout = new QVBoxLayout(this);
	QHBoxLayout *hlayout = new QHBoxLayout;
	hlayout->addWidget(m_btnStopContinue);
	hlayout->addWidget(m_btnReset);
	hlayout->setStretchFactor(m_btnStopContinue, 3);
	hlayout->setStretchFactor(m_btnReset, 1);
	layout->addLayout(hlayout);
	QHBoxLayout *hlayout0 = new QHBoxLayout;
	hlayout0->addWidget(m_btnForward);
	hlayout0->addWidget(m_btnBackward);
	layout->addLayout(hlayout0);
	QHBoxLayout *hlayout1 = new QHBoxLayout;
	hlayout1->addWidget(m_btnUp);
	hlayout1->addWidget(m_btnDown);
	layout->addLayout(hlayout1);
	m_splitter = new QSplitter(Qt::Horizontal, this);
	m_splitter->setHandleWidth(1);
	m_btnCarForward = new QPushButton("CarForward", this);
	m_btnCarBackward = new QPushButton("CarBackward", this);
	m_btnCarLeft = new QPushButton("CarSteerLeft", this);
	m_btnCarRight = new QPushButton("CarSteerRight", this);
	QHBoxLayout *hlayout2 = new QHBoxLayout;
	hlayout2->addWidget(m_btnCarForward);
	hlayout2->addWidget(m_btnCarBackward);
	QHBoxLayout *hlayout3 = new QHBoxLayout;
	hlayout3->addWidget(m_btnCarLeft);
	hlayout3->addWidget(m_btnCarRight);
	layout->addWidget(m_splitter);
	layout->addLayout(hlayout2);
	layout->addLayout(hlayout3);
	layout->addWidget(m_label);
	layout->addWidget(m_editDisplay);
	setLayout(layout);
	connect(m_btnBackward, SIGNAL(clicked(bool)), this, SLOT(clickedBackward()));
	connect(m_btnForward, SIGNAL(clicked(bool)), this, SLOT(clickedForward()));
	connect(m_btnUp, SIGNAL(clicked(bool)), this, SLOT(clickedUp()));
	connect(m_btnDown, SIGNAL(clicked(bool)), this, SLOT(clickedDown()));
	connect(m_btnStopContinue, SIGNAL(clicked(bool)), this, SLOT(clickedStopContinue()));
	connect(m_btnReset, SIGNAL(clicked(bool)), this, SLOT(clickedReset()));
	m_strOutput = "";
	connect(m_listener, &FrameListener::errorOccurred, this, &ControlPanel::showError);
	connect(m_listener, &FrameListener::currentInfo, this, &ControlPanel::showNextInfo);
	connect(m_listener, &FrameListener::nextDeg, this, &ControlPanel::showNextDeg);
	connect(m_editDisplay, &QTextEdit::textChanged, this, &ControlPanel::autoScroll);
}

ControlPanel::~ControlPanel()
{
}

void ControlPanel::autoScroll() {
	QTextCursor cursor = m_editDisplay->textCursor();
	cursor.movePosition(QTextCursor::End);
	m_editDisplay->setTextCursor(cursor);
}

void ControlPanel::clickedUp()
{
	m_listener->handleTrans(AS_6DOF::UP);
//	m_listener->handleTrans(AS_6DOF::GRAB);
}

void ControlPanel::clickedDown()
{
	m_listener->handleTrans(AS_6DOF::DOWN);
//	m_listener->handleTrans(AS_6DOF::RIGHT);
}

void ControlPanel::clickedForward()
{
	m_listener->handleTrans(AS_6DOF::FORWARD);
//	m_listener->handleTrans(AS_6DOF::ROLL);
}

void ControlPanel::clickedBackward()
{
	m_listener->handleTrans(AS_6DOF::BACKWARD);
//	m_listener->handleTrans(AS_6DOF::ROLLA);
}

void ControlPanel::clickedReset()
{
	m_listener->handleReset();
}

void ControlPanel::clickedSteerLeft()
{
	m_listener->handleTrans_car(Car_Doit::STEER_LEFT);
}

void ControlPanel::clickedCarForward()
{
	m_listener->handleTrans_car(Car_Doit::FORWARD);
}

void ControlPanel::clickedCarBackward()
{
	m_listener->handleTrans_car(Car_Doit::BACKWARD);
}

void ControlPanel::clickedSteerRight()
{
	m_listener->handleTrans_car(Car_Doit::STEER_RIGHT);
}

void ControlPanel::showError(const Model::ERROR_TYPE error)
{
	switch (error)
	{
	case Model::INVAILID_Z:
		m_strOutput += "Warning: z >= 0\n\n";
		break;
	case Model::CANT_REACH:
		m_strOutput += "Warning: Can Not Reach\n\n";
	default:
		break;
	}
	m_editDisplay->setText(m_strOutput);
}

void ControlPanel::showNextInfo(const VectorXf info)
{
	m_strOutput += QString("R: %1Deg  P: %2Deg  Y: %3Deg  \nx: %4mm  y: %5mm  z: %6mm  strength: %7\n")
		.arg(info(0)).arg(info(1)).arg(info(2)).arg(info(3)).arg(info(4)).arg(info(5)).arg(info(6));
	m_editDisplay->setText(m_strOutput);
}

void ControlPanel::showNextDeg(const VectorXf deg)
{
	m_strOutput += QString("Q0: %1  Q1: %2  Q2: %3  Q3: %4  Q4: %5\n\n")
		.arg(deg(0)).arg(deg(1)).arg(deg(2)).arg(deg(3)).arg(deg(4));
	m_editDisplay->setText(m_strOutput);
}

void ControlPanel::clickedStopContinue()
{
	if (m_listener->isRunning()) {
		m_listener->stopListen();
		m_btnStopContinue->setText("Continue");
	}
	else {
		m_listener->start();
		m_btnStopContinue->setText("Stop");
	}

}
