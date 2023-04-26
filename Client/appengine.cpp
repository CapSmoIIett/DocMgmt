#include "appengine.h"

AppEngine::AppEngine(QObject* parent) :
    QObject(parent)
{
    connect(&this->client, &Client::Verified, this, [this](bool result) { qDebug() << "call"; emit this->verified(result); });

}

QString AppEngine::userName()
{
    return s_UserName;
}

void AppEngine::setUserName(const QString &userName)
{
    s_UserName = userName;
}

QString AppEngine::password()
{
    return s_Password;
}

void AppEngine::setPassword(const QString &password)
{
    s_Password = password;
}

bool AppEngine::verify()
{
    qDebug();
    qDebug() << "AppEngine::verify";
    qDebug() << s_UserName << " " << s_Password;

    if (!client.IsConnected())
        client.ConnectToServer();

    client.VerifyRequest(s_UserName, s_Password);

    return true;
}
