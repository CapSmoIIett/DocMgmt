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
    QML_ELEMENT

public:
    explicit AppEngine(QObject *parent = nullptr);

    QString userName();
    void setUserName(const QString &userName);

    QString password();
    void setPassword(const QString &password);

    Q_INVOKABLE bool verify();

signals:
    void verified(bool result);

private:
    Client client;

    QString s_UserName;
    QString s_Password;

};

