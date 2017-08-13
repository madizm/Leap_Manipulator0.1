#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	qRegisterMetaType<Model::ERROR_TYPE>("ERROR_TYPE");
	qRegisterMetaType<VectorXf>("VectorXf");
	qRegisterMetaType<AS_6DOF::TRANS_TYPE>("TRANS_TYPE");
    MainWindow w;
    w.show();

    return a.exec();
}
