#include "server_camera.h"

Server_Camera::Server_Camera()
{
    tcpServer = new QTcpServer(this);
    m_nImageSize = 0;
    m_arrBuf = new QByteArray[NUMBUF];
    if(!tcpServer->listen(QHostAddress::Any, 8002))
    {
        qDebug()<<tcpServer->errorString();
    }
    //emit readyReceive ();
    connect (tcpServer, &QTcpServer::newConnection, this, &Server_Camera::acceptConnection);
}


void Server_Camera::acceptConnection ()
{
    qDebug()<<"accept new connection";
    tcpServerConnection = tcpServer->nextPendingConnection ();
    connect(tcpServerConnection, SIGNAL(readyRead()),this, SLOT(receiveImage()));
    connect(tcpServerConnection, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
}

void Server_Camera::receiveImage ()
{
    if(m_nImageSize==0){
        if(tcpServerConnection->bytesAvailable () < HEADSIZE)
            return;
        QByteArray buf = tcpServerConnection->read (HEADSIZE);
        m_nImageSize = buf.toUInt ();
    }

    if(tcpServerConnection->bytesAvailable () < m_nImageSize){
        return;
    }
    emit readyDisplay();
    //might have problem here
    m_nImageSize = 0;
}

QByteArray Server_Camera::getImageBuf ()
{
    return m_bufImage;
}

//void Server_Camera::displayImage ()
//{
//    QByteArray data = tcpServerConnection->read (m_nImageSize);
//    QBuffer buf(&data);
//    buf.open (QIODevice::ReadOnly);

//    QImageReader reader(&buf, "jpg");
//    QImage image = reader.read ();

//    ui->label_image->setPixmap (QPixmap::fromImage (image));

//    m_nImageSize = 0;
////    cv::Mat rawMat(cv::Size(480, 640), CV_8UC3, bytesData.data ());
////    cv::Mat image = cv::imdecode (rawMat, CV_LOAD_IMAGE_COLOR);
////    cv::imshow ("show", image);
//}

void Server_Camera::displayError (QAbstractSocket::SocketError socketError)
{
    qDebug() << tcpServerConnection->errorString();
    tcpServerConnection->close();
}
