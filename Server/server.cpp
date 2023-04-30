#include "server.h"


Server::Server(int port) :
    i_Port(port)
{
    p_Server = new QTcpServer();

    if (!p_Server->listen(QHostAddress::Any, i_Port))
    {
        qDebug() << "Error listening";
        return;
    }

    qDebug() << "Start listening";

    connect(p_Server, &QTcpServer::newConnection, this, &Server::NewConnection);
    connect(this, &Server::SendedClient, this, &Server::SendToClient);
}

Server::~Server()
{
    for (auto socket : set_Sockets)
    {
        socket->close();
        socket->deleteLater();
    }

    p_Server->close();
    p_Server->deleteLater();
}

void Server::NewConnection()
{
    while (p_Server->hasPendingConnections())
        AppendToSocketLists(p_Server->nextPendingConnection());
}

void Server::AppendToSocketLists(QTcpSocket* socket)
{
    set_Sockets.insert(socket);
    connect (socket, &QTcpSocket::readyRead, this, &Server::ReadSocket);
    connect (socket, &QTcpSocket::disconnected, this, &Server::DiscardSocket);
    connect (socket, &QTcpSocket::errorOccurred, this, &Server::DisplayError);

    qDebug() << QString("Client connected, socket: %1").arg(socket->socketDescriptor());
}

void Server::ReadSocket()
{
    qDebug();
    qDebug() << "Server::ReadSocket";


    auto socket = reinterpret_cast<QTcpSocket*>(sender());

    QByteArray buffer;
    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_6_4);

    socketStream.startTransaction();
    socketStream >> buffer;

    if (!socketStream.commitTransaction())
    {
        qDebug() << QString("%1 :: Waiting for more data to come..").arg(socket->socketDescriptor());
        //emit newMessage(message);
        return;
    }

    //QString msg = buffer;
    //ProcessingMessage(buffer);

    QString header = buffer;

    QString type = header.split(",")[0].split(":")[1];
    qDebug() << "Type: " << type;

    switch (type.toInt())
    {
    case MSG_VERIFY:
    {
        QString username = header.split(",")[1].split(":")[1];
        QString password = header.split(",")[2].split(":")[1];

        qDebug() << "Username: " << username;
        qDebug() << "Password: " << password;

        bool isVerified = false;

        isVerified = db.Verify(username, password);

        qDebug() << "Verified: " << isVerified;

        emit SendToClient(QString("Type:%1,result:%2").arg(MSG_VERIFY).arg(isVerified));
    } break;

    case MSG_ALL_USERS:
    {
        auto users = db.GetUsersList();

        QString data = QString("Type:%1,Size:%2,").arg(MSG_ALL_USERS).arg(users.size());
        for (int i = 0; i < users.size(); i++)
        {
            data += QString("ID%1:%2,").arg(i).arg(users[i].i_ID);
            data += QString("Full_Name_%1:%2,").arg(i).arg(users[i].s_Full_Name);
            data += QString("Office_%1:%2,").arg(i).arg(users[i].s_Office);
            data += QString("Right_%1:%2,").arg(i).arg(users[i].s_Right);
        }

        emit SendToClient(data);
    } break;

    case MSG_ADD_USER:
    {
        db.AddUser();
    } break;
    case MSG_LOAD_DATA_USER:
    {
        QString username = header.split(",")[1].split(":")[1];

        auto user = db.GetUserData(username);

        QString data = QString("Type:%1,").arg(MSG_LOAD_DATA_USER);
        data += QString("ID%1:%2,").arg(user.i_ID);
        data += QString("Full_Name:%1,").arg(user.s_Full_Name);
        data += QString("Office:%1,").arg(user.s_Office);
        data += QString("Right:%1,").arg(user.s_Right);

        emit SendToClient(data);
    }break;

    case MSG_LOAD_RIGHTS:
    {
        auto rights = db.GetRights();

        QString data = QString("Type:%1,Size:%2,").arg(MSG_LOAD_RIGHTS).arg(rights.size());
        for (int i = 0; i < rights.size(); i++)
        {
            data += QString("ID%1:%2,").arg(i).arg(rights[i].i_ID);
            data += QString("Name%1:%2,").arg(i).arg(rights[i].s_Name);
        }

        emit SendToClient(data);
    } break;

    case MSG_ADD_RIGHT:
    {
        db.AddRight();
    } break;
    case MSG_REMOVE_USER:
    {
        int id = header.split(",")[1].split(":")[1].toInt();

        db.RemoveUser(id);
    } break;
    case MSG_LOAD_OFFICE:
    {
        auto offices = db.GetOffices();

        QString data = QString("Type:%1,Size:%2,").arg(MSG_LOAD_OFFICE).arg(offices.size());
        for (int i = 0; i < offices.size(); i++)
        {
            data += QString("ID%1:%2,").arg(i).arg(offices[i].i_ID);
            data += QString("Name%1:%2,").arg(i).arg(offices[i].s_Name);
            data += QString("Address%1:%2,").arg(i).arg(offices[i].s_Address);
        }

        emit SendToClient(data);
    } break;
    case MSG_ADD_OFFICE:
    {
        db.AddOffice();

    } break;

    }

    qDebug() << buffer.toStdString().c_str();

}

void Server::DiscardSocket()
{
    auto socket = reinterpret_cast<QTcpSocket*>(sender());

    auto it = set_Sockets.find(socket);

    if (it != set_Sockets.end())
    {
        qDebug() << QString("%1 :: disconect").arg(socket->socketDescriptor());
        set_Sockets.remove(*it);
    }

    socket->deleteLater();
}

void Server::DisplayError(QAbstractSocket::SocketError socketError)
{
    switch(socketError)
    {
    case QAbstractSocket::HostNotFoundError:
        qDebug() << "Host not found";
        break;
    }
}

void Server::SendToClient(QString str)
{
    qDebug();
    qDebug() << "Server::SendToClient";
    qDebug() << str;

    auto socket = reinterpret_cast<QTcpSocket*>(sender());

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_6_4);

    QByteArray byteArray;
    byteArray.prepend(str.toUtf8());

    socketStream << byteArray;

}




void Server::ProcessingMessage(QString header)
{
    qDebug() << "Start msg processing";

    QString type = header.split(",")[0].split(":")[1];
    qDebug() << "Type: " << type;

    switch (type.toInt())
    {
    case MSG_VERIFY:
    {
        QString username = header.split(",")[1].split(":")[1];
        QString password = header.split(",")[2].split(":")[1];

        qDebug() << "Username: " << username;
        qDebug() << "Password: " << password;

        bool isVerified = false;

        isVerified = db.Verify(username, password);

        qDebug() << "Verified: " << isVerified;
    } break;
    }
}


/*
Server::Server(int port)
{
    //p_UdpSocket = new QUdpSocket();

    //p_UdpSocket->bind(QHostAddress::Any, port);

    if (this->listen(QHostAddress::Any), port)
        qDebug() << "Start listening port " << port;

    p_TcpSocket = new QTcpSocket(this);


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

    qDebug() << "Client connected" << socketDescriptor;
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

    int type = 0;

    in >> type;

    switch (type)
    {
    case MSG_VERIFY:
    {
        qDebug() << "MSG_VERIFY";

        QString username;
        QString password;
        bool isVerified = false;

        in >> username;
        in >> password;

        isVerified = db.Verify(username, password);

        SendToClient("Hi");


        qDebug() << "MSG_VERIFY end";
    } break;

    }

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

    qDebug() << type;

    switch (type)
    {
    /*
     * case MSG_TYPE_USUAL:
        {
            QString str;
            in >> str;
        } break;
*/
/*
    case MSG_VERIFY:
    {
        qDebug() << "MSG_VERIFY";

        QString username;
        QString password;
        bool isVerified = false;

        in >> username;
        in >> password;

        isVerified = db.Verify(username, password);

        SendToClient("Hi");


        qDebug() << "MSG_VERIFY end";
    } break;

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
/*
}

QString Server::GenerateToken(QString user)
{
    static int token = 100000;
    auto it =  m_Tokens.find(user);

    if (it != m_Tokens.end())
    {
        m_Tokens[user] = QString::number(token);
        return QString::number(token++);
    }

    return it.value();

}
*/
