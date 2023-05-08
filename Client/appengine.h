#pragma once

#include <QObject>
#include <QString>
#include <qqml.h>

#include <client.h>

class AppEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userName READ userName WRITE setUserName)
    Q_PROPERTY(QString password READ password WRITE setPassword)
    Q_PROPERTY(QString office READ office WRITE setOffice)
    Q_PROPERTY(QString right READ right WRITE setRight)

    Q_PROPERTY(QString ip READ ip WRITE setIP NOTIFY onChangeIP)

    QML_ELEMENT

public:
    explicit AppEngine(QObject *parent = nullptr);

    QString userName();
    void setUserName(const QString &userName);

    QString password();
    void setPassword(const QString &password);

    QString office();
    void setOffice(const QString &password);

    QString right();
    void setRight(const QString &password);

    QString ip();
    void setIP(const QString &ip);

    Client& GetClient();

    Q_INVOKABLE bool verify();
    Q_INVOKABLE void usersListRequest();
    Q_INVOKABLE void addUserRequest();

    Q_INVOKABLE void loadCurUserDataRequest();
    Q_INVOKABLE void loadUserDataRequest(int id);
    Q_INVOKABLE void loadRightsRequest();
    Q_INVOKABLE void addRightsRequest();
    Q_INVOKABLE void removeUserRequest(int id);
    Q_INVOKABLE void loadOfficesRequest();
    Q_INVOKABLE void addOfficesRequest();
    Q_INVOKABLE void loadOfficeRequest(int id);
    Q_INVOKABLE void loadRightRequest(int id);

    Q_INVOKABLE void loadFilesRequest(QString path);

    Q_INVOKABLE void downloadFileRequest(QString path, QString name);

    void uploadUserData(User user);


signals:
    void verified(bool result);
    void onChangeIP();

public slots:
    void GetCurUser(User user);

private:
    Client client;

    User user;
    QString s_Password;
    QString s_IP;

};

