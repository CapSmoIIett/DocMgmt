#include "server.h"


Server::Server(int port) :
    i_Port(port)
{
    Logger::Init();
    p_Server = new QTcpServer();

    if (!p_Server->listen(QHostAddress::Any, i_Port))
    {
        qDebug() << "Error listening";
        qDebug() << p_Server->serverError();
        return;
    }

    qDebug() << "Start listening";
    qDebug() << i_Port;

    connect(p_Server, &QTcpServer::newConnection, this, &Server::NewConnection);
    //connect(this, &Server::SendedClient, this, &Server::SendToClient);
    //connect(this, &Server::SendedSpecificClient, this, &Server::SendToSpecificClient);
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

    QString header = buffer;//encrypter(Encrypter::VERNAM).Decrypt(buffer);
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

        map_Users[socket] = db.GetUserData(username);
        ///map_Users.insert(socket, db.GetUserData(username));

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
            data += QString("Lvl%1:%2,").arg(i).arg(rights[i].i_acs_lvl);
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
        data += QString("Lvl:%1,").arg(right.i_acs_lvl);

        emit SendToClient(data);
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

    case MSG_UPLOAD_RIGHT_DATA:
    {
        Right right;
        right.i_ID = header.split(",")[1].split(":")[1].toInt();
        right.s_Name = header.split(",")[2].split(":")[1];
        right.i_acs_lvl = header.split(",")[3].split(":")[1].toInt();

        db.UpdateRightData(right);

    } break;

    case MSG_UPLOAD_CALENDAR:
    {
        int month = header.split(",")[1].split(":")[1].toInt();
        int year = header.split(",")[2].split(":")[1].toInt();

        auto tp = db.GetHolidays(month, year);

        auto users = std::get<0>(tp);
        auto holidays = std::get<1>(tp);

        QString data = QString("Type:%1,Size:%2,Month:%3,Year:%4,").arg(MSG_UPLOAD_CALENDAR).arg(users.size())
           .arg(month).arg(year);

        for (int i = 0; i < users.size(); i++)
        {
            data += QString("User%1:%2,").arg(i).arg(users[i]);
            data += QString("Size%1:%2,").arg(i).arg(holidays[i].size());

            for (int j = 0; j < holidays[i].size(); j++)
            {
                data += QString("date%1_%2:%3,").arg(i).arg(j).arg(holidays[i][j].toString("dd"));
            }
        }

        emit SendToClient(data);
    } break;

    case MSG_SET_HOLIDAY:
    {
        QString name = header.split(",")[1].split(":")[1];
        QDate date = QDate::fromString(header.split(",")[2].split(":")[1]);

        db.SetHoliday(date, db.GetUserID(name));

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
            data += QString("LVL%1:%2,").arg(i).arg(file.i_acs_lvl);
            data += QString("Date%1:%2,").arg(i).arg(file.dt_DateModified.toString(fileDateFormate));
        }

        emit SendToClient(data);
    } break;

    case MSG_DOWNLOAD_FILE:
    {
        QString path = header.split(",")[1].split(":")[1];


        int file_size = fb.GetFileSize(path);

        if (file_size < KB)
        {

            int user_id = header.split(",")[2].split(":")[1].toInt();

            qDebug() << db.GetUserAccessLvl(user_id) << " " << fb.GetAccessLvl(path);

            if (db.GetUserAccessLvl(user_id) > fb.GetAccessLvl(path))
            {
                qDebug() << "Not enogh lvl";
                break;
            }


            auto text = fb.GetFileBytes(path);
            QString data = QString("Type:%1,Size:%2,Path:%3,Flag:0,").arg(MSG_DOWNLOAD_FILE).arg(text.size()).arg(path);

            qDebug() << "text: " << text;

            data += QString("Data:");
            QByteArray bytes = data.toUtf8() + text;

            emit SendToClient(bytes);
        }
        else
        {
            static int size = 0;
            static QDataStream* in = nullptr;
            static QFile* file = nullptr;



            if (!header.contains(QString("Flag")))
            {
                int user_id = header.split(",")[2].split(":")[1].toInt();

                qDebug() << db.GetUserAccessLvl(user_id) << " " << fb.GetAccessLvl(path);

                if (db.GetUserAccessLvl(user_id) > fb.GetAccessLvl(path))
                {
                    qDebug() << "Not enogh lvl";
                    break;
                }

                size = fb.GetFileSize(path);

                file = fb.GetFilePointer(path);
                in = new QDataStream(file);

                QString data = QString("Type:%1,Size:%2,Path:%3,Flag:%4,").arg(MSG_DOWNLOAD_FILE).arg(0).arg(path).arg(FLAG_FILE_TRANSFER_START);
                emit SendToClient(data.toUtf8());

                break;
            }

            if (size > KB)
            {
                QString msg = QString("Type:%1,Size:%2,Path:%3,Flag:%4,Data:").arg(MSG_DOWNLOAD_FILE).arg(KB).arg(path).arg(FLAG_FILE_TRANSFER_CONTINUE);
                QByteArray bytes (KB, 0);

                qDebug() << "size: " << size;

                in->readRawData(bytes.data(), bytes.size());

                qDebug() << bytes.size();

                emit SendToClient(msg.toUtf8() + bytes);

                size -= KB;
            }
            else if (size > 0)
            {
                QString msg = QString("Type:%1,Size:%2,Path:%3,Flag:%4,Data:").arg(MSG_DOWNLOAD_FILE).arg(KB).arg(path).arg(FLAG_FILE_TRANSFER_CONTINUE);
                QByteArray bytes (size, 0);

                qDebug() << "size: " << size;

                in->readRawData(bytes.data(), bytes.size());

                emit SendToClient(msg.toUtf8() + bytes);

                file->close();
                delete in;
                delete file;
            }


        }


    } break;

    case MSG_UPLOAD_FILE:
    {
        QString name = header.split(",")[1].split(":")[1];
        QString text = header.split(",")[2].split(":")[1];

        fb.CreateFile(name, text.toUtf8());

    } break;

    case MSG_CHANGE_ACS_LVL:
    {
        QString name = header.split(",")[1].split(":")[1];
        int lvl = header.split(",")[2].split(":")[1].toInt();

        fb.ChangeAccessLvl(name, lvl);

    } break;

    case MSG_SEND_MSG:
    {
        QString text = header.split(",")[1].split(":")[1];
        int id_sender = header.split(",")[2].split(":")[1].toInt();
        int id_accepter = header.split(",")[3].split(":")[1].toInt();

        db.SaveMsg(text, id_sender, id_accepter);

        QTcpSocket* accepter = nullptr;
        for (QMap<QTcpSocket*, User>::Iterator it = map_Users.begin(); it != map_Users.end(); it++)
        {
            if (it.value().i_ID == id_accepter)
                accepter = it.key();
        }

        QString data = QString("Type:%1,Text:%2,Sender:%3,Recepient:%4,Date:%5").arg(MSG_SEND_MSG).arg(text).
                       arg(id_sender).arg(id_accepter).arg(QDateTime::currentDateTime().toString());

        emit SendToSpecificClient(accepter, data);

    } break;

    case MSG_UPLOAD_MSGS:
    {
        int id1  = header.split(",")[1].split(":")[1].toInt();
        int id2  = header.split(",")[2].split(":")[1].toInt();

        auto messages = db.GetMessages(id1, id2);

        QString data = QString("Type:%1,Size:%2,").arg(MSG_UPLOAD_MSGS).arg(messages.size());

        for (int i = 0; i < messages.size(); i++)
        {
            auto msg = messages[i];

            data += QString("Text%1:%2,").arg(i).arg(msg.text);
            data += QString("Sender%1:%2,").arg(i).arg(msg.sender);
            data += QString("Recipient%1:%2,").arg(i).arg(msg.recepient);
            data += QString("Date%1:%2,").arg(i).arg(msg.date_time.toString());
        }

        emit SendToClient(data);

    } break;



    }


}

void Server::DiscardSocket()
{
    auto socket = reinterpret_cast<QTcpSocket*>(sender());

    qDebug() << QString("%1 :: disconect").arg(socket->socketDescriptor());

    auto it = set_Sockets.find(socket);

    if (it != set_Sockets.end())
    {
        set_Sockets.remove(*it);
    }

    auto it2 = map_Users.find(socket);

    if (it2 != map_Users.end())
    {
        map_Users.remove(socket);
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
    qDebug() << str;

    auto socket = reinterpret_cast<QTcpSocket*>(sender());

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_6_4);

    QByteArray byteArray;
    byteArray.prepend(str.toUtf8());

    socketStream << byteArray;
}

void Server::SendToClient(QByteArray str)
{
    qDebug() << str;

    auto socket = reinterpret_cast<QTcpSocket*>(sender());

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_6_4);

    socketStream << str;
}

void Server::SendToSpecificClient(QTcpSocket* socket, QString str)
{
    qDebug() << socket << " " << str;

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

