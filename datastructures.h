#pragma once

#include <QString>
#include <QDateTime>
#include <Qvector>


struct User
{
    int i_ID;
    QString s_Full_Name;
    QString s_Right;
    QString s_Office;
};


#define EDIT_USERS 0
#define EDIT_RIGHTS 1
#define EDIT_OFFICE 2
#define EDIT_HOLIDAYS 3
#define LAST_EDIT EDIT_HOLIDAYS

struct Right
{
    int i_ID;
    QString s_Name;
    int i_acs_lvl;
    bool rights[LAST_EDIT + 1];
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
    int i_acs_lvl;
    long i_Size;
};

struct Message
{
    QString text;
    QDateTime date_time;
    int sender;
    int recepient;
};

#define LOWEST_ACS_LVL 7
#define SEP "|"

#define KB 1024
