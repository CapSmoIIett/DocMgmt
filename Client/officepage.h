#pragma once

#include <QObject>

#include <appengine.h>

class OfficePage: public QObject
{
    Q_OBJECT

    Q_PROPERTY(int id READ id WRITE setID)
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString address READ address WRITE setAddress)

public:
    OfficePage(AppEngine* engine, QObject *parent = nullptr);

    int id();
    void setID(const int &id);

    QString name();
    void setName(const QString &name);

    QString address();
    void setAddress(const QString &address);

    Q_INVOKABLE void loadOfficeRequest(int id);

public slots:
    void GetOffice(Office office);

signals:
    void getedOffice();

private:
    AppEngine* p_AppEngine;
    Office office;
};

