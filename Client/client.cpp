#include "client.h"


Client::Client(QString ip, int port) :
    s_IP(ip),
    i_Port(port)
{
    p_TcpSocket = new QTcpSocket(this);

    connect(p_TcpSocket, &QTcpSocket::readyRead, this, &Client::ReadSocket);
    connect(p_TcpSocket, &QTcpSocket::disconnected, this, &Client::DiscardSocket);

    ConnectToServer();
}

void Client::ConnectToServer()
{
    if (p_TcpSocket->state() == QTcpSocket::ConnectedState)
    {
        qDebug() << "lready connected";
        return;
    }

    qDebug() << "Connecting" << s_IP << " " << i_Port;
    p_TcpSocket->connectToHost(s_IP, i_Port);

    p_TcpSocket->waitForConnected();

    qDebug() << "Connection: " << (p_TcpSocket->state() == QTcpSocket::ConnectedState);
}

bool Client::IsConnected()
{
    return p_TcpSocket->state() == QTcpSocket::ConnectedState;
}

void Client::SendToServer(QString str)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);
    out << str;
    p_TcpSocket->write(Data);
}


bool Client::VerifyRequest (QString username, QString password)
{
    qDebug();
    qDebug() << "Client::VerifyRequest";

    if (!p_TcpSocket)
    {
        qDebug () << "Verify: socket error";
        return false;
    }

    if (!p_TcpSocket->isOpen())
    {
        qDebug () << "Verify: socket close";
        return false;
    }

    QDataStream socketStream(p_TcpSocket);
    socketStream.setVersion(QDataStream::Qt_6_4);

    QByteArray byteArray;
    byteArray.prepend((QString("Type:%1,Username:%2,Password:%3").arg(MSG_VERIFY).arg(username).arg(password)).toUtf8());

    qDebug() << byteArray;

    socketStream << byteArray;


    return true;
}

void Client::ReadSocket ()
{
    qDebug();
    qDebug() << "Client::ReadSocket";

    QByteArray buffer;
    QDataStream socketStream(p_TcpSocket);
    socketStream.setVersion(QDataStream::Qt_6_4);

    //p_TcpSocket = (QTcpSocket*)sender();

    if(socketStream.status() != QDataStream::Ok)
    {
        std::cout << "Error" << "\n";
    }

    socketStream.startTransaction();
    socketStream >> buffer;

    if (!socketStream.commitTransaction())
    {
        qDebug() << QString("%1 :: Waiting for more data to come..").arg(p_TcpSocket->socketDescriptor());
        //emit newMessage(message);
        return;
    }

    QString header = buffer;

    QString type = header.split(",")[0].split(":")[1];
    qDebug() << "Type: " << type;


    switch (type.toInt())
    {
    case MSG_VERIFY:
    {
        QString result = header.split(",")[1].split(":")[1];
        qDebug() << "MSG_VERIFY: " << result;
        emit Verified(result.toInt() == 1);
    }
    }

    qDebug() << "header " << header;
    qDebug() << buffer.toStdString().c_str();
}

void Client::DiscardSocket()
{
    p_TcpSocket->deleteLater();
    p_TcpSocket = nullptr;
}
