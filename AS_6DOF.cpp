#include "AS_6DOF.h"



AS_6DOF::AS_6DOF(QObject *parent):
	Model(parent)
{
	serial = nullptr;
	initModel();
}


AS_6DOF::~AS_6DOF()
{

}
//接收vector6f
void AS_6DOF::setJointsDeg(VectorXf deg) {
	float degq0 = deg(0);
	float degq1 = deg(1);
	float degq2 = deg(2);
	float degq3 = deg(3);
	float degq4 = deg(4);
	float strength = deg(5);

	m_x = (l2*cos((degq1 + degq2)*Leap::DEG_TO_RAD) + l1*cos(degq1*Leap::DEG_TO_RAD))*sin(degq0*Leap::DEG_TO_RAD);
	m_y = l2*sin((degq1 + degq2)*Leap::DEG_TO_RAD) + l1*sin(degq1*Leap::DEG_TO_RAD);
	m_z = (l2*cos((degq1 + degq2)*Leap::DEG_TO_RAD) + l1*cos(degq1*Leap::DEG_TO_RAD))*cos(degq0*Leap::DEG_TO_RAD);
	m_R = degq4*Leap::DEG_TO_RAD;
	m_P = degq3*Leap::DEG_TO_RAD;
	m_strength = strength;
	//m_Y = degq0*Leap::DEG_TO_RAD;

	VectorXf newInfo(7);
	newInfo << m_R*Leap::RAD_TO_DEG, m_P*Leap::RAD_TO_DEG, m_Y*Leap::RAD_TO_DEG, m_x, m_y, m_z, m_strength;
	emit currentInfo(newInfo);
	//发射vector6fDegree
	emit nextDeg(deg);

	m_q0 = degq0;
	m_q1 = degq1;
	m_q2 = degq2;
	m_q3 = degq3;
	m_q4 = degq4;
	m_q5 = strength;

	////算出舵机需要的参数
	int q0 = 1500 + 10 * degq0;
	int q1 = 1750 - 10 * (degq1 - 60);
	int q2 = 900 - 10 * (degq2 - 120);
	int q3 = 2150 + 10 * (degq3 + degq1 + degq2 - 180);
	int q4 = 1550 - 10 * degq4;
	int q5 = 1000 - (1500 - 500)*strength;

	std::ostringstream ostr;
	ostr << q0 << " " << q1 << " " << q2 << " " << q3 << " " << q4 << " " << q5 << ';';
	std::string s = ostr.str();
	std::cout << s << std::endl;

	if (serial != nullptr && serial->IsConnected())
		std::cout << serial->WriteData(s.c_str(), s.length()) << " bytes sent" << std::endl;
	else
		std::cout << "no serial or serial is not connected" << std::endl;
}

void AS_6DOF::handleTrans(TRANS_TYPE trans)
{
	float q = 0.0f;
	switch (trans)
	{
	case FORWARD:
		q = atanf(m_x / m_z);
		m_x -= 10 * sinf(q);
		m_z -= 10 * cosf(q);
		break;
	case BACKWARD:
		q = atanf(m_x / m_z);
		m_x += 10 * sinf(q);
		m_z += 10 * cosf(q);
		break;
	case UP:
		m_y += 10;
		break;
	case DOWN:
		m_y -= 10;
		break;
	default:
		break;
	}
	VectorXf info(7);
	info << m_R, m_P, m_Y, m_x, m_y, m_z, m_strength;
	update(info);
}

void AS_6DOF::update(VectorXf info)
{
	float R = info(0);
	float P = info(1);
	float Y = info(2);
	float x = info(3);
	float y = info(4);
	float z = info(5);
	float strength = info(6);
	std::cout << "R: " << R*Leap::RAD_TO_DEG << "   P: " << P*Leap::RAD_TO_DEG << "   Y:" << Y*Leap::RAD_TO_DEG
		<< "   x: " << x << "   y:" << y << "   z: " << z << "   strength: " << strength << std::endl; 
//	emit nextInfo(info);

	VectorXf vecOUT(6);
	if (!translate2DEG(info, vecOUT)) {
		return;
	}
	m_Y = Y;
	/*m_R = R;
	m_P = P;
	m_Y = Y;
	m_x = x;
	m_y = y;
	m_z = z;
	m_strength = strength;
	

	m_q0 = vecOUT(0);
	m_q1 = vecOUT(1);
	m_q2 = vecOUT(2);
	m_q3 = vecOUT(3);
	m_q4 = vecOUT(4);
	m_q5 = vecOUT(5);*/
	setJointsDeg(vecOUT);

}

void AS_6DOF::initModel()
{
	l1 = 97.0f;
	//l2 = 120.0;
	//l3 = 5.0;
	l2 = 92.0f;
	l3 = 30.0f;

	m_q0 = 0.0f;
	m_q1 = 60.0f;
	m_q2 = 120.0f;
	m_q3 = 0.0f;
	m_q4 = 0.0f;
	m_q5 = 0.0f;

	m_x = 0.0f;
	m_y = l1*sinf(M_PI / 3);
	m_z = l1*cosf(M_PI / 3) - l2;
	//以弧度记录
	m_R = 0.0f;
	m_P = 0.0f;
	m_Y = 0.0f;
	m_strength = 0.0f;

	VectorXf info(7);
	info << m_R, m_P, m_Y, m_x, m_y, m_z, m_strength;
	update(info);
}

//输入(RPYxyzs)输出(q0,q1,q2,q3,q4,q5)返回是否转换成功
bool AS_6DOF::translate2DEG(VectorXf infoIN, VectorXf &infoOUT)
{
	float R = infoIN(0);
	float P = infoIN(1);
	float Y = infoIN(2);
	float x = infoIN(3);
	float y = infoIN(4);
	float z = infoIN(5);
	float s = infoIN(6);

	if (z >= 0)
	{
		std::cout << "z>=0 invailid" << std::endl;
		emit errorOccurred(Model::INVAILID_Z);
		return false;
	}
	//////算法部分
	float qq0;
	qq0 = atanf(x / z);//底座旋转角度

	//float fac = 0.8f;//扩大人手可移动的范围
	//x = x*fac;
	//y = y*fac;
	//z = z*fac;

	float zz0 = -sqrtf(z*z + x*x);//手腕到原点在水平面投影的长度

	float A = y ;
	float B = zz0 ;

	float t = (A*A + B*B - l1*l1 - l2*l2) / (2 * l1*l2);
	if (t>1) {
		std::cout << "Can Not Reach!!" << std::endl;
		emit errorOccurred(Model::CANT_REACH);
		return false;
	}
	float theta2 = acosf(t);

	float p = l1 + l2*cos(theta2);
	float q = l2*sin(theta2);
	t = (p*A - q*B) / (p*p + q*q);
	if (t>1) {
		std::cout << "Can Not Reach!!" << std::endl;
		emit errorOccurred(Model::CANT_REACH);
		return false;
	}
	float theta1 = asinf(t);//asin的区间与要求不一致

	if(abs(l1*sinf(theta1)+l2*sinf(theta1+theta2)-A)>5.0f)
		theta1 = M_PI - asinf(t);
/*
	m_x = (l2*cos(theta1 + theta2) + l1*cos(theta1))*sin(qq0);
	m_y = l2*sin(theta1 + theta2) + l1*sin(theta1);
	m_z = (l2*cos(theta1 + theta2) + l1*cos(theta1))*cos(qq0);
*/


	std::cout << qq0*Leap::RAD_TO_DEG << " " << theta1*Leap::RAD_TO_DEG << " " 
		<< theta2*Leap::RAD_TO_DEG << " " << P*Leap::RAD_TO_DEG << " " << R*Leap::RAD_TO_DEG << std::endl;

	infoOUT << qq0*Leap::RAD_TO_DEG, theta1*Leap::RAD_TO_DEG, theta2*Leap::RAD_TO_DEG,
		P*Leap::RAD_TO_DEG, R*Leap::RAD_TO_DEG, s;

	return true;
}
