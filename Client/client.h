#pragma once

#include <iostream>

#include <QtSql/QSqlDatabase>
#include <QSqlQuery>

#include <QTcpServer>
#include <QTcpSocket>

#include "../messages.h"

class Client : public QObject
{
public:
    Client(QString ip = "127.0.0.1", int port = 5500);

    void ConnectToServer();
    bool IsConnected();
    void SendToServer(QString str);
    QString ReadFromServer();

    bool Verify (QString username, QString password);

public slots:
    void ReadyRead();

private:
    QTcpSocket* p_TcpSocket;
    QByteArray Data;

    QString s_IP;
    int i_Port;
};

