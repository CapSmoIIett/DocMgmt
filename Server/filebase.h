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
    QByteArray GetFileBytes(QString);
    QFile* GetFilePointer(QString);
    int GetFileSize(QString name);
    void CreateFile(QString name, QByteArray text);
    void ChangeAccessLvl(QString name, int lvl);
    int GetAccessLvl(QString name);

public slots:
    void UpdateFileBase();

private:
    bool CreateTables();

    QTimer timer;

    QDir* p_dir;
    QSqlDatabase    db;

};
