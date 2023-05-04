
#include "officepage.h"

OfficePage::OfficePage(AppEngine* engine, QObject *parent) :
    QObject{parent},
    p_AppEngine(engine)
{
    connect(&engine->GetClient(), &Client::onGetOffice, this, &OfficePage::GetOffice);
}

int OfficePage::id()
{
    return office.i_ID;
}

void OfficePage::setID(const int &id)
{
    office.i_ID = id;
}


QString OfficePage::name()
{
    return office.s_Name;
}

void OfficePage::setName(const QString &name)
{
    office.s_Name = name;
}

QString OfficePage::address()
{
    return office.s_Address;
}

void OfficePage::setAddress(const QString &address)
{
    office.s_Address = address;
}

void OfficePage::loadOfficeRequest(int id)
{
    qDebug();
    qDebug() << "OfficePage::loadOfficeRequest: " << id;

    p_AppEngine->loadOfficeRequest(id);
}

void OfficePage::GetOffice(Office office)
{
    this->office = office;
    emit getedOffice();
}

