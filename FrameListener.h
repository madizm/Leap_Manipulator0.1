#pragma once

#include <QThread>
#include <iostream>
#include <cstring>
#include "Leap.h"
#include "Model.h"
#include "AS_6DOF.h"
#include "Car_Doit.h"
#include <Windows.h>

using namespace Leap;
class FrameListener : public QThread
{
	Q_OBJECT

public:
	FrameListener(Controller& _con, QObject *parent = 0);
	~FrameListener();

	void addObserverModel(Model* m);
	void stopListen();
	bool isRunning();
	void notify(VectorXf info);
	VectorXf getInfo();

protected:
	void run();
private:

	bool running;
	int numOberver;
	const static int MAXOBSERVER = 5;
	Model** observes;
	Controller con;

	float m_x, m_y, m_z, m_R, m_P, m_Y, m_strength;

signals:
	void errorOccurred(Model::ERROR_TYPE error);
	void nextInfo(VectorXf info);
	void nextDeg(VectorXf info);
	void currentInfo(VectorXf info);

//���²����ڷ����ź�
private slots:
	void reportError(Model::ERROR_TYPE error);
	void reportNextInfo(VectorXf info);
	void reportNextDeg(VectorXf infodeg);
	void reportCurrentInfo(VectorXf info);

public slots:
	//����spinner��deg�ź�
	void handleDegs(VectorXf deg);
	//����control panel��ת��
	void handleTrans(AS_6DOF::TRANS_TYPE trans, int factor = 10);
	void handleTrans_car(Car_Doit::TRANS_TYPE_CAR trans, int factor = 100);
	void handleReset();
};