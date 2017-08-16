#pragma once
#include <Eigen/Dense>
#define _USE_MATH_DEFINES
#include <math.h>
#include <Windows.h>
#include "SerialUtil.h"
#include <string>
#include <iostream>
#include <sstream>  
#include <QObject>
#include <QMetaType>
#include "Leap.h"

using namespace Eigen;
class Model : public QObject
{
	Q_OBJECT
public:
	typedef enum Enum {
		INVAILID_Z,
		CANT_REACH
	}ERROR_TYPE;
	Model(QObject *parent = 0);
	~Model();
	void setSerial(SerialUtil* serial);
	virtual int update(VectorXf) = 0;

protected:
	SerialUtil* serial;

signals:
	void errorOccurred(ERROR_TYPE error);
	void nextInfo(VectorXf info);
	void nextDeg(VectorXf info);

};
Q_DECLARE_METATYPE(Model::ERROR_TYPE);

