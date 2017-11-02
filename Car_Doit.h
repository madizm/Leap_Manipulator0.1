#pragma once

#include <QObject>
#include"Model.h"

class Car_Doit : public Model
{
	Q_OBJECT

public:
	typedef enum Enum {
		FORWARD,
		BACKWARD,
		STEER_LEFT,
		STEER_RIGHT
	}TRANS_TYPE_CAR;
	Car_Doit(QObject *parent = 0);
	~Car_Doit();
	void handleTrans(TRANS_TYPE_CAR trans, int factor = 100);
public slots:
	virtual int update(VectorXf info);
private:
	int setMotor(char method, int factor);
};
Q_DECLARE_METATYPE(Car_Doit::TRANS_TYPE_CAR);
