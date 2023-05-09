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

QString Client::getIP()
{
    return s_IP;
}

void Client::setIP(const QString &ip)
{
    s_IP = ip;
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

    //p_TcpSocket->waitForConnected();

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

void Client::SendRequest (QString message)
{
    qDebug();
    qDebug() << "Client::SendRequest";
    qDebug() << QTime::currentTime().toString();
    qDebug() << message;

    QString str = encrypter(Encrypter::VERNAM)(message);

    qDebug() << str;
    qDebug() << encrypter(Encrypter::VERNAM).Decrypt(str);

    if (!p_TcpSocket)
    {
        qDebug () << "Verify: socket error";
        return;
    }

    if (!p_TcpSocket->isOpen())
    {
        qDebug () << "Verify: socket close";
        return;
    }

    QDataStream socketStream(p_TcpSocket);
    socketStream.setVersion(QDataStream::Qt_6_4);

    QByteArray byteArray;
    byteArray.prepend(str.toUtf8());

   // qDebug() << byteArray;

    socketStream << byteArray;
}

bool Client::VerifyRequest (QString username, QString password)
{
    SendRequest(QString("Type:%1,Username:%2,Password:%3").arg(MSG_VERIFY).arg(username).arg(password));

    return true;
}

void Client::UsersListRequest()
{
    SendRequest(QString("Type:%1").arg(MSG_ALL_USERS));
}

void Client::AddUserRequest()
{
    SendRequest(QString("Type:%1").arg(MSG_ADD_USER));
}

void Client::loadUserDataRequest(QString username)
{
    SendRequest(QString("Type:%1,Username:%2").arg(MSG_LOAD_DATA_USER).arg(username));
}

void Client::loadUserDataRequest(int id)
{
    SendRequest(QString("Type:%1,ID:%2").arg(MSG_LOAD_DATA_USER_BY_ID).arg(id));
}

void Client::loadRightsRequest()
{
    SendRequest(QString("Type:%1").arg(MSG_LOAD_RIGHTS));
}

void Client::addRightsRequest()
{
    SendRequest(QString("Type:%1").arg(MSG_ADD_RIGHT));
}

void Client::removeUserRequest(int id)
{
    SendRequest(QString("Type:%1,ID:%2").arg(MSG_REMOVE_USER).arg(id));
}

void Client::loadOfficesRequest()
{
    SendRequest(QString("Type:%1").arg(MSG_LOAD_OFFICES));
}

void Client::addOfficeRequest()
{
    SendRequest(QString("Type:%1").arg(MSG_ADD_OFFICE));
}

void Client::loadOfficeRequest(int id)
{
    SendRequest(QString("Type:%1,ID:%2").arg(MSG_LOAD_OFFICE).arg(id));
}

void Client::loadRightRequest(int id)
{
    SendRequest(QString("Type:%1,ID:%2").arg(MSG_LOAD_RIGHT).arg(id));
}

void Client::loadFilesRequest(QString path)
{
    SendRequest(QString("Type:%1,Path:%2").arg(MSG_GET_FILE_LIST).arg(path));
}

void Client::downloadFileRequest(QString path)
{
    SendRequest(QString("Type:%1,Path:%2").arg(MSG_DOWNLOAD_FILE).arg(path));
}

void Client::uploadUserData(User user)
{
    SendRequest(QString("Type:%1,ID:%2,Name:%3,Right:%4,Office:%5")
        .arg(MSG_UPLOAD_USER_DATA).arg(user.i_ID).arg(user.s_Full_Name).arg(user.s_Right).arg(user.s_Office));
}

void Client::ReadSocket ()
{
    qDebug();
    qDebug() << "Client::ReadSocket";
    qDebug() << QTime::currentTime().toString() ;

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

        emit onVerified(result.toInt() == 1);
    } break;

    case MSG_ALL_USERS:
    {
        QVector<User> users;
        QString size = header.split(",")[1].split(":")[1];

        qDebug() << "MSG_ALL_USERS: " << size;

        for (int i = 0; i < size.toInt(); i++)
        {
            User user;
            user.i_ID = header.split(",")[1 + (i * 4) + 1].split(":")[1].toInt();
            user.s_Full_Name = header.split(",")[1 + (i * 4) + 2].split(":")[1];
            user.s_Office = header.split(",")[1 + (i * 4) + 3].split(":")[1];
            user.s_Right = header.split(",")[1 + (i * 4) + 4].split(":")[1];

            //qDebug() << user.i_ID;
            //qDebug() << user.s_Full_Name;
            //qDebug() << user.s_Right;
            //qDebug() << user.s_Office;

            users.push_back(user);
        }

        emit onGetUsersList(users);
    } break;

    case MSG_LOAD_DATA_USER:
    {
        qDebug() << "MSG_LOAD_DATA_USER";

        User user;
        user.i_ID = header.split(",")[1].split(":")[1].toInt();
        user.s_Full_Name = header.split(",")[2].split(":")[1];
        user.s_Office = header.split(",")[3].split(":")[1];
        user.s_Right = header.split(",")[4].split(":")[1];

        emit onGetUserData(user);
    } break;

    case MSG_LOAD_RIGHTS:
    {
        QVector<Right> rights;
        QString size = header.split(",")[1].split(":")[1];

        qDebug() << "MSG_LOAD_RIGHTS" << size;

        for (int i = 0; i < size.toInt(); i++)
        {
            Right right;
            right.i_ID = header.split(",")[1 + (i * 2)+ 1].split(":")[1].toInt();
            right.s_Name = header.split(",")[1 + (i * 2) + 2].split(":")[1];

            //qDebug() << header.split(",")[1 + i + 1];
            //qDebug() << header.split(",")[1 + i + 2];

            //qDebug() << "ID: " << right.i_ID;
            //qDebug() << "Name: " << right.s_Name;

            rights.push_back(right);
        }

        emit onGetRights(rights);
    } break;

    case MSG_LOAD_OFFICES:
    {
        QVector<Office> offices;
        QString size = header.split(",")[1].split(":")[1];

        qDebug() << "MSG_LOAD_OFFICES" << size;

        for (int i = 0; i < size.toInt(); i++)
        {
            Office office;
            office.i_ID = header.split(",")[1 + (i * 3)+ 1].split(":")[1].toInt();
            office.s_Name = header.split(",")[1 + (i * 3) + 2].split(":")[1];
            office.s_Address = header.split(",")[1 + (i * 3) + 3].split(":")[1];

            //qDebug() << header.split(",")[1 + i + 1];
            //qDebug() << header.split(",")[1 + i + 2];

            //qDebug() << "ID: " << office.i_ID;
            //qDebug() << "Name: " << office.s_Name;
            //qDebug() << "Address: " << office.s_Address;

            offices.push_back(office);
        }

        emit onGetOffices(offices);

    } break;

    case MSG_LOAD_OFFICE:
    {
        qDebug() << "MSG_LOAD_OFFICE";

        Office office;
        office.i_ID = header.split(",")[1].split(":")[1].toInt();
        office.s_Name = header.split(",")[2].split(":")[1];
        office.s_Address = header.split(",")[3].split(":")[1];

        emit onGetOffice(office);

    } break;

    case MSG_LOAD_RIGHT:
    {
        qDebug() << "MSG_LOAD_RIGHT";

        Right right;
        right.i_ID = header.split(",")[1].split(":")[1].toInt();
        right.s_Name = header.split(",")[2].split(":")[1];

        emit onGetRight(right);
    } break;


    case MSG_GET_FILE_LIST:
    {
        qDebug() << "MSG_GET_FILE_LIST";

        QVector<File> files;
        QString size = header.split(",")[1].split(":")[1];

        qDebug() << "Size" << size;

        for (int i = 0; i < size.toInt(); i++)
        {
            File file;

            file.s_Name = header.split(",")[1 + (i * 4) + 1].split(":")[1];
            file.s_Type = header.split(",")[1 + (i * 4) + 2].split(":")[1];
            file.i_Size = header.split(",")[1 + (i * 4) + 3].split(":")[1].toInt();
            file.dt_DateModified = QDateTime::fromString(header.split(",")[1 + (i * 4) + 4].split(":")[1]);

            files.push_back(file);
        }

        emit onGetFiles(files);

    } break;

    case MSG_DOWNLOAD_FILE:
    {
        qDebug() << "MSG_DOWNLOAD_FILE";

        QVector<File> files;
        QString size = header.split(",")[1].split(":")[1];
        QString name = header.split(",")[2].split(":")[1];

        qDebug() << "Size" << size;
        qDebug() << "Name" << name;

        QFile file(name);

        if(!file.open(QIODevice::ReadWrite))
        {
            qDebug() << "Error open file";
            qDebug() << file.errorString();
        }
        else
        {
            QTextStream stream(&file);
            QString text = header.split(",")[3].split(":")[1];
            stream << text;
    void ConnectToServer();
        }

    } break;


    }

    qDebug() << QTime::currentTime().toString();
    qDebug()  << buffer.toStdString().c_str();
}

void Client::DiscardSocket()
{
    p_TcpSocket->deleteLater();
    p_TcpSocket = nullptr;
}



