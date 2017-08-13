#include "FrameListener.h"

FrameListener::FrameListener(Controller & _con, QObject *parent)
	: QThread(parent)
{
	running = false;
	numOberver = 0;
	observes = new Model*[MAXOBSERVER];
	con = _con;
	m_x = 0.0f;
	m_y = 97.0f*sinf(M_PI / 3);
	m_z = 97.0f*cosf(M_PI / 3) - 92.0f;
	m_R = 0.0f;
	m_P = 0.0f;
	m_Y = 0.0f;
	m_strength = 0.0f;
}

FrameListener::~FrameListener()
{
}

void FrameListener::addObserverModel(Model * m)
{
	numOberver++;
	if (numOberver >= MAXOBSERVER)
	{
		std::cout << "Can not Add more Obverser" << std::endl;
		return;
	}
	observes[numOberver - 1] = m;
	if (m->inherits("AS_6DOF")) {
		connect((AS_6DOF*)m, &AS_6DOF::errorOccurred, this, &FrameListener::reportError);
	//	connect((AS_6DOF*)m, &AS_6DOF::nextInfo, this, &FrameListener::reportNextInfo);
		connect((AS_6DOF*)m, &AS_6DOF::nextDeg, this, &FrameListener::reportNextDeg);
		connect((AS_6DOF*)m, &AS_6DOF::currentInfo, this, &FrameListener::reportCurrentInfo);
		connect(this, &FrameListener::nextInfo, (AS_6DOF*)m, &AS_6DOF::update);
	}
}

void FrameListener::stopListen()
{
	running = false;
}

bool FrameListener::isRunning()
{
	return running;
}

void FrameListener::run()
{
	running = true;
	while (running) {
		const Leap::Frame fr = con.frame();
		const Hand hand = fr.hands()[0];
		if (fr.hands().isEmpty()) {
			continue;
		}
	//	const Leap::Vector position = hand.palmPosition();
		const Leap::Vector position = hand.wristPosition();
		const Leap::Vector normal = hand.palmNormal();
		const Leap::Vector direction = hand.direction();

		const float R = normal.roll();
		const float P = direction.pitch();
		const float Y = direction.yaw();
		const float x = position.x;
		const float y = position.y;
		const float z = position.z;
		const float s = hand.grabStrength();
		m_x = x;
		m_y = y;
		m_z = z;
		m_R = R;
		m_P = P;
		m_Y = Y;
		m_strength = s;
		VectorXf vec = Eigen::VectorXf(7);
		vec << R, P, Y, x, y, z, s;
		emit nextInfo(vec);
	//	notify(vec);
		msleep(600);
	}
	running = false;
}

void FrameListener::reportError(const Model::ERROR_TYPE error)
{
	emit errorOccurred(error);
}

void FrameListener::reportNextInfo(const VectorXf info)
{
	emit nextInfo(info);
	m_R = info(0);
	m_P = info(1);
	m_Y = info(2);
	m_x = info(3);
	m_y = info(4);
	m_z = info(5);
	m_strength = info(6);
}

void FrameListener::reportNextDeg(const VectorXf infodeg)
{
	emit nextDeg(infodeg);
}

void FrameListener::reportCurrentInfo(VectorXf info)
{
	emit currentInfo(info);
}

void FrameListener::handleTrans(AS_6DOF::TRANS_TYPE trans)
{
	for (int i = 0; i < numOberver; i++) {
		if (observes[i]->inherits("AS_6DOF")) {
			((AS_6DOF*)observes[i])->handleTrans(trans);
		}
	}
}

void FrameListener::handleReset()
{
	for (int i = 0; i < numOberver; i++) {
		if (observes[i]->inherits("AS_6DOF")) {
			((AS_6DOF*)observes[i])->initModel();
		}
	}
}

void FrameListener::handleDegs(VectorXf deg)
{
	for (int i = 0; i < numOberver; i++) {
		if (observes[i]->inherits("AS_6DOF")) {
			((AS_6DOF*)observes[i])->setJointsDeg(deg);
		}
	}
}

void FrameListener::notify(VectorXf info)
{
	int i;
	for (i = 0; i<numOberver; i++)
	{
		observes[i]->update(info);
	}
}

VectorXf FrameListener::getInfo()
{
	VectorXf info(7);
	info << m_R, m_P, m_Y, m_x, m_y, m_z, m_strength;
	return info;
}
