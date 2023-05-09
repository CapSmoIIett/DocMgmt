
#include "filebase.h"

Filebase::Filebase()
{
    if (!QDir(FILES_FOLDER_NAME).exists())
    {
        QDir().mkdir(FILES_FOLDER_NAME);
    }

    p_dir = new QDir(QDir::currentPath() + "/" + FILES_FOLDER_NAME);

    db = QSqlDatabase::database("DocMgmt");
    CreateTables();

    connect(&timer, &QTimer::timeout, this, &Filebase::UpdateFileBase);
    timer.start(3000);

    qDebug();
    qDebug() << "Filebase: " << p_dir->currentPath();

}

Filebase::~Filebase()
{

}


QVector<File> Filebase::GetFileList(QString path)
{
    //QDir dir = QFileDialog::getExistingDirectory(this, p_dir->currentPath() + "/" + path);
    QDir dir (p_dir->path());
    QVector<File> files;

    //QStringList list = dir.entryList(QStringList() << "*", QDir::Files);
    QFileInfoList fileInfo = dir.entryInfoList();


    for (auto info : fileInfo)
    {
        File file;

        file.s_Name = info.fileName();
        file.i_Size = info.size();
        file.dt_DateModified = info.lastModified();
        file.s_Type = info.suffix();

        files.push_back(file);
    }

    return files;
}

QString Filebase::GetFile(QString name)
{
    qDebug();
    qDebug() << "Filebase::GetFile";
    qDebug() << name;
    qDebug() << p_dir->path();

    QFile file (p_dir->path() + '/' + name);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Error open file";
        qDebug() << file.errorString();
    }

    QTextStream in(&file);

    QString text = in.readAll();

    file.close();

    return text;
}

void Filebase::CreateFile(QString name, QString text)
{
        QFile file(p_dir->path() + '/' +name);

        if(!file.open(QIODevice::ReadWrite))
        {
            qDebug() << "Error open file";
            qDebug() << file.errorString();
        }
        else
        {
            QTextStream stream(&file);
            stream << text;
        }
}

void Filebase::UpdateFileBase()
{
        qDebug();
    QDir dir (p_dir->path());
    QFileInfoList fileInfo = dir.entryInfoList();

    QSqlQuery query;
    bool result = 0;

    for (auto info : fileInfo)
    {
        File file;

        file.s_Name = info.fileName();
        query.prepare(QString("SELECT * FROM files WHERE name = :name"));

        query.bindValue(":name", info.fileName());

        result = query.exec();

        if (!result)
        {
            qDebug() << query.lastQuery();
            qDebug() << query.lastError().text();
        }

        if (!query.next())
        {
            query.prepare("INSERT INTO files (name, access_lvl) VALUES (:name, :lvl) ");

            query.bindValue(":name", info.fileName());
            query.bindValue(":lvl", 0);

            result = query.exec();

            if (!result)
            {
                qDebug() << query.lastQuery();
                qDebug() << query.lastError().text();
            }
        }

    }

}


bool Filebase::CreateTables()
{
    QSqlQuery query;
    bool result = 0;

    result = query.exec("CREATE TABLE IF NOT EXISTS files"
                "("
                    "id serial primary key,"
                    "name varchar(255) null,"
                    "access_lvl int"
                ")");

    if (!result)
    {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
        return false;
    }
}
