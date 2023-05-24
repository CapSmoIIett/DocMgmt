#pragma once


#include <QObject>

#include "appengine.h"

class RightPage: public QObject
{
    Q_OBJECT

    Q_PROPERTY(int id READ id WRITE setID)
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(int lvl READ lvl WRITE setLvl)

public:
    RightPage(AppEngine* engine, QObject *parent = nullptr);

    int id();
    void  setID(const int &id);

    QString name();
    void setName(const QString &name);

    int lvl();
    void  setLvl(const int &id);

    Q_INVOKABLE void loadRightRequest(int id);
    Q_INVOKABLE void uploadData();

public slots:
    void GetRight(Right right);

signals:
    void getedRight();

private:
    AppEngine* p_AppEngine;
    Right right;
};

