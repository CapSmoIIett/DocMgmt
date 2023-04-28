#pragma once

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QFile>
#include <QDate>
#include <QDebug>

#include "../datastructures.h"

/* Директивы имен таблицы, полей таблицы и базы данных */
#define DATABASE_HOSTNAME   "ExampleDataBase"
#define DATABASE_NAME       "DataBase.db"

#define TABLE_EMPLOYEE				"employee"
#define TABLE_EMPLOYEE_NAME			"full_name"
#define TABLE_EMPLOYEE_OFFICE		"office"
//#define TABLE_EMPLOYEE_PROFESSION	"profession"

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = 0);
    ~Database();

    bool Verify (QString userName, QString password);
    QVector<User> GetUsersList();
    User GetUserData(QString username);

    QString FindFreeDefaultName();
    void AddUser();


private:
    // Сам объект базы данных, с которым будет производиться работа
    QSqlDatabase    db;

public:
    /* Внутренние методы для работы с базой данных
     * */
    bool createTables();
};
