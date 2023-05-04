#pragma once


#include <QObject>

#include <appengine.h>

class RightPage: public QObject
{
    Q_OBJECT

    Q_PROPERTY(int id READ id WRITE setID)
    Q_PROPERTY(QString name READ name WRITE setName)

public:
    RightPage(AppEngine* engine, QObject *parent = nullptr);

    int id();
    void  setID(const int &id);

    QString name();
    void setName(const QString &name);

    Q_INVOKABLE void loadRightRequest(int id);

public slots:
    void GetRight(Right right);

signals:
    void getedRight();

private:
    AppEngine* p_AppEngine;
    Right right;
};

