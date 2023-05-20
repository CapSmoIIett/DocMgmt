#include "appengine.h"

#include <QHash>

//#include "VersyPDF.h"
#include "../versypdf/VersyPDF.h"


AppEngine::AppEngine(QObject* parent) :
    QObject(parent),
    s_IP("127.0.0.1")
{
    Logger::Init();

    connect(&this->client, &Client::onVerified, this, [this](bool result) { qDebug() << "call"; emit this->verified(result); });
    connect(&this->client, &Client::onGetUserData, this, &AppEngine::GetCurUser);

    connect(this, &AppEngine::onChangeIP, this, [this]()
    {
        this->client.setIP(this->s_IP);
        this->client.ConnectToServer();
    });

    connect(this, &AppEngine::onChangePort, this, [this]()
    {
        this->client.setPort(this->s_Port.toInt());
        this->client.ConnectToServer();
    });
}

AppEngine::~AppEngine()
{
    Logger::clean();
}

QString AppEngine::userName()
{
    return user.s_Full_Name;
}

void AppEngine::setUserName(const QString &userName)
{
    user.s_Full_Name = userName;
}

QString AppEngine::password()
{
    return s_Password;
}

void AppEngine::setPassword(const QString &password)
{
    s_Password = password;
}

QString AppEngine::office()
{
    return user.s_Office;
}

void AppEngine::setOffice(const QString &office)
{
    user.s_Office = office;
}

QString AppEngine::right()
{
    return user.s_Right;
}

void AppEngine::setRight(const QString &right)
{
    user.s_Right = right;
}

int AppEngine::id()
{
    return user.i_ID;
}

void AppEngine::setID(const int &id)
{
    user.i_ID = id;
}

Client& AppEngine::GetClient()
{
    return client;
}

QString AppEngine::ip()
{
    return s_IP;
}

void AppEngine::setIP(const QString &ip)
{
    s_IP = ip;
    emit onChangeIP();
}

QString AppEngine::port()
{
    qDebug();
    return s_Port;
}

void AppEngine::setPort(const QString &port)
{
    s_Port = port;
    qDebug() << s_Port;
    emit onChangePort();
}

bool AppEngine::verify()
{
    qDebug();
    qDebug() << "AppEngine::verify";
    qDebug() << user.s_Full_Name << " " << s_Password;

    if (!client.IsConnected())
    {
        client.ConnectToServer();
        return false;
    }

    client.VerifyRequest(user.s_Full_Name, s_Password);

    return true;
}

void AppEngine::usersListRequest()
{
    qDebug();
    qDebug() << "AppEngine::UsersListRequest";
    qDebug() << user.s_Full_Name << " " << s_Password;

    if (!client.IsConnected())
        client.ConnectToServer();

    client.UsersListRequest();
}

void AppEngine::addUserRequest()
{
    qDebug();
    qDebug() << "AppEngine::addUserRequest";
    qDebug() << user.s_Full_Name << " " << s_Password;

    client.AddUserRequest();
}

void AppEngine::loadCurUserDataRequest()
{
    qDebug() << user.s_Full_Name;
    client.loadUserDataRequest(user.s_Full_Name);
}

void AppEngine::loadUserDataRequest(int id)
{
    client.loadUserDataRequest(id);
}

void AppEngine::loadRightsRequest()
{
    client.loadRightsRequest();
}

void AppEngine::addRightsRequest()
{
    client.addRightsRequest();
}

void AppEngine::removeUserRequest(int id)
{
    client.removeUserRequest(id);
}

void AppEngine::loadOfficesRequest()
{
    client.loadOfficesRequest();
}

void AppEngine::addOfficesRequest()
{
    client.addOfficeRequest();
}

void AppEngine::loadOfficeRequest(int id)
{
    client.loadOfficeRequest(id);
}

void AppEngine::loadRightRequest(int id)
{
    client.loadRightRequest(id);
}

void AppEngine::loadFilesRequest(QString path)
{
    client.loadFilesRequest(path);
}

void AppEngine::downloadFileRequest(QString path, QString name, User user)
{
    qDebug() << (path.isEmpty() ? name : path + '/' + name);
    qDebug() << user.i_ID << " " << user.s_Full_Name;
    client.downloadFileRequest(path.isEmpty() ? name : path + '/' + name, user.i_ID);
}

void AppEngine::uploadUserData(User user)
{
    client.uploadUserData(user);
}

void AppEngine::uploadRightData(Right right)
{
    client.uploadRightData(right);
}

void AppEngine::changeAccessLvl(QString path, QString name, int lvl)
{
    client.changeAccessLvlFileRequest(path.isEmpty() ? name : path + '/' + name, lvl);
}

User AppEngine::getCurUser()
{
    return user;
}

User AppEngine::sign(QString path, QString name)
{
    PDFDocHandle Doc = NULL;
    PDFLibHandle Lib = NULL;
}

void AppEngine::GetCurUser(User user)
{
    qDebug() << this->user.i_ID;
    qDebug() << user.i_ID << user.s_Full_Name;
    if (user.i_ID == this->user.i_ID || user.s_Full_Name == this->user.s_Full_Name)
        this->user = user;
}


void AppEngine::uploadFile(QString path)
{
    path = path.split("///")[1];
    QString name = path.section('/', -1, -1);
    qDebug() << path  << " " << name;
    QFile::copy(path, name);


    QFile file(name);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Error open file";
        qDebug() << file.errorString();
    }

    QTextStream in(&file);

    QString text = in.readAll();

    file.close();

    client.uploadFile(name, text);
}

void AppEngine::sendMessage(QString text, int id)
{
    qDebug();
    if (text.isEmpty())
        return;
    client.sendMessage(text, user.i_ID, id);
}

void AppEngine::uploadMessages(int id)
{
    client.uploadMessages(user.i_ID, id);
}

QString AppEngine::getIcon100UrlById(int id)
{
    static QHash<int, QString> icons = {
        {0, "qrc:/images/characters/finn-50.png"},
        {1, "qrc:/images/characters/ice-king-50.png"},
        {2, "qrc:/images/characters/jake-50.png"},
        {3, "qrc:/images/characters/lumpy-space-princess-50.png"},
        {4, "qrc:/images/characters/marceline-50.png"},
        {5, "qrc:/images/characters/princess-bubblegum-50.png"},
        {6, "qrc:/images/characters/ice-50.png"},
        {7, "qrc:/images/characters/ice-50.png"},
        {8, "qrc:/images/characters/gunter-50.png"}
    };

    return icons[id % icons.size()];
}

QString AppEngine::getIcon500UrlById(int id)
{
    static QHash<int, QString> icons = {
        {0, "qrc:/images/characters/gunter-100.png"}
    };

    return icons[id % icons.size()];
}
