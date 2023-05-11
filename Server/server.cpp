#include "server.h"


Server::Server(int port) :
    i_Port(port)
{
    Logger::Init();
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

    Logger::clean();
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
    qDebug() << QTime::currentTime().toString() ;


    auto socket = reinterpret_cast<QTcpSocket*>(sender());

    QByteArray buffer;
    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_6_4);

    socketStream.startTransaction();
    socketStream >> buffer;
    qDebug() << buffer.toStdString().c_str();

    if (!socketStream.commitTransaction())
    {
        qDebug() << QString("%1 :: Waiting for more data to come..").arg(socket->socketDescriptor());
        //emit newMessage(message);
        return;
    }

    //QString msg = buffer;
    //ProcessingMessage(buffer);

    QString header = encrypter(Encrypter::VERNAM).Decrypt(buffer);
    qDebug() << header;
    qDebug() << QTime::currentTime().toString() ;

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

        User user = db.GetUserData(username);

        QString data = QString("Type:%1,").arg(MSG_LOAD_DATA_USER);
        data += QString("ID:%2,").arg(user.i_ID);
        data += QString("Full_Name:%1,").arg(user.s_Full_Name);
        data += QString("Office:%1,").arg(user.s_Office);
        data += QString("Right:%1,").arg(user.s_Right);

        emit SendToClient(data);
    } break;
    case MSG_LOAD_DATA_USER_BY_ID:
    {
        QString id = header.split(",")[1].split(":")[1];

        auto user = db.GetUserData(id.toInt());

        QString data = QString("Type:%1,").arg(MSG_LOAD_DATA_USER);
        data += QString("ID:%2,").arg(user.i_ID);
        data += QString("Full_Name:%1,").arg(user.s_Full_Name);
        data += QString("Office:%1,").arg(user.s_Office);
        data += QString("Right:%1,").arg(user.s_Right);

        emit SendToClient(data);
    } break;

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
    case MSG_LOAD_OFFICES:
    {
        auto offices = db.GetOffices();

        QString data = QString("Type:%1,Size:%2,").arg(MSG_LOAD_OFFICES).arg(offices.size());
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

    case MSG_LOAD_OFFICE:
    {

        QString id = header.split(",")[1].split(":")[1];

        auto office = db.GetOffice(id.toInt());

        QString data = QString("Type:%1,").arg(MSG_LOAD_OFFICE);
        data += QString("ID:%1,").arg(office.i_ID);
        data += QString("Name:%1,").arg(office.s_Name);
        data += QString("Address:%1,").arg(office.s_Address);

        emit SendToClient(data);
    } break;

    case MSG_LOAD_RIGHT:
    {
        QString id = header.split(",")[1].split(":")[1];

        auto right = db.GetRight(id.toInt());

        QString data = QString("Type:%1,").arg(MSG_LOAD_RIGHT);
        data += QString("ID:%1,").arg(right.i_ID);
        data += QString("Name:%1,").arg(right.s_Name);

        emit SendToClient(data);
    } break;



    case MSG_GET_FILE_LIST:
    {
        QString path = header.split(",")[1].split(":")[1];

        auto files = fb.GetFileList(path);

        QString data = QString("Type:%1,Size:%2,").arg(MSG_GET_FILE_LIST).arg(files.size());

        for (int i = 0; i < files.size(); i++)
        {
            auto file = files[i];

            data += QString("Name%1:%2,").arg(i).arg(file.s_Name);
            data += QString("Type%1:%2,").arg(i).arg(file.s_Type);
            data += QString("Size%1:%2,").arg(i).arg(file.i_Size);
            data += QString("Date%1:%2,").arg(i).arg(file.dt_DateModified.toString(fileDateFormate));
        }

        emit SendToClient(data);
    } break;

    case MSG_DOWNLOAD_FILE:
    {
        QString path = header.split(",")[1].split(":")[1];

        auto text = fb.GetFile(path);

        QString data = QString("Type:%1,Size:%2,Path:%3,").arg(MSG_DOWNLOAD_FILE).arg(text.size()).arg(path);

        data += QString("Data:") + text;

        emit SendToClient(data);
    } break;

    case MSG_UPLOAD_FILE:
    {
        QString name = header.split(",")[1].split(":")[1];
        QString text = header.split(",")[2].split(":")[1];

        fb.CreateFile(name, text);

    } break;

    case MSG_UPLOAD_USER_DATA:
    {
        User user;
        user.i_ID = header.split(",")[1].split(":")[1].toInt();
        user.s_Full_Name = header.split(",")[2].split(":")[1];
        user.s_Right = header.split(",")[3].split(":")[1];
        user.s_Office = header.split(",")[4].split(":")[1];

        db.UpdateUserData(user);

    } break;


    }


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
    qDebug() << QTime::currentTime().toString();

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

