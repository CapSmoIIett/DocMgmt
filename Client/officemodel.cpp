
#include "officemodel.h"

OfficeTableModel::OfficeTableModel(AppEngine* engine, QObject *parent) :
    QAbstractTableModel{parent},
    p_AppEngine(engine)
{
    connect(&engine->GetClient(), &Client::onGetOffices, this, &OfficeTableModel::GetOffices);
}


int OfficeTableModel::rowCount(const QModelIndex &parent) const
{
    return v_Offices.size();
}

int OfficeTableModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QHash<int, QByteArray> OfficeTableModel::roleNames() const
{
    return {{Qt::DisplayRole, "display"}};
}

QVariant OfficeTableModel::data(const QModelIndex &index, int role) const
{
    if (index.row() >= v_Offices.size())
        return QVariant("");

    qDebug();
    qDebug() << "OfficeTableModel::data " << index << role;

    Office office = v_Offices[index.row()];

    if (role == Qt::DisplayRole)
    {
        switch (index.column())
        {
        case 0: return office.i_ID;
        case 1: return office.s_Name;
        case 2: return office.s_Address;
        default:
            break;
        }
    }

    return QVariant("");
}

QVariant OfficeTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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
            return QString("Address");
        default:
            break;
        }
    }
    return QVariant("");
}

void OfficeTableModel::GetOffices(QVector<Office> offices)
{
    qDebug();
    qDebug() << "OfficeTableModel::GetOffices";

    for (auto r : offices)
    {
        qDebug() << r.i_ID << r.s_Name << r.s_Address;
    }

    v_Offices = offices;

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    endInsertRows();

    emit dataChanged(index(0, 0), index(v_Offices.size() - 1, 3), {Qt::DisplayRole});
}

