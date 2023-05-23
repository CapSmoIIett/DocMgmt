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
    User GetUserData(int id);
    QVector<Right> GetRights();



    QString FindFreeDefaultName(QString table = "users", QString param = "full_name", QString name = "User");
    void AddUser();
    void AddRight();
    void AddOffice();

    void RemoveUser(int id);

    QVector<Office> GetOffices();

    Office GetOffice(int id);
    Right GetRight(int id);

    int GetID(QString table, QString field, QString value);
    void UpdateUserData(User);
    void UpdateRightData(Right);
    int GetUserAccessLvl(int id);


    void SaveMsg(QString, int, int);
    QVector<Message> GetMessages(int, int);

    std::tuple<QVector<QString>, QVector<QVector<QDate>>> GetHolidays(int, int);
    int GetUserID(QString name);
    void SetHoliday(QDate, int);

private:
    // Сам объект базы данных, с которым будет производиться работа
    QSqlDatabase    db;

public:
    /* Внутренние методы для работы с базой данных
     * */
    bool createTables();
};
