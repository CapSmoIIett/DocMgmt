#pragma once

//#include <QSctpServer>
//#include <QSslServer>
//#include <QTcpServer>
//#include <QTcpSocket>

#include <QVector>

#include <QUdpSocket>
#include <QTcpSocket>
#include <QTcpServer>
#include <QObject>

#include <iostream>

#include "messages.h"

class Server : public QTcpServer
{
    //Q_OBJECT

public:
    Server(int port = 5500);
    //void incomingConnection(qintptr socketDescription);
    //void slotReadyRead();

    void send(QString, int type);
    //void sendFile(QString fileName);

public slots:
    void read();
    void IncomingConnection(qintptr socketDescriptor);
    void ReadyRead();

private:
    QVector<QTcpSocket*> v_Sockets;
    QByteArray Data;
    void SendToClient(QString);
    void SendPartOfFile();

    int i_Port;
    QUdpSocket* p_UdpSocket;
    QTcpSocket* p_TcpSocket;
};

