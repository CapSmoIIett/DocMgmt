
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

        QSqlQuery query;
        int result = 0;
        int it = 0;

        query.prepare("SELECT access_lvl FROM files WHERE name = :name");

        query.bindValue(":name", info.fileName());

        result = query.exec();

        if (!result)
        {
            qDebug() << query.lastQuery();
            qDebug() << query.lastError().text();
        }

        QSqlRecord rec = query.record();
        const int indexLvl = rec.indexOf( "access_lvl" );

        if (query.next())
        {
            file.i_acs_lvl = query.value(indexLvl).toInt();
        }
        else
            file.i_acs_lvl = 0;

        file.s_Name = info.fileName();
        file.i_Size = info.size();
        file.dt_DateModified = info.lastModified();
        file.s_Type = info.suffix();

        files.push_back(file);
    }

    return files;
}

QByteArray Filebase::GetFileBytes(QString name)
{
    qDebug() <<p_dir->path() + '/' + name;

    QFile file (p_dir->path() + '/' + name);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Error open file";
        qDebug() << file.errorString();
    }

    QDataStream in(&file);
    char* raw;

    uint len = static_cast<uint>(file.size());
    QByteArray data(file.size(), 0);

    qDebug() << "len: " << len;

    in.readRawData(data.data(), data.size());
    qDebug() << "data: " << data;

    file.close();

    return data;
}

//QDataStream Filebase::GetFileStream(QString name)
QFile* Filebase::GetFilePointer(QString name)
{
    qDebug() << name;

    QFile* file  = new QFile(p_dir->path() + '/' + name);
    if(!file->open(QIODevice::ReadOnly))
    {
        qDebug() << "Error open file";
        qDebug() << file->errorString();
    }

    //QDataStream in(&file);

    return file;
}

int Filebase::GetFileSize(QString name)
{
    qDebug();
    QFileInfo fileInfo (p_dir->path() + '/' + name);

    return fileInfo.size();

}

void Filebase::CreateFile(QString name, QByteArray text)
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

void Filebase::ChangeAccessLvl(QString name, int lvl)
{
    QSqlQuery query;
    Right right;
    int result;

    query.prepare(QString("UPDATE files SET access_lvl = :lvl WHERE name = :name"));

    query.bindValue(":lvl", lvl);
    query.bindValue(":name", name);

    result = query.exec();

    if (!result)
    {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
    }
}

int Filebase::GetAccessLvl(QString name)
{
    qDebug() << name;

    QSqlQuery query;
    int result;

    result = query.exec(QString("SELECT access_lvl FROM files"));

    if (!result)
    {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
        return -1;
    }

    QSqlRecord rec = query.record();
    const int indexLvl = rec.indexOf( "access_lvl" );

    if (query.next())
    {
        return query.value(indexLvl).toInt();
    }

    return LOWEST_ACS_LVL;
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
