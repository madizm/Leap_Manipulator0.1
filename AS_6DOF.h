#pragma once
#include "Model.h"
class AS_6DOF :
	public Model
{
	Q_OBJECT

public:
	typedef enum Enum {
		FORWARD,
		BACKWARD,
		UP,
		DOWN,
		LEFT,
		RIGHT,
		ROLL,
		ROLLA,
		GRAB
	}TRANS_TYPE;
	AS_6DOF(QObject *parent = 0);
	~AS_6DOF();
	void setJointsDeg(VectorXf deg);
	void handleTrans(TRANS_TYPE trans, int factor = 10);
public slots:
	virtual void update(VectorXf info);
	void initModel();

private:
	float l1, l2, l3;
	bool translate2DEG(VectorXf infoIN, VectorXf &infoOUT);
	float m_x, m_y, m_z, m_R, m_P, m_Y, m_strength;
	float m_q0, m_q1, m_q2, m_q3, m_q4, m_q5;
	bool m_bGrabed = false;
public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

signals :
	void errorOccurred(ERROR_TYPE error);
	void nextInfo(VectorXf info);
	void nextDeg(VectorXf info);
	void currentInfo(VectorXf info);
//public slots:
//	void setJointsDeg(VectorXf deg);
};
Q_DECLARE_METATYPE(AS_6DOF::TRANS_TYPE);
