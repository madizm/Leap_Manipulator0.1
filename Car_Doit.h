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
	}TRANS_TYPE;
	Car_Doit(QObject *parent);
	~Car_Doit();
	void handleTrans(TRANS_TYPE trans, int factor = 100);
public slots:
	virtual int update(VectorXf info);
private:
	int setMotor(char method, int factor);
};
