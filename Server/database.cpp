#include "database.h"

#include "database.h"

#include <qrandom.h>

/*
        QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", "mydb");
       db.setHostName("DESKTOP-49Q6B8N");
       db.setDatabaseName("DocMgmt");
       db.setUserName("postgres");
       db.setPassword("1111");
       bool ok = db.open();
       std::cout << "BD connect: " << ok << "\n";

       QSqlQuery query;
       query.exec("INSERT INTO EMPLOYEE (Rights_id, Full_Name, Birth_date, Office_id, phone_number) VALUES (0, 'name2', TO_DATE('1/1/2000', 'DD/MM/YYYY'), 0, '11111111')");

 */

Database::Database(QObject *parent) :
    QObject(parent)
{
    db = QSqlDatabase::addDatabase("QPSQL");

    db.setDatabaseName("DocMgmt");
    db.setUserName("postgres");
    db.setPassword("1111");
    db.setHostName("localhost");
    //db.setHostName("127.0.0.1");
    //db.setPort(5434);

    qDebug() << QSqlDatabase::drivers() << "\n";

    db.open();

    if (db.isOpen())
    {
        qDebug("DB open");
    }
    else
    {
        qDebug("DB not open");
        qDebug() << db.lastError().text() << "\n";
    }

    createTables();
}

Database::~Database()
{
    db.close();
}

bool Database::createTables()
{

    /*****************************************************
     * Create tables
     */

    QSqlQuery query;
    bool result = 0;

    result = query.exec("CREATE TABLE IF NOT EXISTS users"
                "("
                    "id serial primary key,"
                    "password varchar(255) null,"
                    "rights_Id integer references Rights(Id),"
                    "full_Name varchar(255) null,"
                    "birth_Date date null,"
                    "office_Id integer references Office(Id),"
                    "phone_Number varchar(30)"
                ")");

    if (!result)
    {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
        return false;
    }

    result = query.exec("CREATE TABLE IF NOT EXISTS rights"
                "("
                    "id serial primary key"
                ")");

    if (!result)
    {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
        return false;
    }

    result = query.exec("CREATE TABLE IF NOT EXISTS office"
                "("
                    "id serial primary key"
                ")");

    if (!result)
    {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
        return false;
    }


    /*****************************************************
     * Add rights for supervisor
     */

    result = query.exec("SELECT * FROM rights WHERE id = 0");

    if (!result)
    {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
        return false;
    }

    if (!query.next())
    {
        result = query.exec("INSERT INTO rights (id) VALUES (0) ");

        if (!result)
        {
            qDebug() << query.lastQuery();
            qDebug() << query.lastError().text();
            return false;
        }
    }

    /*****************************************************
     * Add office for supervisor
     */

    result = query.exec("SELECT * FROM office WHERE id = 0");

    if (!result)
    {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
        return false;
    }

    if (!query.next())
    {
        result = query.exec("INSERT INTO office (id) VALUES (0) ");

        if (!result)
        {
            qDebug() << query.lastQuery();
            qDebug() << query.lastError().text();
            return false;
        }
    }

    /*****************************************************
     * Add supervisor
     */

    result = query.exec("SELECT * FROM users WHERE id = 0");

    if (!result)
    {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
        return false;
    }

    if (!query.next())
    {
        result = query.exec("INSERT INTO users (id, password, rights_id , full_name, office_id) VALUES (0, 1111, 0, 'supervisor', 0) ");

        if (!result)
        {
            qDebug() << query.lastQuery();
            qDebug() << query.lastError().text();
            return false;
        }
    }


    return true;
}

bool Database::Verify (QString userName, QString password)
{
    QSqlQuery query;
    int result = 0;

    qDebug();
    qDebug() << "Database::Verify";
    qDebug() << userName;
    qDebug() << password;

    result = query.exec(QString("SELECT password FROM users WHERE  full_name = '%1'").arg(userName));

    //query.exec("SELECT password FROM users WHERE  full_name = ':username'");
    //query.bindValue(":username", userName);
    //result =  query.exec();

    if (!result)
    {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
        return false;
    }

    QSqlRecord rec = query.record();
    const int index = rec.indexOf( "password" );

    if (query.next())
    {
        qDebug() << "Passwords: " << query.value(index).toString() << " " << password;
        return query.value(index).toString() == password;
    }

    return false;

}
