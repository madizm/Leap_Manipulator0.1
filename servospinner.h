#ifndef SERVOSPINNER_H
#define SERVOSPINNER_H

#include <QWidget>
#include <QtWidgets>

class ServoSpinner : public QWidget
{
    Q_OBJECT
public:
    explicit ServoSpinner(QWidget *parent = 0);
    ServoSpinner(QWidget *parent, int min, int max, int value, int No=0);
	~ServoSpinner();
private:
    QDial *m_dial;
    QLCDNumber *m_lcd;
    int m_No;

  //  void setRange(int min, int max);
signals:
    void valueChanged(int value, int No);
public slots:
    void setValue(int value);
	int getValue();
private slots:
	void setDeg(int deg);

};

#endif // SERVOSPINNER_H
