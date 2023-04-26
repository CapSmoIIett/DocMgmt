#pragma once

//#include <QSctpServer>
//#include <QSslServer>
//#include <QTcpServer>
//#include <QTcpSocket>

#include <QVector>
#include <QMap>
#include <QSet>

#include <QUdpSocket>
#include <QTcpSocket>
#include <QTcpServer>
#include <QObject>

#include <iostream>

#include "database.h"
#include "../messages.h"

struct _Client
{
    QTcpSocket* socket;
    QString ip;
};

class Server : public QObject //public QTcpServer
{
    Q_OBJECT

public:
    Server(int port = 5500);
    ~Server();
    //void incomingConnection(qintptr socketDescription);
    //void slotReadyRead();

    //void send(QString, int type);
    //void sendFile(QString fileName);

    void AppendToSocketLists(QTcpSocket* socket);

    void ProcessingMessage(QString header);

signals:
    void SendedClient(QString str);

public slots:
    //void read();
    //void IncomingConnection(qintptr socketDescriptor);
    void NewConnection();
    //void ReadyRead();

    void ReadSocket();
    void DiscardSocket();
    void DisplayError(QAbstractSocket::SocketError socketError);

    void SendToClient(QString str);

private:
    QSet<QTcpSocket*> set_Sockets;

    //QByteArray Data;
    //void SendToClient(QString);
    //void SendPartOfFile();

    QString GenerateToken(QString user);

    int i_Port;

    //QTcpSocket* p_TcpSocket;

    QTcpServer* p_Server;

    QMap<QString, QString> m_Tokens;

public:
    Database db;
};

