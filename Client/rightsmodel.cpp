
#include "rightsmodel.h"

RightsTableModel::RightsTableModel(AppEngine* engine, QObject *parent) :
    QAbstractTableModel{parent},
    p_AppEngine(engine)
{
    connect(&engine->GetClient(), &Client::onGetRights, this, &RightsTableModel::GetRights);
    /*
    for (int i = 0; i < 10; i++)
    {
        Right r;
        r.s_Name = '1';
        v_Rights.push_back(r);
    }
//*/

}

int RightsTableModel::rowCount(const QModelIndex &parent) const
{
    return v_Rights.size();
}

int RightsTableModel::columnCount(const QModelIndex &parent) const
{
    return 2;
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
        default:
            break;
        }
    }

    /*
     * switch (role)
    {
    case Qt::DisplayRole:
        return right.s_Name;//QString("%1, %2").arg(index.row()).arg(index.column());
    default:
        break;
    }
*/

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
        default:
            break;
        }
    }
    return QVariant("");
}

void RightsTableModel::GetRights(QVector<Right> rights)
{
    qDebug();
    qDebug() << "RightsTableModel::GetRights";

    for (auto r : rights)
    {
        qDebug() << r.i_ID << r.s_Name;
    }

    v_Rights = rights;

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    endInsertRows();

    emit dataChanged(index(0, 0), index(v_Rights.size() - 1, 2), {Qt::DisplayRole});
}

