#include "database.h"

#include "database.h"

#include <qrandom.h>


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
                    "id serial primary key,"
                    "name varchar(255),"
                    "access_lvl int,"
                    "allow_edit_users boolean default 'f',"
                    "allow_edit_rights boolean default 'f',"
                    "allow_edit_office boolean default 'f',"
                    "allow_edit_holidays boolean default 'f'"
                ")");

    if (!result)
    {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
        return false;
    }

    result = query.exec("CREATE TABLE IF NOT EXISTS office"
                "("
                    "id serial primary key,"
                    "name varchar(255),"
                    "address varchar(255)"
                ")");

    if (!result)
    {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
        return false;
    }

    result = query.exec("CREATE TABLE IF NOT EXISTS messages"
                "("
                    "id_sender int,"
                    "id_recipient int,"
                    "name varchar(255),"
                    "date_time timestamp"
                ")");

    if (!result)
    {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
        return false;
    }

    result = query.exec("CREATE TABLE IF NOT EXISTS holidays"
                "("
                    "id_user int NOT NULL,"
                    "date date NOT NULL"
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
        result = query.exec("INSERT INTO rights (id, name, access_lvl, allow_edit_users, allow_EDIT_RIGHTS, allow_edit_office, allow_edit_holidays)"
            "VALUES (0, 'supervisor', 0, 't','t','t','t') ");

        if (!result)
        {
            qDebug() << query.lastQuery();
            qDebug() << query.lastError().text();
            return false;
        }
    }

    //allow_edit_users, allow_EDIT_RIGHTS, allow_edit_office, allow_edit_holidays

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
    const int indexID = rec.indexOf( "id" );
    const int indexFullName = rec.indexOf( "full_name" );
    const int indexOffice = rec.indexOf( "office_id" );
    const int indexRight = rec.indexOf( "rights_id" );

    while (query.next())
    {
        User user;
        user.i_ID = query.value(indexID).toInt();
        user.s_Full_Name = query.value(indexFullName).toString();
        user.s_Office = query.value(indexOffice).toString();
        user.s_Right = query.value(indexRight).toString();

        qDebug() << user.i_ID;
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
    qDebug() << "Database::GetUserData (username)";

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
    const int indexID = rec.indexOf( "id" );
    const int indexFullName = rec.indexOf( "full_name" );
    const int indexOffice = rec.indexOf( "office_id" );
    const int indexRight = rec.indexOf( "rights_id" );

    if (query.next())
    {
        user.i_ID = query.value(indexID).toInt();
        user.s_Full_Name = query.value(indexFullName).toString();
        user.s_Office = query.value(indexOffice).toString();
        user.s_Right = query.value(indexRight).toString();

        qDebug() << user.i_ID;
        qDebug() << user.s_Full_Name;
        qDebug() << user.s_Right;
        qDebug() << user.s_Office;
    }

    return user;
}

User Database::GetUserData(int id)
{
    qDebug();
    qDebug() << "Database::GetUserData (id)";

    QSqlQuery query;
    User user;
    int result;

    query.prepare(QString("SELECT * FROM users WHERE id = :id"));

    query.bindValue(":id", id);

    result = query.exec();

    if (!result)
    {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
        return {};
    }

    QSqlRecord rec = query.record();
    const int indexID = rec.indexOf( "id" );
    const int indexFullName = rec.indexOf( "full_name" );
    const int indexOffice = rec.indexOf( "office_id" );
    const int indexRight = rec.indexOf( "rights_id" );

    if (query.next())
    {
        user.i_ID = query.value(indexID).toInt();
        user.s_Full_Name = query.value(indexFullName).toString();
        user.s_Office = query.value(indexOffice).toString();
        user.s_Right = query.value(indexRight).toString();

        qDebug() << user.i_ID;
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
    const int indexName = rec.indexOf( "name" );
    const int indexLVL = rec.indexOf( "access_lvl" );
    const int indexEditUser = rec.indexOf( "allow_edit_users" );
    const int indexEditRights = rec.indexOf( "allow_EDIT_RIGHTS" );
    const int indexEditOffice = rec.indexOf( "allow_edit_office" );
    const int indexEditHolidays = rec.indexOf( "allow_edit_holidays" );

    while (query.next())
    {
        Right right;

        right.i_ID = query.value(indexId).toInt();
        right.s_Name = query.value(indexName).toString();
        right.i_acs_lvl = query.value(indexLVL).toInt();
        right.rights[EDIT_USERS] = query.value(indexEditUser).toBool();
        right.rights[EDIT_RIGHTS] = query.value(indexEditRights).toBool();
        right.rights[EDIT_OFFICE] = query.value(indexEditOffice).toBool();
        right.rights[EDIT_HOLIDAYS] = query.value(indexEditHolidays).toBool();

        rights.push_back(right);

        qDebug() << right.i_ID << right.s_Name;
    }

    return rights;
}

QString Database::FindFreeDefaultName(QString table, QString param,QString insert_name)
{
    qDebug();
    qDebug() << "Database::FindFreeDefaultName";

    QString name = insert_name;

    QSqlQuery query;
    int result = 0;
    int it = 0;

    do
    {
        name = (it++ == 0) ? insert_name : insert_name + QString::number(it);

        query.prepare(QString("SELECT * FROM %1 WHERE %2 = :name").arg(table).arg(param));

        query.bindValue(":name", name);

        result = query.exec();

        if (!result)
        {
            qDebug() << query.lastQuery();
            qDebug() << query.lastError().text();
        }
    }
    while (query.next());

    qDebug() << name;

    return name;
}

void Database::AddUser()
{
    qDebug();

    auto name = FindFreeDefaultName("users", "full_name", "User");

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

void Database::AddRight()
{
    qDebug();
    qDebug() << "Database::AddRight";

    auto name = FindFreeDefaultName("rights", "name", "Right");

    QSqlQuery query;
    int result = 0;
    int it = 0;

    query.prepare("INSERT INTO rights (id, name, access_lvl) VALUES ((SELECT MAX(id) + 1 from rights), :name, :lvl) ");

    query.bindValue(":name", name);
    query.bindValue(":lvl", LOWEST_ACS_LVL);

    result = query.exec();

    if (!result)
    {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
    }
}

void Database::AddOffice()
{
    qDebug();
    qDebug() << "Database::AddOffice";

    auto name = FindFreeDefaultName("office", "name", "Office");

    QSqlQuery query;
    int result = 0;
    int it = 0;

    query.prepare("INSERT INTO office (name) VALUES (:name) ");

    query.bindValue(":name", name);

    result = query.exec();

    if (!result)
    {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
    }
}

void Database::RemoveUser(int id)
{
    qDebug() << id;

    QSqlQuery query;
    int result = 0;
    int it = 0;

    query.prepare("DELETE FROM users WHERE id = :id ");

    query.bindValue(":id", id);

    result = query.exec();

    if (!result)
    {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
    }

}

QVector<Office> Database::GetOffices()
{
    qDebug();
    qDebug() << "Database::GetOffices";

    QSqlQuery query;
    QVector<Office> offices;
    int result;

    result = query.exec(QString("SELECT * FROM office"));

    if (!result)
    {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
        return {};
    }

    QSqlRecord rec = query.record();
    const int indexId = rec.indexOf( "id" );
    const int indexName = rec.indexOf( "name" );
    const int indexAddress = rec.indexOf( "address" );

    while (query.next())
    {
        Office office;

        office.i_ID = query.value(indexId).toInt();
        office.s_Name = query.value(indexName).toString();
        office.s_Address = query.value(indexAddress).toString();

        offices.push_back(office);

        qDebug() << office.i_ID << office.s_Name;
    }

    return offices;
}

Office Database::GetOffice(int id)
{
    qDebug();
    qDebug() << "Database::GetUserData (id)";

    QSqlQuery query;
    Office office;
    int result;

    query.prepare(QString("SELECT * FROM office WHERE id = :id"));

    query.bindValue(":id", id);

    result = query.exec();

    if (!result)
    {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
        return {};
    }

    QSqlRecord rec = query.record();
    const int indexID = rec.indexOf( "id" );
    const int indexName = rec.indexOf( "name" );
    const int indexAddress = rec.indexOf( "address" );

    if (query.next())
    {
        office.i_ID = query.value(indexID).toInt();
        office.s_Name = query.value(indexName).toString();
        office.s_Address = query.value(indexAddress).toString();

    }

    return office;
}

Right Database::GetRight(int id)
{
    qDebug() << id;

    QSqlQuery query;
    Right right;
    int result;

    query.prepare(QString("SELECT * FROM rights WHERE id = :id"));

    query.bindValue(":id", id);

    result = query.exec();

    if (!result)
    {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
        return {};
    }

    QSqlRecord rec = query.record();
    const int indexID = rec.indexOf( "id" );
    const int indexName = rec.indexOf( "name" );
    const int indexLvl = rec.indexOf( "access_lvl" );
    const int indexEditUser = rec.indexOf( "allow_edit_users" );
    const int indexEditRights = rec.indexOf( "allow_EDIT_RIGHTS" );
    const int indexEditOffice = rec.indexOf( "allow_edit_office" );
    const int indexEditHolidays = rec.indexOf( "allow_edit_holidays" );


    if (query.next())
    {
        right.i_ID = query.value(indexID).toInt();
        right.s_Name = query.value(indexName).toString();
        right.i_acs_lvl = query.value(indexLvl).toInt();
        right.rights[EDIT_USERS] = query.value(indexEditUser).toBool();
        right.rights[EDIT_RIGHTS] = query.value(indexEditRights).toBool();
        right.rights[EDIT_OFFICE] = query.value(indexEditOffice).toBool();
        right.rights[EDIT_HOLIDAYS] = query.value(indexEditHolidays).toBool();

    }

    return right;
}

Right Database::GetRight(QString name)
{
    qDebug() << name;

    QSqlQuery query;
    Right right;
    int result;

    query.prepare(QString("SELECT * FROM rights WHERE name = :name"));

    query.bindValue(":name", name);

    result = query.exec();

    if (!result)
    {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
        return {};
    }

    QSqlRecord rec = query.record();
    const int indexID = rec.indexOf( "id" );
    const int indexName = rec.indexOf( "name" );
    const int indexLvl = rec.indexOf( "access_lvl" );
    const int indexEditUser = rec.indexOf( "allow_edit_users" );
    const int indexEditRights = rec.indexOf( "allow_EDIT_RIGHTS" );
    const int indexEditOffice = rec.indexOf( "allow_edit_office" );
    const int indexEditHolidays = rec.indexOf( "allow_edit_holidays" );


    if (query.next())
    {
        right.i_ID = query.value(indexID).toInt();
        right.s_Name = query.value(indexName).toString();
        right.i_acs_lvl = query.value(indexLvl).toInt();
        right.rights[EDIT_USERS] = query.value(indexEditUser).toBool();
        right.rights[EDIT_RIGHTS] = query.value(indexEditRights).toBool();
        right.rights[EDIT_OFFICE] = query.value(indexEditOffice).toBool();
        right.rights[EDIT_HOLIDAYS] = query.value(indexEditHolidays).toBool();

    }

    return right;
}

int Database::GetID(QString table, QString field, QString value)
{
    qDebug();
    qDebug() << "Database::GetID";

    QSqlQuery query;
    int result;

    query.prepare(QString("SELECT id FROM %1 WHERE %2 = :value").arg(table).arg(field));

    query.bindValue(":value", value);

    result = query.exec();

    if (!result)
    {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
        return {};
    }

    QSqlRecord rec = query.record();
    const int indexID = rec.indexOf( "id" );

    if (query.next())
    {
        return query.value(indexID).toInt();
    }

    return 0;
}

void Database::UpdateUserData(User user)
{
    qDebug();

    QSqlQuery query;
    int result;

    query.prepare(QString("UPDATE users SET full_name = :name, rights_id = :right, office_id = :office WHERE id = :id"));

    query.bindValue(":id", user.i_ID);
    query.bindValue(":name", user.s_Full_Name);
    query.bindValue(":office", GetID("office", "name", user.s_Office));
    query.bindValue(":right", GetID("rights", "name", user.s_Right));

    result = query.exec();

    if (!result)
    {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
    }

}

void Database::UpdateRightData(Right right)
{

    qDebug() << right.i_ID << " " << right.s_Name << " " << right.i_acs_lvl;

    QSqlQuery query;
    int result;

    query.prepare(QString("UPDATE rights SET name = :name, access_lvl = :lvl WHERE id = :id"));

    query.bindValue(":id", right.i_ID);
    query.bindValue(":name", right.s_Name);
    query.bindValue(":lvl", right.i_acs_lvl);

    result = query.exec();

    if (!result)
    {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
    }

}

int Database::GetUserAccessLvl(int id)
{
    qDebug() << id;

    QSqlQuery query;
    int result;

    query.prepare(QString("SELECT rights.access_lvl AS lvl FROM users  INNER JOIN rights ON users.rights_id = rights.id WHERE users.id = :id"));

    query.bindValue(":id", id);

    result = query.exec();

    if (!result)
    {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
        return {};
    }

    QSqlRecord rec = query.record();
    const int indexLvl = rec.indexOf( "lvl" );

    if (query.next())
    {
        return query.value(indexLvl).toInt();
    }

    return LOWEST_ACS_LVL;
}

void Database::SaveMsg(QString text, int id_sender, int id_recipient)
{
    qDebug();

    QSqlQuery query;
    int result = 0;
    int it = 0;

    query.prepare("INSERT INTO messages (id_sender, id_recipient, text, date_time) VALUES (:sender, :recipient, :text, TO_TIMESTAMP(:dtime, 'DD/MM/YYYY HH24:MI:SS')) ");

    query.bindValue(":sender", id_sender);
    query.bindValue(":recipient", id_recipient);
    query.bindValue(":text", text);
    query.bindValue(":dtime", QDateTime::currentDateTime().toString("dd/MM/yyyy HH:MM:ss"));

    result = query.exec();

    if (!result)
    {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
    }

}

QVector<Message> Database::GetMessages(int id1, int id2)
{
    qDebug() << id1 << " " << id2;

    QSqlQuery query;
    QVector<Message> messages;
    int result;

    query.prepare(QString("SELECT * FROM messages WHERE (id_sender = :id1 AND id_recipient = :id2) OR (id_sender = :id2 AND id_recipient = :id1)"));

    query.bindValue(":id1", id1);
    query.bindValue(":id2", id2);

    result = query.exec();

    if (!result)
    {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
        return {};
    }

    QSqlRecord rec = query.record();
    const int indexText = rec.indexOf( "text" );
    const int indexSender = rec.indexOf( "id_sender" );
    const int indexRecipient = rec.indexOf( "id_recipient" );
    const int indexTimestamp = rec.indexOf( "date_time" );

    while (query.next())
    {
        Message msg;
        msg.text = query.value(indexText).toString();
        msg.sender = query.value(indexSender).toInt();
        msg.recepient = query.value(indexRecipient).toInt();
        msg.date_time = query.value(indexTimestamp).toDateTime();

        messages.push_back(msg);
    }

    return messages;
}


std::tuple<QVector<QString>, QVector<QVector<QDate>>> Database::GetHolidays(int month, int year)
{
    qDebug() << month << " " << year;

    QSqlQuery queryUsers;
    QSqlQuery queryHolidays;
    QVector<QString> users;
    QVector<QVector<QDate>> holidays;
    int result;

    result = queryUsers.exec("SELECT id, full_name FROM users ORDER BY id");

    if (!result)
    {
        qDebug() << queryUsers.lastQuery();
        qDebug() << queryUsers.lastError().text();
        return {};
    }

    QSqlRecord rec = queryUsers.record();
    const int indexID = rec.indexOf( "id" );
    const int indexName = rec.indexOf( "full_name" );

    while (queryUsers.next())
    {
        int id = queryUsers.value(indexID).toInt();
        QString name = queryUsers.value(indexName).toString();

        qDebug() << id << " " << name;

        users.push_back(name);

        queryHolidays.prepare("SELECT date FROM holidays WHERE id_user = :id AND EXTRACT(year from date) = :year AND EXTRACT(month from date) = :month ORDER BY id_user");

        queryHolidays.bindValue(":id", id);
        queryHolidays.bindValue(":year", year);
        queryHolidays.bindValue(":month", month);

        result = queryHolidays.exec();

        if (!result)
        {
            qDebug() << queryHolidays.lastQuery();
            qDebug() << queryHolidays.lastError().text();
            return {};
        }

        QSqlRecord rec = queryHolidays.record();
        const int indexDate = rec.indexOf( "date" );

        QVector<QDate> dates;
        while (queryHolidays.next())
        {
            QDate date = queryHolidays.value(indexDate).toDate();
            qDebug() << date.toString();
            dates.push_back(date);
        }
        holidays.push_back(dates);
    }

    return std::make_tuple(users, holidays);
}

int Database::GetUserID(QString name)
{
    qDebug();

    QSqlQuery query;
    int result = 0;

    query.prepare("SELECT id FROM users WHERE full_name = :name");

    query.bindValue(":name", name);

    result = query.exec();

    if (!result)
    {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
    }

    QSqlRecord rec = query.record();
    const int indexDate = rec.indexOf( "id" );

    if (query.next())
    {
        return query.value(indexDate).toInt();
    }

    return -1;
}

void Database::SetHoliday(QDate date, int id)
{

    qDebug();

    QSqlQuery query;
    int result = 0;

    query.prepare("SELECT * FROM holidays WHERE id_user = :id AND date = :date");

    query.bindValue(":id", id);
    query.bindValue(":date", date);

    result = query.exec();

    if (!result)
    {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
    }

    if (!query.next())
    {
        query.prepare("INSERT INTO holidays (id_user, date) VALUES (:id, :date)");

        query.bindValue(":id", id);
        query.bindValue(":date", date);

        result = query.exec();

        if (!result)
        {
            qDebug() << query.lastQuery();
            qDebug() << query.lastError().text();
        }

        return;
    }

    query.prepare("DELETE FROM holidays WHERE id_user = :id AND date = :date");

    query.bindValue(":id", id);
    query.bindValue(":date", date);

    result = query.exec();

    if (!result) {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
    }

    return;
}
