
#ifndef FILESMODEL_H
#define FILESMODEL_H


#include <QObject>

#include <QAbstractListModel>

#include <appengine.h>



class FilesTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:

    explicit FilesTableModel (AppEngine* engine, QObject* parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    Q_INVOKABLE QString getNameByRow(int row);

public slots:
    void GetFiles(QVector<File>);

signals:
  Q_INVOKABLE void loadFiles(QString);

private:
    AppEngine* p_AppEngine;
    QVector<File> v_Files;

};


#endif // FILESMODEL_H
