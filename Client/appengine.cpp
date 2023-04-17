#include "appengine.h"

AppEngine::AppEngine(QObject* parent) :
    QObject(parent)
{

}

QString AppEngine::UserName()
{
    return "user";
}

void AppEngine::setUserName(const QString &userName)
{

}

QString AppEngine::Password()
{
    return "password";
}

void AppEngine::setPassword(const QString &password)
{

}

bool AppEngine::Verify()
{
    return true;
}
