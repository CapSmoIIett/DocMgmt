#pragma once

#include <iostream>

#include <QtSql/QSqlDatabase>
#include <QSqlQuery>

#include <QTcpServer>
#include <QTcpSocket>

#include "../messages.h"

class Client : public QObject
{
    Q_OBJECT

public:
    Client(QString ip = "127.0.0.1", int port = 5500);

    void ConnectToServer();
    bool IsConnected();
    void SendToServer(QString str);
    QString ReadFromServer();

    bool VerifyRequest (QString username, QString password);

signals:
    void Verified(bool result);

public slots:
    void ReadSocket();
    void DiscardSocket();


private:
    QTcpSocket* p_TcpSocket;
    QByteArray Data;

    QString s_IP;
    int i_Port;
};

