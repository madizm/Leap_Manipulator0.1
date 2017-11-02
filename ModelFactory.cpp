#include "ModelFactory.h"



ModelFactory::ModelFactory()
{
}


ModelFactory::~ModelFactory()
{
}

Model * ModelFactory::createModel(ROBOT_TYPE type)
{
	Model* model = nullptr;
	switch (type)
	{
	case AS6DOF:
		model = new AS_6DOF();
		break;
	case CAR_DOIT:
		model = new Car_Doit();
		break;
	default:
		break;
	}
	return model;
}
