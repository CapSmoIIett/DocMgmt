#include "personalmodel.h"



PersonalTableModel::PersonalTableModel (AppEngine* engine, QObject* parent) :
    p_AppEngine(engine),
    QAbstractTableModel(parent)
{
    connect(&p_AppEngine->GetClient(), &Client::onGetUsersList, this, &PersonalTableModel::GetUserList);
    //connect(this, &QAbstractTableModel::dataChanged, this, &QAbstractTableModel:: 	)
    //connect(this, &PersonalTableModel::modelReset, this, &PersonalTableModel::GetUserList);
}


int PersonalTableModel::rowCount(const QModelIndex &parent) const
{
    qDebug();
    qDebug() << "PersonalTableModel::rowCount";
    qDebug() << v_Users.size();
    //if (parent.isValid())
    //Q_UNUSED(parent);
    return 9;//v_Users.size();
}

int PersonalTableModel::columnCount(const QModelIndex &parent) const
{
    qDebug();
    qDebug() << "PersonalTableModel::columnCount";
    //if (parent.isValid())
    //Q_UNUSED(parent);
    return 3;
}

QHash<int, QByteArray> PersonalTableModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(Qt::UserRole+FULL_NAME, "full_name");
    roles.insert(Qt::UserRole+RIGHT, "right");
    roles.insert(Qt::UserRole+OFFICE, "office");
    return roles;
}

QVariant PersonalTableModel::data(const QModelIndex &index, int role) const
{
    qDebug();
    qDebug() << "PersonalTableModel::data";

    if (!index.isValid() || role !=  Qt::DisplayRole)
        return QVariant("null");

    if (index.row() >= v_Users.size())
        return QVariant("null");

    User user = v_Users[index.row()];

    qDebug() << index.row() << " " << index.column();

    switch (index.column()) {
    case 0:
        {
            qDebug() << user.s_Full_Name;
            return user.s_Full_Name;
        }
    case 1:
        {
            qDebug() << user.s_Right;
            return user.s_Right;
        }
    case 2:
        {
            qDebug() << user.s_Office;
            return user.s_Office;
        }
    }
    return QVariant(QString("1"));
}

QVariant PersonalTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section)
        {
        case 0:
            return QString("Full Name");
        case 1:
            return QString("Right");
        case 2:
            return QString("Office");
        }
    }
    return QVariant();

}

void PersonalTableModel::GetUserList(QVector<User> users)
{
    qDebug();
    qDebug() << "PersonalTableModel::GetUserList";


    beginRemoveRows(QModelIndex(), 0, rowCount());
    removeRows(0, rowCount());
    endRemoveRows();

    v_Users = users;

    for (auto user : v_Users)
    {
        qDebug() << user.s_Full_Name;
        qDebug() << user.s_Right;
        qDebug() << user.s_Office;
    }

    //emit onRowCountChanged(users.size());

    beginInsertRows(QModelIndex(), 0, users.size());
    insertRows(0, v_Users.size());
    endInsertRows();

    emit dataChanged(index(0, 0), index(v_Users.size() - 1, 2), {Qt::DisplayRole});

}
