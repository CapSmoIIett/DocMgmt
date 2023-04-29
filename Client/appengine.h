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

    Client& GetClient();

    Q_INVOKABLE bool verify();
    Q_INVOKABLE void usersListRequest();
    Q_INVOKABLE void addUserRequest();

    Q_INVOKABLE void loadCurUserDataRequest();
    Q_INVOKABLE void loadUserDataRequest();
    Q_INVOKABLE void loadRightsRequest();

signals:
    void verified(bool result);

public slots:

private:
    Client client;

    User user;
    QString s_Password;

};

