
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
    Q_PROPERTY(int id READ id WRITE setID)

public:
    UserPage(AppEngine* engine, QObject *parent = nullptr);

    QString userName();
    void setUserName(const QString &userName);

    QString office();
    void setOffice(const QString &password);

    QString right();
    void setRight(const QString &password);

    int id();
    void setID(const int &ip);

    Q_INVOKABLE void loadUserRequest(int id);
    Q_INVOKABLE void uploadData();

public slots:
    void GetUser(User user);
    void GetMessages(QVector<Message>);
    void GetMessage(Message msg);

signals:
    void getedUser();

private:
    AppEngine* p_AppEngine;
    User user;

    QVector<Message> v_Messages;
};

#endif // USERPAGE_H
