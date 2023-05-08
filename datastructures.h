#pragma once

#include <QString>
#include <QDateTime>


struct User
{
    int i_ID;
    QString s_Full_Name;
    QString s_Right;
    QString s_Office;
};

struct Right
{
    int i_ID;
    QString s_Name;
};

struct Office
{
    int i_ID;
    QString s_Name;
    QString s_Address;
};


const QString fileDateFormate = "yyyy-MM-dd HH:mm:ss";

struct File
{
    QString s_Name;
    QDateTime dt_DateModified;
    QString s_Type;
    long i_Size;
};
