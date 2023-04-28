
#ifndef RIGHTSMODEL_H
#define RIGHTSMODEL_H

#include <QAbstractTableModel>
#include <QObject>

#include <appengine.h>

class RightsTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit RightsTableModel(AppEngine* engine, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role) const override;

private:
    AppEngine* p_AppEngine;
    QVector<User> v_Rights;
};

#endif // RIGHTSMODEL_H
