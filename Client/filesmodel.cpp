
#include "filesmodel.h"


FilesTableModel::FilesTableModel(AppEngine* engine, QObject *parent) :
    QAbstractTableModel(parent),
    p_AppEngine(engine)
{
    connect(&engine->GetClient(), &Client::onGetFiles, this, &FilesTableModel::GetFiles);
}

int FilesTableModel::rowCount(const QModelIndex& parent) const
{
    return v_Files.size();
}

int FilesTableModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QHash<int, QByteArray> FilesTableModel::roleNames() const
{
    return {{Qt::DisplayRole, "display"}};
}

QVariant FilesTableModel::data(const QModelIndex& index, int role) const
{

    qDebug();
    qDebug() << "FilesModel::data " << index << role;

    if (index.row() >= v_Files.size())
        return QVariant("");

    auto file = v_Files[index.row()];

    if (role == Qt::DisplayRole)
    {
        switch (index.column())
        {
        case 0: return file.s_Name;
        case 1: return file.s_Type;
        case 2: return (int)file.i_Size;
        case 3: return (int)file.i_acs_lvl;
        default:
            break;
        }
    }

    return QVariant("");

}

QVariant FilesTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case 0: return QString("Name");
        case 1: return QString("Type");
        case 2: return QString("Size");
        case 3: return QString("LVL");
        default:
            break;
        }
    }
    return QVariant("");
}

QString FilesTableModel::getNameByRow(int row)
{
    qDebug() << row;
    return v_Files[row].s_Name;
}


void FilesTableModel::GetFiles(QVector<File> files)
{
    qDebug();
    qDebug() << "FilesTableModel::GetFiles";


    v_Files = files;
    qDebug() << "Size: " << v_Files.size();

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    endInsertRows();

    emit dataChanged(index(0, 0), index(v_Files.size() - 1, 4), {Qt::DisplayRole});

}

