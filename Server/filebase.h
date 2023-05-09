#pragma once

#include <QObject>
#include <QDir>
#include <QFile>
#include <QFileDialog>

#include <QTimer>

#include <QString>
#include <QVector>

#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlRecord>

#include "../datastructures.h"

#define FILES_FOLDER_NAME "files"


class Filebase : public QObject
{
    Q_OBJECT

public:
    Filebase();
    ~Filebase();

    QVector<File> GetFileList(QString);
    QString GetFile(QString);
    void CreateFile(QString name, QString text);

public slots:
    void UpdateFileBase();

private:
    bool CreateTables();

    QTimer timer;

    QDir* p_dir;
    QSqlDatabase    db;

};
