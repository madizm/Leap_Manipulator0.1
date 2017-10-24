#include "mainwindow.h"
#include <QApplication>
#include <time.h>
#include <stdlib.h>
#include <iostream>

int randIn(int a, int b) {
	return (rand() % (b - a + 1)) + a;
}

int main(int argc, char *argv[])
{
	//大部分由Qt框架自动创建
    QApplication a(argc, argv);
	//注册三个自定义的消息类型
	qRegisterMetaType<Model::ERROR_TYPE>("ERROR_TYPE");
	qRegisterMetaType<VectorXf>("VectorXf");
	qRegisterMetaType<AS_6DOF::TRANS_TYPE>("TRANS_TYPE");
	//qRegisterMetaType<QImage>();

    MainWindow w;
    w.show();

    return a.exec();
/*	
	//运行效率测试代码
	const int scale = 1<<8;
	VectorXf arrVec[scale];
	for (int i = 0; i < scale; i++) {
		arrVec[i] = VectorXf(7);
	}
	std::cout << "test start" << std::endl;
	ModelFactory factory;
	AS_6DOF *as = (AS_6DOF*)factory.createModel(ModelFactory::AS6DOF);
	srand((unsigned)time(NULL));
	for (int i = 0; i < scale; i++) {
		arrVec[i] << randIn(0, 180), randIn(0, 180), randIn(0, 180),
			randIn(0, 200), randIn(0, 200), randIn(0, 200), randIn(0, 180) / 180.0;
	}
	time_t before, after;
	std::cout << "trans start" << std::endl;
	clock_t start_time = clock();
	for (int i = 0; i < scale; i++) {
		as->update(arrVec[i]);
	}
	clock_t end_time = clock();
	cout << "Running time is: " << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	//std::cout << "elapsed time " << difftime(after, before) << " seconds" << std::endl;
	getchar();
	return 0;*/
}
