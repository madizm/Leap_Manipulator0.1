#ifndef SERVER_CAMERA_H
#define SERVER_CAMERA_H

#include <QObject>
#include <QtNetwork>

class Server_Camera : public QObject
{
    Q_OBJECT
public:
    Server_Camera();

private:
    QTcpServer *tcpServer;
    QTcpSocket *tcpServerConnection;

    const quint8 HEADSIZE = 16;
    const quint8 NUMBUF = 16;
    QByteArray *m_arrBuf;
    quint32 m_nImageSize;
    QByteArray m_bufImage;

private slots:
    void receiveImage();
    void acceptConnection();
    void displayError(QAbstractSocket::SocketError socketError);

public:
//    void displayImage();
    QByteArray getImageBuf();

signals:
    void readyDisplay();
//    void readyReceive();
};

#endif // SERVER_CAMERA_H
