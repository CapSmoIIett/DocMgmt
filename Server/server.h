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

#include <QTime>

#include <iostream>


#include "database.h"
#include "filebase.h"
#include "../messages.h"

#include "../encrypter.h"
#include "../logger.h"

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
    void SendWarning(QString text);

signals:
    void SendedClient(QString str);
    void SendedSpecificClient(QTcpSocket* socket, QString str);

public slots:
    //void read();
    //void IncomingConnection(qintptr socketDescriptor);
    void NewConnection();
    //void ReadyRead();

    void ReadSocket();
    void DiscardSocket();
    void DisplayError(QAbstractSocket::SocketError socketError);

    void SendToClient(QString str);
    void SendToClient(QByteArray str);
    void SendToSpecificClient(QTcpSocket* socket, QString str);


private:
    QSet<QTcpSocket*> set_Sockets;
    QMap<QTcpSocket*, User> map_Users;

    QString GenerateToken(QString user);

    int i_Port;

    QTcpServer* p_Server;

    QMap<QString, QString> m_Tokens;

public:
    Database db;
    Filebase fb;

    Encrypter encrypter;
};

