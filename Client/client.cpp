#include "client.h"


Client::Client()
{

    static int i = 0;

    if (i++ == 0)
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", "mydb");
       db.setHostName("DESKTOP-49Q6B8N");
       db.setDatabaseName("DocMgmt");
       db.setUserName("postgres");
       db.setPassword("1111");
       bool ok = db.open();
       std::cout << "BD connect: " << ok << "\n";

       QSqlQuery query;
       query.exec("INSERT INTO EMPLOYEE (Rights_id, Full_Name, Birth_date, Office_id, phone_number) VALUES (0, 'name2', TO_DATE('1/1/2000', 'DD/MM/YYYY'), 0, '11111111')");

    }
}
