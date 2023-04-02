#pragma once

//#include <QSctpServer>
//#include <QSslServer>
//#include <QTcpServer>
//#include <QTcpSocket>
#include <QVector>

class Server //: public QTcpServer
{
    //Q_OBJECT

public:
    Server();
    void incomingConnection(qintptr socketDescription);
    void slotReadyRead();

private:
    //QVector<QTcpSocket> Sockets;
    QByteArray Data;
    void SendToClient();
};

