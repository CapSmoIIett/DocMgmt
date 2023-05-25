#include "client.h"


Client::Client(QString ip, int port) :
    s_IP(ip),
    i_Port(port)
{
    p_TcpSocket = new QTcpSocket(this);

    connect(p_TcpSocket, &QTcpSocket::readyRead, this, &Client::ReadSocket);
    connect(p_TcpSocket, &QTcpSocket::disconnected, this, &Client::DiscardSocket);
    connect(p_TcpSocket, &QTcpSocket::errorOccurred, this, [this](QAbstractSocket::SocketError socketError)
    {
        qDebug() << socketError;

        if (socketError == QAbstractSocket::OperationError)
        {
            p_TcpSocket->abort();
            p_TcpSocket->close();
        }
        //p_TcpSocket->reset();
    });

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

int Client::getPort()
{
    return i_Port;
}

void Client::setPort(const int &port)
{
    i_Port = port;
}

void Client::ConnectToServer()
{
    qDebug();
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

    qDebug() << "loger";

    //Logger("Client::SendRequest");// << "Test";

    QString str = message;//encrypter(Encrypter::VERNAM)(message);

    //qDebug() << str;
    //qDebug() << encrypter(Encrypter::VERNAM).Decrypt(str);

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
    SendRequest(QString("Type:%1,Username:%2,Password:%3").replace(",",SEP).arg(MSG_VERIFY).arg(username).arg(password));

    return true;
}

void Client::UsersListRequest()
{
    SendRequest(QString("Type:%1").replace(",",SEP).arg(MSG_ALL_USERS));
}

void Client::AddUserRequest()
{
    SendRequest(QString("Type:%1").replace(",",SEP).arg(MSG_ADD_USER));
}

void Client::loadUserDataRequest(QString username)
{
    SendRequest(QString("Type:%1,Username:%2").replace(",",SEP).arg(MSG_LOAD_DATA_USER).arg(username));
}

void Client::loadUserDataRequest(int id)
{
    SendRequest(QString("Type:%1,ID:%2").replace(",",SEP).arg(MSG_LOAD_DATA_USER_BY_ID).arg(id));
}

void Client::loadRightsRequest()
{
    SendRequest(QString("Type:%1").replace(",",SEP).arg(MSG_LOAD_RIGHTS));
}

void Client::addRightsRequest()
{
    SendRequest(QString("Type:%1").replace(",",SEP).arg(MSG_ADD_RIGHT));
}

void Client::removeUserRequest(int id)
{
    SendRequest(QString("Type:%1,ID:%2").replace(",",SEP).arg(MSG_REMOVE_USER).arg(id));
}

void Client::loadOfficesRequest()
{
    SendRequest(QString("Type:%1").replace(",",SEP).arg(MSG_LOAD_OFFICES));
}

void Client::addOfficeRequest()
{
    SendRequest(QString("Type:%1").replace(",",SEP).arg(MSG_ADD_OFFICE));
}

void Client::loadOfficeRequest(int id)
{
    SendRequest(QString("Type:%1,ID:%2").replace(",",SEP).arg(MSG_LOAD_OFFICE).arg(id));
}

void Client::loadRightRequest(int id)
{
    SendRequest(QString("Type:%1,ID:%2").replace(",",SEP).arg(MSG_LOAD_RIGHT).arg(id));
}

void Client::loadFilesRequest(QString path)
{
    SendRequest(QString("Type:%1,Path:%2").replace(",",SEP).arg(MSG_GET_FILE_LIST).arg(path));
}

void Client::downloadFileRequest(QString path, int user_id)
{
    SendRequest(QString("Type:%1,Path:%2,User:%3").replace(",",SEP).arg(MSG_DOWNLOAD_FILE).arg(path).arg(user_id));
}

void Client::uploadUserData(User user)
{
    SendRequest(QString("Type:%1,ID:%2,Name:%3,Right:%4,Office:%5").replace(",",SEP)
        .arg(MSG_UPLOAD_USER_DATA).arg(user.i_ID).arg(user.s_Full_Name).arg(user.s_Right).arg(user.s_Office));
}

void Client::uploadRightData(Right right)
{
    SendRequest(QString("Type:%1,ID:%2,Name:%3,LVL:%4").replace(",",SEP)
        .arg(MSG_UPLOAD_RIGHT_DATA).arg(right.i_ID).arg(right.s_Name).arg(right.i_acs_lvl));
}

void Client::uploadFile(QString name, QString text)
{
    SendRequest(QString("Type:%1,Name:%2,Text:%3").replace(",",SEP).arg(MSG_UPLOAD_FILE).arg(name).arg(text.toUtf8()));
}

void Client::sendMessage(QString text, int id_sender, int id_accepter)
{
    SendRequest(QString("Type:%1,Text:%2,SEND:%3,ACCEPT:%4").replace(",",SEP).arg(MSG_SEND_MSG).arg(text).arg(id_sender).arg(id_accepter));
}

void Client::uploadMessages(int id1, int id2)
{
    SendRequest(QString("Type:%1,ID1:%2,ID2:%3").replace(",",SEP).arg(MSG_UPLOAD_MSGS).arg(id1).arg(id2));
}

void Client::changeAccessLvlFileRequest(QString name, int lvl)
{
    qDebug() << name << " " << lvl;
    SendRequest(QString("Type:%1,Name:%2,LVL:%3").replace(",",SEP).arg(MSG_CHANGE_ACS_LVL).arg(name).arg(lvl));
}

void Client::loadCalendarRequest(int month, int year)
{
    qDebug() << month << " " << year;
    SendRequest(QString("Type:%1,Month:%2,Year:%3").replace(",",SEP).arg(MSG_UPLOAD_CALENDAR).arg(month).arg(year));
}

void Client::setHolidayRequest(QDate date, QString name)
{
    qDebug() << name;
    SendRequest(QString("Type:%1,Name:%2,Date:%3").replace(",",SEP).arg(MSG_SET_HOLIDAY).arg(name).arg(date.toString()));
}

void Client::ReadSocket ()
{
    qDebug();

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

    QString type = header.split(SEP)[0].split(":")[1];
    //qDebug() << header;
    qDebug() << "Type: " << type;


    switch (type.toInt())
    {
    case MSG_VERIFY:
    {
        QString result = header.split(SEP)[1].split(":")[1];

        qDebug() << "MSG_VERIFY: " << result;

        emit onVerified(result.toInt() == 1);
    } break;

    case MSG_ALL_USERS:
    {
        QVector<User> users;
        QString size = header.split(SEP)[1].split(":")[1];

        qDebug() << "MSG_ALL_USERS: " << size;

        for (int i = 0; i < size.toInt(); i++)
        {
            User user;
            user.i_ID = header.split(SEP)[1 + (i * 4) + 1].split(":")[1].toInt();
            user.s_Full_Name = header.split(SEP)[1 + (i * 4) + 2].split(":")[1];
            user.s_Office = header.split(SEP)[1 + (i * 4) + 3].split(":")[1];
            user.s_Right = header.split(SEP)[1 + (i * 4) + 4].split(":")[1];

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
        User user;
        user.i_ID = header.split(SEP)[1].split(":")[1].toInt();
        user.s_Full_Name = header.split(SEP)[2].split(":")[1];
        user.s_Office = header.split(SEP)[3].split(":")[1];
        user.s_Right = header.split(SEP)[4].split(":")[1];


        emit onGetUserData(user);
    } break;

    case MSG_LOAD_RIGHTS:
    {
        QVector<Right> rights;
        int size = header.split(SEP)[1].split(":")[1].toInt();

        qDebug() << "MSG_LOAD_RIGHTS" << size;

        for (int i = 0; i < size; i++)
        {
            Right right;
            right.i_ID = header.split(SEP)[1 + (i * 3)+ 1].split(":")[1].toInt();
            right.s_Name = header.split(SEP)[1 + (i * 3) + 2].split(":")[1];
            right.i_acs_lvl = header.split(SEP)[1 + (i * 3)+ 3].split(":")[1].toInt();

            rights.push_back(right);
        }

        emit onGetRights(rights);
    } break;

    case MSG_LOAD_OFFICES:
    {
        QVector<Office> offices;
        QString size = header.split(SEP)[1].split(":")[1];

        qDebug() << "MSG_LOAD_OFFICES" << size;

        for (int i = 0; i < size.toInt(); i++)
        {
            Office office;
            office.i_ID = header.split(SEP)[1 + (i * 3)+ 1].split(":")[1].toInt();
            office.s_Name = header.split(SEP)[1 + (i * 3) + 2].split(":")[1];
            office.s_Address = header.split(SEP)[1 + (i * 3) + 3].split(":")[1];

            //qDebug() << header.split(SEP)[1 + i + 1];
            //qDebug() << header.split(SEP)[1 + i + 2];

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
        office.i_ID = header.split(SEP)[1].split(":")[1].toInt();
        office.s_Name = header.split(SEP)[2].split(":")[1];
        office.s_Address = header.split(SEP)[3].split(":")[1];

        emit onGetOffice(office);

    } break;

    case MSG_LOAD_RIGHT:
    {
        qDebug() << "MSG_LOAD_RIGHT";

        Right right;
        right.i_ID = header.split(SEP)[1].split(":")[1].toInt();
        right.s_Name = header.split(SEP)[2].split(":")[1];
        right.i_acs_lvl = header.split(SEP)[3].split(":")[1].toInt();

        emit onGetRight(right);
    } break;

    case MSG_UPLOAD_CALENDAR:
    {
        int size = header.split(SEP)[1].split(":")[1].toInt();
        int month = header.split(SEP)[2].split(":")[1].toInt();
        int year = header.split(SEP)[3].split(":")[1].toInt();

        qDebug() << size << " " << month << " " << year;

        QVector<QString> users;
        QVector<QVector<QDate>> holidays;

        int it = 4;
        for (int i = 0; i < size; i++)
        {
            QString name = header.split(SEP)[it++].split(":")[1];
            int size = header.split(SEP)[it++].split(":")[1].toInt();

            users.push_back(name);

            QVector<QDate> dates;
            for (int j = 0; j < size; j++)
            {
                int day = header.split(SEP)[it++].split(":")[1].toInt();
                dates.push_back(QDate(year, month, day));
            }
            holidays.push_back(dates);
        }

        emit onGetHolidays(users, holidays);
    } break;


    case MSG_WARNING:
    {
        QString text = header.split(SEP)[1].split(":")[1];
        emit onWarning(text);
    }


    case MSG_GET_FILE_LIST:
    {
        qDebug() << "MSG_GET_FILE_LIST";

        QVector<File> files;
        QString size = header.split(SEP)[1].split(":")[1];

        qDebug() << "Size" << size;

        for (int i = 0; i < size.toInt(); i++)
        {
            File file;

            file.s_Name = header.split(SEP)[1 + (i * 5) + 1].split(":")[1];
            file.s_Type = header.split(SEP)[1 + (i * 5) + 2].split(":")[1];
            file.i_Size = header.split(SEP)[1 + (i * 5) + 3].split(":")[1].toInt();
            file.i_acs_lvl = header.split(SEP)[1 + (i * 5) + 4].split(":")[1].toInt();
            file.dt_DateModified = QDateTime::fromString(header.split(SEP)[1 + (i * 5) + 5].split(":")[1]);

            files.push_back(file);
        }

        emit onGetFiles(files);

    } break;

    case MSG_DOWNLOAD_FILE:
    {
        qDebug() << "MSG_DOWNLOAD_FILE";

        QString size = header.split(SEP)[1].split(":")[1];
        QString name = header.split(SEP)[2].split(":")[1];
        int flag = header.split(SEP)[3].split(":")[1].toInt();

        qDebug() << "Size" << size;
        qDebug() << "Name" << name;
        qDebug() << flag;

        //TODO ПЕРЕНЕСИ ЗАПИСБ В ФАЙЛ В APPENGINE


        QFile file(name);

        if(!file.open(QIODevice::ReadWrite | (flag == 0 ? QIODevice::Truncate : QIODevice::Append)))
        {
            qDebug() << "Error open file";
            qDebug() << file.errorString();
            break;
        }

        if (flag == FLAG_FILE_TRANSFER_START)
        {
            file.resize(0);
            file.close();
            SendRequest(QString("Type:%1,Path:%2,Flag:%3").arg(MSG_DOWNLOAD_FILE).arg(name).arg(FLAG_FILE_TRANSFER_CONTINUE));
            break;
        }

        int pos = buffer.indexOf("Data:");
        int endPos = buffer.indexOf(":", pos);
        QByteArray text = buffer.mid(endPos + 1);

        file.write(text);

        if (flag != 0 && text.size() == KB)
        {
            qDebug();
            SendRequest(QString("Type:%1,Path:%2,Flag:%3").arg(MSG_DOWNLOAD_FILE).arg(name).arg(FLAG_FILE_TRANSFER_CONTINUE));
        }
        qDebug() <<text.size();

        file.close();

    } break;

    case MSG_SEND_MSG:
    {
        QString text = header.split(SEP)[1].split(":")[1];
        int sender = header.split(SEP)[2].split(":")[1].toInt();
        int recepient = header.split(SEP)[3].split(":")[1].toInt();
        QDateTime dtime = QDateTime::fromString(header.split(SEP)[4].split(":")[1]);

        qDebug() << sender << " " << recepient;

        Message msg;
        msg.text = text;
        msg.sender = sender;
        msg.recepient = recepient;
        msg.date_time = dtime;


        emit onGetMessage(msg);

    } break;

    case MSG_UPLOAD_MSGS:
    {
        qDebug();

        QVector<Message> messages;
        QString size = header.split(SEP)[1].split(":")[1];

        qDebug() << "Size" << size;

        for (int i = 0; i < size.toInt(); i++)
        {
            Message msg;

            msg.text = header.split(SEP)[1 + (i * 4) + 1].split(":")[1];
            msg.sender = header.split(SEP)[1 + (i * 4) + 2].split(":")[1].toInt();
            msg.recepient = header.split(SEP)[1 + (i * 4) + 3].split(":")[1].toInt();
            msg.date_time = QDateTime::fromString(header.split(SEP)[1 + (i * 4) + 4].split(":")[1]);

            messages.push_back(msg);
        }

        emit onGetMessages(messages);

    } break;

    }

    qDebug() << QTime::currentTime().toString();
    //qDebug()  << buffer;
}

void Client::DiscardSocket()
{
    p_TcpSocket->deleteLater();
    p_TcpSocket = nullptr;
}



