
#include "messenger.h"

Messenger::Messenger(AppEngine* engine, QObject *parent) :
    QAbstractListModel{parent},
    p_AppEngine(engine)
{
    /*
    i_CurUser = -1;
    i_SecondUser = -2;

    Message msg1;
    msg1.text = "hi";
    msg1.date_time = QDateTime::currentDateTime();
    msg1.sender = 0;
    msg1.recepient = i_CurUser;

    Message msg2;
    msg2.text = "hi!";
    msg2.date_time = QDateTime::currentDateTime();
    msg1.sender = i_SecondUser;
    msg1.recepient = 0;


    Message msg3;
    msg3.text = "how a you?";
    msg3.date_time = QDateTime::currentDateTime();
    msg1.sender = 0;
    msg1.recepient = i_CurUser;

    v_Messages = {msg1, msg2, msg3};
    */

    connect(&engine->GetClient(), &Client::onGetMessages, this, &Messenger::GetMessages);
    connect(&engine->GetClient(), &Client::onGetMessage, this, &Messenger::GetMessage);

}

int Messenger::rowCount(const QModelIndex& parent) const
{
    qDebug() << v_Messages.size();
    return v_Messages.size();
}

QVariant Messenger::data( const QModelIndex& index, int role) const
{
    qDebug() << index.row();

    if (role == Role::Sender)
    {
        qDebug() << v_Messages[v_Messages.size() - index.row() - 1].sender << " " <<  this->i_CurUser ;
        return v_Messages[v_Messages.size() - index.row() - 1].sender == this->i_CurUser;
    }

    qDebug() << v_Messages[v_Messages.size() - index.row() - 1].text;

    return v_Messages[v_Messages.size() - index.row() - 1].text;
}

QHash<int, QByteArray> Messenger::roleNames() const
{
    QHash<int, QByteArray> hash;
    return {{Qt::DisplayRole, "display"}, {Role::Sender, "isYouSentIt"}};
}


void Messenger::GetMessages(QVector<Message> messages)
{
    qDebug() << messages.size();

    beginInsertRows(QModelIndex(), 0, messages.size());
    v_Messages = messages;
    endInsertRows();

    emit dataChanged(index(0, 0), index(v_Messages.size() - 1, 1), {Qt::DisplayRole});
}

void Messenger::GetMessage(Message msg)
{
    if (msg.sender != this->i_SecondUser)
        return;

    qDebug() << msg.text;
    qDebug() << msg.sender;

    beginInsertRows(QModelIndex(), 0, 0);

    v_Messages.push_back(msg);

    endInsertRows();

    emit dataChanged(index(0, 0), index(v_Messages.size() - 1, 1), {Qt::DisplayRole});
}

void Messenger::addMessage(QString str)
{
    if (str.isEmpty())
        return;

    qDebug() << str;

    beginInsertRows(QModelIndex(), 0, 0);

    Message msg;
    msg.text = str;
    msg.sender = i_CurUser;
    msg.recepient = i_SecondUser;
    v_Messages.push_back(msg);

    endInsertRows();

    emit dataChanged(index(0, 0), index(v_Messages.size() - 1, 1), {Qt::DisplayRole});

    //update();
}

void Messenger::clear()
{
    v_Messages.clear();
}

void Messenger::setUsersID(int main, int second)
{
    i_CurUser = main;
    i_SecondUser = second;
}

void Messenger::update()
{
    /*
    for(auto msg : v_Messages)
    {
        qDebug() << msg.text;
    }
*/

    qDebug();
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    endInsertRows();

    emit dataChanged(index(0, 0), index(v_Messages.size() - 1, 1), {Qt::DisplayRole});

}
