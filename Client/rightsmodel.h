
#ifndef RIGHTSMODEL_H
#define RIGHTSMODEL_H

#include <QAbstractTableModel>

#include <QObject>


class RightsTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit RightsTableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role) const override;
};

#endif // RIGHTSMODEL_H
