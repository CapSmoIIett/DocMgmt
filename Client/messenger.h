
#ifndef MESSENGER_H
#define MESSENGER_H


#include <QObject>
#include <QAbstractListModel>

#include "appengine.h"

class Messenger : public QAbstractListModel
{
    Q_OBJECT
public:
    Messenger(AppEngine* engine, QObject *parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data( const QModelIndex& index, int role) const override;

    Q_INVOKABLE void addMessage(QString);
    Q_INVOKABLE void clear(QString);
    Q_INVOKABLE void setUsersID(int main, int second);
    Q_INVOKABLE void update();


public slots:
    void GetMessages(QVector<Message>);
    void GetMessage(Message msg);

private:
    AppEngine* p_AppEngine;
    QVector<Message> v_Messages;

    int i_CurUser;
    int i_SecondUser;
};

#endif // MESSENGER_H
