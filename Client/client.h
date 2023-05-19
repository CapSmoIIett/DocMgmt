#pragma once

#include <iostream>

#include <QtSql/QSqlDatabase>
#include <QSqlQuery>

#include <QTcpServer>
#include <QTcpSocket>

#include <QTime>
#include <QFile>

#include "../logger.h"

#include "../encrypter.h"

#include "../messages.h"
#include "../datastructures.h"

class Client : public QObject
{
    Q_OBJECT

public:
    Client(QString ip = "127.0.0.1", int port = 5500);

    QString getIP();
    void setIP(const QString &ip);

    int getPort();
    void setPort(const int &port);

    bool IsConnected();
    void SendToServer(QString str);

    void SendRequest (QString);
    bool VerifyRequest (QString username, QString password);

    void UsersListRequest();
    void AddUserRequest();
    void loadUserDataRequest(QString username);
    void loadUserDataRequest(int id);
    void loadRightsRequest();
    void addRightsRequest();
    void removeUserRequest(int id);
    void loadOfficesRequest();
    void addOfficeRequest();
    void loadOfficeRequest(int id);
    void loadRightRequest(int id);


    void loadFilesRequest(QString);

    void downloadFileRequest(QString, int);
    void changeAccessLvlFileRequest(QString, int);

    void uploadUserData(User);
    void uploadRightData(Right);
    void uploadFile(QString name, QString text);

    void sendMessage(QString, int, int);
    void uploadMessages(int, int);

signals:
    void onVerified(bool result);
    void onGetUsersList(QVector<User>);
    void onGetUserData(User);
    void onGetRights(QVector<Right>);
    void onGetOffices(QVector<Office>);
    void onGetRight(Right);
    void onGetOffice(Office);
    void onGetFiles(QVector<File>);
    void onGetMessages(QVector<Message>);
    void onGetMessage(Message);

public slots:
    void ConnectToServer();
    void ReadSocket();
    void DiscardSocket();


private:
    QTcpSocket* p_TcpSocket;
    QByteArray Data;

    QString s_IP;
    int i_Port;

    Encrypter encrypter;

};

