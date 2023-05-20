#pragma once

#include <QObject>
#include <QAbstractTableModel>

#include <appengine.h>

class PersonalTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:

    enum Role {
        Display = Qt::DisplayRole,
        Type = Qt::UserRole
    };
    Q_ENUM(Role)

    explicit PersonalTableModel (AppEngine* engine, QObject* parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    Q_INVOKABLE int getIDbyRow(int row);

public slots:
    void GetUserList(QVector<User>);

signals:
    Q_INVOKABLE void loadUserPage(int id);

private:
    AppEngine* p_AppEngine;
    QVector<User> v_Users;

};

