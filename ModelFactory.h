#pragma once
#include "Model.h"
#include "AS_6DOF.h"
#include <string>

using namespace std;
class ModelFactory
{
public:
	typedef enum MyEnum
	{
		AS6DOF
	}ROBOT_TYPE;

	ModelFactory();
	~ModelFactory();

	Model* createModel(ROBOT_TYPE type);
};

