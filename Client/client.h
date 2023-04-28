#pragma once

#include <iostream>

#include <QtSql/QSqlDatabase>
#include <QSqlQuery>

#include <QTcpServer>
#include <QTcpSocket>

#include "../messages.h"
#include "../datastructures.h"

class Client : public QObject
{
    Q_OBJECT

public:
    Client(QString ip = "127.0.0.1", int port = 5500);

    void ConnectToServer();
    bool IsConnected();
    void SendToServer(QString str);
    QString ReadFromServer();

    void SendRequest (QString);
    bool VerifyRequest (QString username, QString password);

    void UsersListRequest();
    void AddUserRequest();
    void loadUserDataRequest(QString username);

signals:
    void onVerified(bool result);
    void onGetUsersList(QVector<User>);
    void onGetUserData(User);

public slots:
    void ReadSocket();
    void DiscardSocket();


private:
    QTcpSocket* p_TcpSocket;
    QByteArray Data;

    QString s_IP;
    int i_Port;
};

