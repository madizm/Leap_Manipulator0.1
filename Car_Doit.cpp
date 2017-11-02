#include "Car_Doit.h"

Car_Doit::Car_Doit(QObject *parent)
	: Model(parent)
{
}

Car_Doit::~Car_Doit()
{
}

void Car_Doit::handleTrans(TRANS_TYPE_CAR trans, int factor)
{
	switch (trans)
	{
	case FORWARD:
		setMotor('F', factor);
		break;
	case BACKWARD:
		setMotor('B', factor);
		break;
	case STEER_LEFT:
		setMotor('L', factor);
		break;
	case STEER_RIGHT:
		setMotor('R', factor);
		break;
	default:
		break;
	}
}

int Car_Doit::setMotor(char method, int factor)
{
	std::ostringstream ostr;
	ostr << method << ' ' << factor << ';';
	std::string s = ostr.str();
	std::cout << s << std::endl;
	int ret;
	if (serial != nullptr && serial->IsConnected()) {
		ret = serial->WriteData(s.c_str(), s.length());
		std::cout << ret << " bytes sent to the car" << std::endl;
	}
	else {
		std::cout << "no serial or serial is not connected to the car" << std::endl;
		ret = -1;
	}
	return ret;
}

int Car_Doit::update(VectorXf info)
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

	if (z <= 0)
	{
		std::cout << "z<=0 invailid" << std::endl;
		//emit errorOccurred(Model::INVAILID_Z);
		return -2;
	}

	float degP = P*Leap::RAD_TO_DEG;
	float degY = Y*Leap::RAD_TO_DEG;

	float ep = 10;
	if (degP > ep) {
		handleTrans(FORWARD);
	}
	else if (degP < -ep) {
		handleTrans(BACKWARD);
	}
	if (degY > ep) {
		handleTrans(STEER_LEFT);
	}
	else if (degY < -ep) {
		handleTrans(STEER_RIGHT);
	}
	return 0;
}
