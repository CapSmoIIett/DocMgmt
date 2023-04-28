
#include "rightsmodel.h"

RightsTableModel::RightsTableModel(AppEngine* engine, QObject *parent) :
    QAbstractTableModel{parent},
    p_AppEngine(engine)
{

}

int RightsTableModel::rowCount(const QModelIndex &parent) const
{
    return 10;
}

int RightsTableModel::columnCount(const QModelIndex &parent) const
{
    return 10;
}

QHash<int, QByteArray> RightsTableModel::roleNames() const
{
    return {{Qt::DisplayRole, "display"}};
}

QVariant RightsTableModel::data(const QModelIndex &index, int role) const
{
    switch (role)
    {
    case Qt::DisplayRole:
        return QString("%1, %2").arg(index.row()).arg(index.column());
    default:
        break;
    }

    return QVariant();
}

