
#include "userpage.h"

UserPage::UserPage(AppEngine* engine, QObject *parent) :
    QObject{parent},
    p_AppEngine(engine)
{
    connect(&engine->GetClient(), &Client::onGetUserData, this, &UserPage::GetUser);
}

QString UserPage::userName()
{
    return user.s_Full_Name;
}

void UserPage::setUserName(const QString &userName)
{
    user.s_Full_Name = userName;
}


QString UserPage::office()
{
    return user.s_Office;
}

void UserPage::setOffice(const QString &office)
{
    user.s_Office = office;
}

QString UserPage::right()
{
    return user.s_Right;
}

void UserPage::setRight(const QString &right)
{
    user.s_Right = right;
}

int UserPage::id()
{
    return user.i_ID;
}

void UserPage::setID(const int &id)
{
    user.i_ID = id;
}

void UserPage::loadUserRequest(int id)
{
    qDebug();
    qDebug() << "UserPage::loadUserRequest: " << id;

    p_AppEngine->loadUserDataRequest(id);
}

void UserPage::uploadData()
{
    qDebug();
    qDebug() << "UserPage::uploadData";
    qDebug() << user.i_ID;
    qDebug() << user.s_Full_Name;
    qDebug() << user.s_Right;
    qDebug() << user.s_Office;

    p_AppEngine->uploadUserData(user);
}

void UserPage::GetUser(User user)
{
    this->user = user;
    emit getedUser();
}

void UserPage::GetMessages(QVector<Message> messages)
{
    v_Messages = messages;
}

void UserPage::GetMessage(Message msg)
{
    v_Messages.push_back(msg);
}
