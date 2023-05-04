#include "appengine.h"

AppEngine::AppEngine(QObject* parent) :
    QObject(parent)
{
    connect(&this->client, &Client::onVerified, this, [this](bool result) { qDebug() << "call"; emit this->verified(result); });
    connect(&this->client, &Client::onGetUserData, this, &AppEngine::GetCurUser);

}

QString AppEngine::userName()
{
    return user.s_Full_Name;
}

void AppEngine::setUserName(const QString &userName)
{
    user.s_Full_Name = userName;
}

QString AppEngine::password()
{
    return s_Password;
}

void AppEngine::setPassword(const QString &password)
{
    s_Password = password;
}

QString AppEngine::office()
{
    return user.s_Office;
}

void AppEngine::setOffice(const QString &office)
{
    user.s_Office = office;
}

QString AppEngine::right()
{
    return user.s_Right;
}

void AppEngine::setRight(const QString &right)
{
    user.s_Right = right;
}

Client& AppEngine::GetClient()
{
    return client;
}

bool AppEngine::verify()
{
    qDebug();
    qDebug() << "AppEngine::verify";
    qDebug() << user.s_Full_Name << " " << s_Password;

    if (!client.IsConnected())
        client.ConnectToServer();

    client.VerifyRequest(user.s_Full_Name, s_Password);

    return true;
}

void AppEngine::usersListRequest()
{
    qDebug();
    qDebug() << "AppEngine::UsersListRequest";
    qDebug() << user.s_Full_Name << " " << s_Password;

    if (!client.IsConnected())
        client.ConnectToServer();

    client.UsersListRequest();
}

void AppEngine::addUserRequest()
{
    qDebug();
    qDebug() << "AppEngine::addUserRequest";
    qDebug() << user.s_Full_Name << " " << s_Password;

    client.AddUserRequest();
}

void AppEngine::loadCurUserDataRequest()
{
    client.loadUserDataRequest(user.s_Full_Name);
}

void AppEngine::loadUserDataRequest(int id)
{
    client.loadUserDataRequest(id);
}

void AppEngine::loadRightsRequest()
{
    client.loadRightsRequest();
}

void AppEngine::addRightsRequest()
{
    client.addRightsRequest();
}

void AppEngine::removeUserRequest(int id)
{
    client.removeUserRequest(id);
}

void AppEngine::loadOfficesRequest()
{
    client.loadOfficesRequest();
}

void AppEngine::addOfficesRequest()
{
    client.addOfficeRequest();
}

void AppEngine::loadOfficeRequest(int id)
{
    client.loadOfficeRequest(id);
}

void AppEngine::loadRightRequest(int id)
{
    client.loadRightRequest(id);
}


void AppEngine::GetCurUser(User user)
{
    if (user.i_ID == this->user.i_ID)
        this->user = user;
}


