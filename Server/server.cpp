#include "server.h"

Server::Server(int port)
{
    //p_UdpSocket = new QUdpSocket();

    //p_UdpSocket->bind(QHostAddress::Any, port);

    if (this->listen(QHostAddress::Any), port)
        std::cout << "Server start" << "\n";

    // тут еще какой то код конструктора //
    //connect(p_UdpSocket, &QUdpSocket::readyRead, this,  &Server::read);

}


void Server::IncomingConnection(qintptr socketDescriptor)
{
    p_TcpSocket = new QTcpSocket;
    p_TcpSocket->setSocketDescriptor(socketDescriptor);

    connect (p_TcpSocket, &QTcpSocket::readyRead, this, &Server::ReadyRead);
    connect (p_TcpSocket, &QTcpSocket::disconnected, this, &Server::deleteLater);

    v_Sockets.push_back(p_TcpSocket);

    std::cout << "Client connected" << socketDescriptor << "\n";
}

void Server::ReadyRead ()
{
    p_TcpSocket = (QTcpSocket*)sender();
    QDataStream in(p_TcpSocket);

    in.setVersion(QDataStream::Qt_6_4);
    if(in.status() != QDataStream::Ok)
    {
        std::cout << "Error" << "\n";
    }

    std::cout << "Start reading ..." << "\n";
    QString str;
    in >> str;
    std::cout << "End reading." << "\n";

}

void Server::SendToClient(QString str)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);
    out << str;
    p_TcpSocket->write(Data);

}



void Server::send(QString str, int type)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);

    out << qint64(0);
    out << qint8(type);
    out << str;
    out.device()->seek(qint64(0));
    out << qint64(data.size() - sizeof(qint64));

    p_UdpSocket->writeDatagram(data, QHostAddress::Broadcast, i_Port);
}

void Server::read()
{
    QByteArray datagram;
    datagram.resize(p_UdpSocket->pendingDatagramSize());
    QHostAddress *address = new QHostAddress();
    p_UdpSocket->readDatagram(datagram.data(), datagram.size(), address);

    QDataStream in(&datagram, QIODevice::ReadOnly);

    qint64 size = -1;
    if(in.device()->size() > sizeof(qint64))
    {
        in >> size;
    }
    else
        return;

    if (in.device()->size() - sizeof(qint64) < size)
        return;

    qint8 type = 0;
    in >> type;

    switch (type)
    {
    case MSG_TYPE_USUAL:
        {
            QString str;
            in >> str;
            // код по перенаправке сообщения в классы выше //
            break;
        }

    }

    /*
    else if (type == PERSON_ONLINE)
    {
        // Добавление пользователя с считанным QHostAddress //
    }
    else if (type == WHO_IS_ONLINE)
    {
        sending(nickname, qint8(PERSON_ONLINE));
    }
    */

}
