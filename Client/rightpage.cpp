
#include "rightpage.h"


RightPage::RightPage(AppEngine* engine, QObject *parent) :
    QObject{parent},
    p_AppEngine(engine)
{
    connect(&engine->GetClient(), &Client::onGetRight, this, &RightPage::GetRight);
}

int RightPage::id()
{
    return right.i_ID;
}

void RightPage::setID(const int &id)
{
    right.i_ID = id;
}

QString RightPage::name()
{
    return right.s_Name;
}

void RightPage::setName(const QString &name)
{
    right.s_Name = name;
}

int RightPage::lvl()
{
    return right.i_acs_lvl;
}

void RightPage::setLvl(const int &lvl)
{
    right.i_acs_lvl = lvl;
}

void RightPage::loadRightRequest(int id)
{
    qDebug();
    qDebug() << "RightPage::loadRightRequest: " << id;

    p_AppEngine->loadRightRequest(id);
}

void RightPage::uploadData()
{
    p_AppEngine->uploadRightData(right);
}

void RightPage::GetRight(Right right)
{
    this->right = right;
    emit getedRight();
}

