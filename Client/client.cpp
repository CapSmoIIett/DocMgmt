#include "client.h"


Client::Client(QString ip, int port) :
    s_IP(ip),
    i_Port(port)
{
    p_TcpSocket = new QTcpSocket(this);

    connect(p_TcpSocket, &QTcpSocket::readyRead, this, &Client::ReadyRead);

}

void Client::ConnectToServer()
{
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

QString ReadFromServer()
{

}

bool Client::Verify (QString username, QString password)
{

    if (!IsConnected())
        ConnectToServer();

    SendToServer(MSG_VERIFY_TEXT);
    SendToServer(username);
    SendToServer(password);

}

void Client::ReadyRead ()
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
    //std::cout << str << "\n";
    std::cout << "End reading." << "\n";

}
