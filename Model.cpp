#include "Model.h"



Model::Model(QObject *parent):
	QObject(parent)
{
}


Model::~Model()
{
}

void Model::setSerial(SerialUtil * serial)
{
	this->serial = serial;
}
