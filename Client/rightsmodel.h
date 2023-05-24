
#ifndef RIGHTSMODEL_H
#define RIGHTSMODEL_H

#include <QAbstractTableModel>
#include <QObject>

#include "appengine.h"

class RightsTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit RightsTableModel(AppEngine* engine, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    Q_INVOKABLE int getIDbyRow(int row);

    Q_INVOKABLE  QVector<QString> getRightNames();

public slots:
    void GetRights(QVector<Right> rights);

signals:
   Q_INVOKABLE void loadRightPage(int id);

private:
    AppEngine* p_AppEngine;
    QVector<Right> v_Rights;
};

#endif // RIGHTSMODEL_H
