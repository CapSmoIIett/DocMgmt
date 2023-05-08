#pragma once

#include <QObject>
#include <QDir>
#include <QFile>
#include <QFileDialog>

#include <QString>
#include <QVector>

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

private:
    QDir* p_dir;

};
