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

DataBase::DataBase(QObject *parent) : QObject(parent)
{
    // Подключаемся к базе данных
    this->connectToDataBase();
    /* После чего производим наполнение таблицы базы данных
     * контентом, который будет отображаться в TableView
     * */
}

DataBase::~DataBase()
{

}

/* Методы для подключения к базе данных
 * */
void DataBase::connectToDataBase()
{
    /* Перед подключением к базе данных производим проверку на её существование.
     * В зависимости от результата производим открытие базы данных или её восстановление
     * */
    /*if(!QFile("C:/example/" DATABASE_NAME).exists()){
        this->restoreDataBase();
    } else {
        this->openDataBase();
    }
    */
}

/* Методы восстановления базы данных
 * */
bool DataBase::restoreDataBase()
{
    if(this->openDataBase()){
        if(!this->createTable()){
            return false;
        } else {
            return true;
        }
    } else {
        qDebug() << "Не удалось восстановить базу данных";
        return false;
    }
    return false;
}

/* Метод для открытия базы данных
 * */
bool DataBase::openDataBase()
{
    /* База данных открывается по заданному пути
     * и имени базы данных, если она существует
     * */
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName("C:/example/" DATABASE_NAME);
    if(db.open()){
        return true;
    } else {
        return false;
    }
}

/* Методы закрытия базы данных
 * */
void DataBase::closeDataBase()
{
    db.close();
}

/* Метод для создания таблицы в базе данных
 * */
bool DataBase::createTable()
{
    /* В данном случае используется формирование сырого SQL-запроса
     * с последующим его выполнением.
     * */
    /*SqlQuery query;
    if(!query.exec( "CREATE TABLE " TABLE " ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                            TABLE_DATE      " DATE            NOT NULL,"
                            TABLE_TIME      " TIME            NOT NULL,"
                            TABLE_RANDOM    " INTEGER         NOT NULL,"
                            TABLE_MESSAGE   " VARCHAR(255)    NOT NULL"
                        " )"
                    )){
        qDebug() << "DataBase: error of create " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
    */
    return false;
}

/* Метод для вставки записи в базу данных
 * */
bool DataBase::inserIntoTable(const QVariantList &data)
{
    /* Запрос SQL формируется из QVariantList,
     * в который передаются данные для вставки в таблицу.
     * */
    QSqlQuery query;
    /* В начале SQL запрос формируется с ключами,
     * которые потом связываются методом bindValue
     * для подстановки данных из QVariantList
     * */
    /*query.prepare("INSERT INTO " TABLE_EMPLOYEE " ( " TABLE_DATE ", "
                                             TABLE_TIME ", "
                                             TABLE_RANDOM ", "
                                             TABLE_MESSAGE " ) "
                  "VALUES (:Date, :Time, :Random, :Message )");
    query.bindValue(":Date",        data[0].toDate());
    query.bindValue(":Time",        data[1].toTime());
    query.bindValue(":Random",      data[2].toInt());
    query.bindValue(":Message",     data[3].toString());
    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        qDebug() << "error insert into " << TABLE_EMPLOYEE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }*/
    return false;
}
