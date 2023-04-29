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
    qDebug();
    qDebug() << "Database::Verify";
    qDebug() << userName;
    qDebug() << password;

    QSqlQuery query;
    int result = 0;

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

QVector<User> Database::GetUsersList()
{
    qDebug();
    qDebug() << "Database::UsersListRequest";

    QSqlQuery query;
    QVector<User> users;
    int result;

    result = query.exec(QString("SELECT * FROM users"));

    if (!result)
    {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
        return {};
    }

    QSqlRecord rec = query.record();
    const int indexFullName = rec.indexOf( "full_name" );
    const int indexOffice = rec.indexOf( "office_id" );
    const int indexRight = rec.indexOf( "rights_id" );

    while (query.next())
    {
        User user;
        user.s_Full_Name = query.value(indexFullName).toString();
        user.s_Office = query.value(indexOffice).toString();
        user.s_Right = query.value(indexRight).toString();

        qDebug() << user.s_Full_Name;
        qDebug() << user.s_Right;
        qDebug() << user.s_Office;

        users.push_back(user);
    }

    return users;
}

User Database::GetUserData(QString username)
{
    qDebug();
    qDebug() << "Database::GetUserData";

    QSqlQuery query;
    User user;
    int result;

    query.prepare(QString("SELECT * FROM users WHERE full_name = :username"));

    query.bindValue(":username", username);

    result = query.exec();

    if (!result)
    {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
        return {};
    }

    QSqlRecord rec = query.record();
    const int indexFullName = rec.indexOf( "full_name" );
    const int indexOffice = rec.indexOf( "office_id" );
    const int indexRight = rec.indexOf( "rights_id" );

    if (query.next())
    {
        user.s_Full_Name = query.value(indexFullName).toString();
        user.s_Office = query.value(indexOffice).toString();
        user.s_Right = query.value(indexRight).toString();

        qDebug() << user.s_Full_Name;
        qDebug() << user.s_Right;
        qDebug() << user.s_Office;
    }

    return user;
}

QVector<Right> Database::GetRights()
{
    qDebug();
    qDebug() << "Database::GetRights";

    QSqlQuery query;
    QVector<Right> rights;
    int result;

    result = query.exec(QString("SELECT * FROM rights "));

    if (!result)
    {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
        return {};
    }

    QSqlRecord rec = query.record();
    //const int indexName = rec.indexOf( "name" );
    const int indexId = rec.indexOf( "id" );

    while (query.next())
    {
        Right right;

        right.s_Name = query.value(indexId).toString();

        rights.push_back(right);

        qDebug() << right.s_Name;
    }

    return rights;
}

QString Database::FindFreeDefaultName()
{
    QString userName = "User";

    qDebug();
    qDebug() << "Database::FindFreeDefaultName";

    QSqlQuery query;
    int result = 0;
    int it = 0;

    do
    {
        userName = (it++ == 0) ? QString("User") : QString("User%1").arg(it);

        query.prepare("SELECT * FROM users WHERE full_name = :name");

        query.bindValue(":name", userName);

        result = query.exec();

        if (!result)
        {
            qDebug() << query.lastQuery();
            qDebug() << query.lastError().text();
        }
    }
    while (query.next());

    return userName;
}

void Database::AddUser()
{
    qDebug();
    qDebug() << "Database::AddUser";

    auto name = FindFreeDefaultName();

    QSqlQuery query;
    int result = 0;
    int it = 0;

    query.prepare("INSERT INTO users (password, rights_id , full_name, office_id) VALUES (1111, 0, :name, 0) ");

    query.bindValue(":name", name);

    result = query.exec();

    if (!result)
    {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
    }
}
