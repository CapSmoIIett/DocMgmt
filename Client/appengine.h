#pragma once

#include <QObject>
#include <QString>
#include <qqml.h>

class AppEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY()
    QML_ELEMENT

public:
    explicit AppEngine(QObject *parent = nullptr);

};

