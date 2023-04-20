#include "appengine.h"

AppEngine::AppEngine(QObject* parent) :
    QObject(parent)
{

}

QString AppEngine::userName()
{
    return "user";
}

void AppEngine::setUserName(const QString &userName)
{

}

QString AppEngine::password()
{
    return "password";
}

void AppEngine::setPassword(const QString &password)
{

}

bool AppEngine::verify()
{
    qDebug() << "Verify" << "\n";

    return true;
}
