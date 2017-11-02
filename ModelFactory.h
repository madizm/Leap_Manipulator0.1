#pragma once
#include "Model.h"
#include "AS_6DOF.h"
#include "Car_Doit.h"
#include <string>

using namespace std;
class ModelFactory
{
public:
	typedef enum MyEnum
	{
		AS6DOF,
		CAR_DOIT
	}ROBOT_TYPE;

	ModelFactory();
	~ModelFactory();

	Model* createModel(ROBOT_TYPE type);
};

