#include "personalmodel.h"



PersonalTableModel::PersonalTableModel (AppEngine* engine, QObject* parent) :
    p_AppEngine(engine),
    QAbstractTableModel(parent)
{
    connect(&p_AppEngine->GetClient(), &Client::onGetUsersList, this, &PersonalTableModel::GetUserList);

}


int PersonalTableModel::rowCount(const QModelIndex &parent) const
{
    //qDebug();
    //qDebug() << "PersonalTableModel::rowCount";
    //qDebug() << v_Users.size();


    return v_Users.size();
}

int PersonalTableModel::columnCount(const QModelIndex &parent) const
{
    //qDebug();
    //qDebug() << "PersonalTableModel::columnCount";

    return 4;
}

QHash<int, QByteArray> PersonalTableModel::roleNames() const
{
    QHash<int, QByteArray> hash;
    return {{Qt::DisplayRole, "display"}, {Role::Type, "type"}};
}

QVariant PersonalTableModel::data(const QModelIndex &index, int role) const
{
    qDebug();
    qDebug() << "PersonalTableModel::data";

    if (role == Role::Type)
    {
        return index.column() == 0 ? "icon" : "str";
    }

    if (!index.isValid() || role !=  Qt::DisplayRole)
        return QVariant("null");

    if (index.row() >= v_Users.size())
        return QVariant("null");

    User user = v_Users[index.row()];


    switch (index.column())
    {
    case 0: return user.i_ID;
    case 1: return user.s_Full_Name;
    case 2: return user.s_Right;
    case 3: return user.s_Office;
    default: break;
    }

    return QVariant(QString("null"));
}

QVariant PersonalTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case 0:
            return QString("Avatar");
        case 1:
            return QString("Full Name");
        case 2:
            return QString("Right");
        case 3:
            return QString("Office");
        }
    }
    return QVariant();
}

int PersonalTableModel::getIDbyRow(int row)
{
    return v_Users[row].i_ID;
}

void PersonalTableModel::GetUserList(QVector<User> users)
{
    qDebug();
    qDebug() << "PersonalTableModel::GetUserList";

    v_Users = users;

    /*
    for (auto user : v_Users)
    {
        qDebug() << user.s_Full_Name;
        qDebug() << user.s_Right;
        qDebug() << user.s_Office;
    }
    */

    //emit onRowCountChanged(users.size());

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    endInsertRows();

    emit dataChanged(index(0, 0), index(v_Users.size() - 1, 4), {Qt::DisplayRole, Role::Type});
}
