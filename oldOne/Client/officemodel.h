
#ifndef OFFICETABLEMODEL_H
#define OFFICETABLEMODEL_H

#include <QAbstractTableModel>
#include <QObject>

#include "appengine.h"

class OfficeTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit OfficeTableModel(AppEngine* engine, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    Q_INVOKABLE int getIDbyRow(int row);

    Q_INVOKABLE  QVector<QString> getOfficeNames();

public slots:
    void GetOffices(QVector<Office> offices);

signals:
    Q_INVOKABLE void loadOfficePage(int id);

private:
    AppEngine* p_AppEngine;
    QVector<Office> v_Offices;
};

#endif // OFFICETABLEMODEL_H
