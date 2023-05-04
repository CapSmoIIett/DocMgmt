
#ifndef USERPAGE_H
#define USERPAGE_H


#include <QObject>

#include <appengine.h>

class UserPage: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString userName READ userName WRITE setUserName)
    Q_PROPERTY(QString office READ office WRITE setOffice)
    Q_PROPERTY(QString right READ right WRITE setRight)

public:
    UserPage(AppEngine* engine, QObject *parent = nullptr);

    QString userName();
    void setUserName(const QString &userName);

    QString office();
    void setOffice(const QString &password);

    QString right();
    void setRight(const QString &password);

    Q_INVOKABLE void loadUserRequest(int id);

public slots:
    void GetUser(User user);

signals:
    void getedUser();

private:
    AppEngine* p_AppEngine;
    User user;
};

#endif // USERPAGE_H
