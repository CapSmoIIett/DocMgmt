
#include "rightsmodel.h"

RightsTableModel::RightsTableModel(AppEngine* engine, QObject *parent) :
    QAbstractTableModel{parent},
    p_AppEngine(engine)
{
    connect(&engine->GetClient(), &Client::onGetRights, this, &RightsTableModel::GetRights);
}

int RightsTableModel::rowCount(const QModelIndex &parent) const
{
    return v_Rights.size();
}

int RightsTableModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QHash<int, QByteArray> RightsTableModel::roleNames() const
{
    return {{Qt::DisplayRole, "display"}};
}

QVariant RightsTableModel::data(const QModelIndex &index, int role) const
{
    if (index.row() >= v_Rights.size())
        return QVariant("");

    qDebug();
    qDebug() << "RightsTableModel::data " << index << role;

    Right right = v_Rights[index.row()];

    if (role == Qt::DisplayRole)
    {
        switch (index.column())
        {
        case 0: return right.i_ID;
        case 1: return right.s_Name;
        case 2: return right.i_acs_lvl;
        default:
            break;
        }
    }

    return QVariant("");
}

QVariant RightsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case 0:
            return QString("ID");
        case 1:
            return QString("Name");
        case 2:
            return QString("Lvl");
        default:
            break;
        }
    }
    return QVariant("");
}

int RightsTableModel::getIDbyRow(int row)
{
    return v_Rights[row].i_ID;
}

QVector<QString> RightsTableModel::getRightNames()
{
    QVector<QString> names;

    for (auto right : v_Rights)
        names.push_back(right.s_Name);

    return names;
}

void RightsTableModel::GetRights(QVector<Right> rights)
{
    qDebug();
    qDebug() << "RightsTableModel::GetRights";

    v_Rights = rights;

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    endInsertRows();

    emit dataChanged(index(0, 0), index(v_Rights.size() - 1, 3), {Qt::DisplayRole});
}

