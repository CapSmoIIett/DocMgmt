
#include "filebase.h"

Filebase::Filebase()
{
    if (!QDir(FILES_FOLDER_NAME).exists())
    {
        QDir().mkdir(FILES_FOLDER_NAME);
    }

    p_dir = new QDir(QDir::currentPath() + "/" + FILES_FOLDER_NAME);

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
