#pragma once

#include <QObject>
#include <QString>
#include <qqml.h>

class AppEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString UserName READ UserName WRITE setUserName)
    Q_PROPERTY(QString Password READ Password WRITE setUserName)
    Q_PROPERTY(BOOL Verify READ Verify NOTIFY onVerefied)
    QML_ELEMENT

public:
    explicit AppEngine(QObject *parent = nullptr);

    QString UserName();
    void setUserName(const QString &userName);

    QString Password();
    void setPassword(const QString &password);

    bool Verify();

signals:
    void onVerefied();



};

