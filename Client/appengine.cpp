#include "appengine.h"

#include <QHash>

//#include "VersyPDF.h"
//#include "../versypdf/VersyPDF.h"


AppEngine::AppEngine(QObject* parent) :
    QObject(parent),
    s_IP("127.0.0.1")
{
    Logger::Init();

    connect(&this->client, &Client::onVerified, this, [this](bool result) { qDebug() << "call"; emit this->verified(result); });
    connect(&this->client, &Client::onGetUserData, this, &AppEngine::GetCurUser);
    connect(&this->client, &Client::onWarning, this, [this](QString text){ emit this->onWarnign(text); });

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

QString AppEngine::getIcon50UrlById(int id)
{
    static QHash<int, QString> icons = {
        {0, "qrc:/images/characters/finn-50.png"},
        {1, "qrc:/images/characters/ice-king-50.png"},
        {2, "qrc:/images/characters/jake-50.png"},
        {3, "qrc:/images/characters/lumpy-space-princess-50.png"},
        {4, "qrc:/images/characters/marceline-50.png"},
        {5, "qrc:/images/characters/princess-bubblegum-50.png"},
        {6, "qrc:/images/characters/gunter-50.png"}
    };

    return icons[id % icons.size()];
}

QString AppEngine::getIcon100UrlById(int id)
{
    static QHash<int, QString> icons = {
        {0, "qrc:/images/characters/finn-100.png"},
        {1, "qrc:/images/characters/ice-king-100.png"},
        {2, "qrc:/images/characters/jake-100.png"},
        {3, "qrc:/images/characters/lumpy-space-princess-100.png"},
        {4, "qrc:/images/characters/marceline-100.png"},
        {5, "qrc:/images/characters/princess-bubblegum-100.png"},
        {6, "qrc:/images/characters/gunter-100.png"}
    };

    return icons[id % icons.size()];

}
/*
std::string privateKey ="-----BEGIN RSA PRIVATE KEY-----\n"\
"MIIEowIBAAKCAQEAy8Dbv8prpJ/0kKhlGeJYozo2t60EG8L0561g13R29LvMR5hy\n"\
"vGZlGJpmn65+A4xHXInJYiPuKzrKUnApeLZ+vw1HocOAZtWK0z3r26uA8kQYOKX9\n"\
"Qt/DbCdvsF9wF8gRK0ptx9M6R13NvBxvVQApfc9jB9nTzphOgM4JiEYvlV8FLhg9\n"\
"yZovMYd6Wwf3aoXK891VQxTr/kQYoq1Yp+68i6T4nNq7NWC+UNVjQHxNQMQMzU6l\n"\
"WCX8zyg3yH88OAQkUXIXKfQ+NkvYQ1cxaMoVPpY72+eVthKzpMeyHkBn7ciumk5q\n"\
"gLTEJAfWZpe4f4eFZj/Rc8Y8Jj2IS5kVPjUywQIDAQABAoIBADhg1u1Mv1hAAlX8\n"\
"omz1Gn2f4AAW2aos2cM5UDCNw1SYmj+9SRIkaxjRsE/C4o9sw1oxrg1/z6kajV0e\n"\
"N/t008FdlVKHXAIYWF93JMoVvIpMmT8jft6AN/y3NMpivgt2inmmEJZYNioFJKZG\n"\
"X+/vKYvsVISZm2fw8NfnKvAQK55yu+GRWBZGOeS9K+LbYvOwcrjKhHz66m4bedKd\n"\
"gVAix6NE5iwmjNXktSQlJMCjbtdNXg/xo1/G4kG2p/MO1HLcKfe1N5FgBiXj3Qjl\n"\
"vgvjJZkh1as2KTgaPOBqZaP03738VnYg23ISyvfT/teArVGtxrmFP7939EvJFKpF\n"\
"1wTxuDkCgYEA7t0DR37zt+dEJy+5vm7zSmN97VenwQJFWMiulkHGa0yU3lLasxxu\n"\
"m0oUtndIjenIvSx6t3Y+agK2F3EPbb0AZ5wZ1p1IXs4vktgeQwSSBdqcM8LZFDvZ\n"\
"uPboQnJoRdIkd62XnP5ekIEIBAfOp8v2wFpSfE7nNH2u4CpAXNSF9HsCgYEA2l8D\n"\
"JrDE5m9Kkn+J4l+AdGfeBL1igPF3DnuPoV67BpgiaAgI4h25UJzXiDKKoa706S0D\n"\
"4XB74zOLX11MaGPMIdhlG+SgeQfNoC5lE4ZWXNyESJH1SVgRGT9nBC2vtL6bxCVV\n"\
"WBkTeC5D6c/QXcai6yw6OYyNNdp0uznKURe1xvMCgYBVYYcEjWqMuAvyferFGV+5\n"\
"nWqr5gM+yJMFM2bEqupD/HHSLoeiMm2O8KIKvwSeRYzNohKTdZ7FwgZYxr8fGMoG\n"\
"PxQ1VK9DxCvZL4tRpVaU5Rmknud9hg9DQG6xIbgIDR+f79sb8QjYWmcFGc1SyWOA\n"\
"SkjlykZ2yt4xnqi3BfiD9QKBgGqLgRYXmXp1QoVIBRaWUi55nzHg1XbkWZqPXvz1\n"\
"I3uMLv1jLjJlHk3euKqTPmC05HoApKwSHeA0/gOBmg404xyAYJTDcCidTg6hlF96\n"\
"ZBja3xApZuxqM62F6dV4FQqzFX0WWhWp5n301N33r0qR6FumMKJzmVJ1TA8tmzEF\n"\
"yINRAoGBAJqioYs8rK6eXzA8ywYLjqTLu/yQSLBn/4ta36K8DyCoLNlNxSuox+A5\n"\
"w6z2vEfRVQDq4Hm4vBzjdi3QfYLNkTiTqLcvgWZ+eX44ogXtdTDO7c+GeMKWz4XX\n"\
"uJSUVL5+CVjKLjZEJ6Qc2WZLl94xSwL71E41H4YciVnSCQxVc4Jw\n"\
"-----END RSA PRIVATE KEY-----\n\0";

std::string publicKey ="-----BEGIN PUBLIC KEY-----\n"\
"MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAy8Dbv8prpJ/0kKhlGeJY\n"\
"ozo2t60EG8L0561g13R29LvMR5hyvGZlGJpmn65+A4xHXInJYiPuKzrKUnApeLZ+\n"\
"vw1HocOAZtWK0z3r26uA8kQYOKX9Qt/DbCdvsF9wF8gRK0ptx9M6R13NvBxvVQAp\n"\
"fc9jB9nTzphOgM4JiEYvlV8FLhg9yZovMYd6Wwf3aoXK891VQxTr/kQYoq1Yp+68\n"\
"i6T4nNq7NWC+UNVjQHxNQMQMzU6lWCX8zyg3yH88OAQkUXIXKfQ+NkvYQ1cxaMoV\n"\
"PpY72+eVthKzpMeyHkBn7ciumk5qgLTEJAfWZpe4f4eFZj/Rc8Y8Jj2IS5kVPjUy\n"\
"wQIDAQAB\n"\
"-----END PUBLIC KEY-----\n";

RSA* createPrivateRSA(std::string key) {
  RSA *rsa = NULL;
  const char* c_string = key.c_str();
  BIO * keybio = BIO_new_mem_buf((void*)c_string, -1);
  if (keybio==NULL) {
      return 0;
  }
  rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa,NULL, NULL);
  return rsa;
}

RSA* createPublicRSA(std::string key) {
  RSA *rsa = NULL;
  BIO *keybio;
  const char* c_string = key.c_str();
  keybio = BIO_new_mem_buf((void*)c_string, -1);
  if (keybio==NULL) {
      return 0;
  }
  rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa,NULL, NULL);
  return rsa;
}

bool RSASign( RSA* rsa,
              const unsigned char* Msg,
              size_t MsgLen,
              unsigned char** EncMsg,
              size_t* MsgLenEnc) {
  EVP_MD_CTX* m_RSASignCtx = EVP_MD_CTX_create();
  EVP_PKEY* priKey  = EVP_PKEY_new();
  EVP_PKEY_assign_RSA(priKey, rsa);
  if (EVP_DigestSignInit(m_RSASignCtx,NULL, EVP_sha256(), NULL,priKey)<=0) {
      return false;
  }
  //if (EVP_DigestSignUpdate(m_RSASignCtx, Msg, MsgLen) <= 0) {
      //return false;
  //}
  if (EVP_DigestSignFinal(m_RSASignCtx, NULL, MsgLenEnc) <=0) {
      return false;
  }
  *EncMsg = (unsigned char*)malloc(*MsgLenEnc);
  if (EVP_DigestSignFinal(m_RSASignCtx, *EncMsg, MsgLenEnc) <= 0) {
      return false;
  }
  EVP_MD_CTX_free(m_RSASignCtx);
  return true;
}

bool RSAVerifySignature( RSA* rsa,
                         unsigned char* MsgHash,
                         size_t MsgHashLen,
                         const char* Msg,
                         size_t MsgLen,
                         bool* Authentic) {
  *Authentic = false;
  EVP_PKEY* pubKey  = EVP_PKEY_new();
  EVP_PKEY_assign_RSA(pubKey, rsa);
  EVP_MD_CTX* m_RSAVerifyCtx = EVP_MD_CTX_create();

  if (EVP_DigestVerifyInit(m_RSAVerifyCtx,NULL, EVP_sha256(),NULL,pubKey)<=0) {
    return false;
  }
  //if (EVP_DigestVerifyUpdate(m_RSAVerifyCtx, Msg, MsgLen) <= 0) {
    //return false;
  //}
  int AuthStatus = EVP_DigestVerifyFinal(m_RSAVerifyCtx, MsgHash, MsgHashLen);
  if (AuthStatus==1) {
    *Authentic = true;
    EVP_MD_CTX_free(m_RSAVerifyCtx);
    return true;
  } else if(AuthStatus==0){
    *Authentic = false;
    EVP_MD_CTX_free(m_RSAVerifyCtx);
    return true;
  } else{
    *Authentic = false;
    EVP_MD_CTX_free(m_RSAVerifyCtx);
    return false;
  }
}

void Base64Encode( const unsigned char* buffer,
                   size_t length,
                   char** base64Text) {
  BIO *bio, *b64;
  BUF_MEM *bufferPtr;

  b64 = BIO_new(BIO_f_base64());
  bio = BIO_new(BIO_s_mem());
  bio = BIO_push(b64, bio);

  BIO_write(bio, buffer, length);
  BIO_flush(bio);
  BIO_get_mem_ptr(bio, &bufferPtr);
  BIO_set_close(bio, BIO_NOCLOSE);
  BIO_free_all(bio);

  *base64Text=(*bufferPtr).data;
}

size_t calcDecodeLength(const char* b64input) {
  size_t len = strlen(b64input), padding = 0;

  if (b64input[len-1] == '=' && b64input[len-2] == '=') //last two chars are =
    padding = 2;
  else if (b64input[len-1] == '=') //last char is =
    padding = 1;
  return (len*3)/4 - padding;
}

void Base64Decode(const char* b64message, unsigned char** buffer, size_t* length) {
  BIO *bio, *b64;

  int decodeLen = calcDecodeLength(b64message);
  *buffer = (unsigned char*)malloc(decodeLen + 1);
  (*buffer)[decodeLen] = '\0';

  bio = BIO_new_mem_buf(b64message, -1);
  b64 = BIO_new(BIO_f_base64());
  bio = BIO_push(b64, bio);

  *length = BIO_read(bio, *buffer, strlen(b64message));
  BIO_free_all(bio);
}

char* signMessage(std::string privateKey, std::string plainText) {
  RSA* privateRSA = createPrivateRSA(privateKey);
  unsigned char* encMessage;
  char* base64Text;
  size_t encMessageLength;
  RSASign(privateRSA, (unsigned char*) plainText.c_str(), plainText.length(), &encMessage, &encMessageLength);
  Base64Encode(encMessage, encMessageLength, &base64Text);
  free(encMessage);
  return base64Text;
}

bool verifySignature(std::string publicKey, std::string plainText, char* signatureBase64) {
  RSA* publicRSA = createPublicRSA(publicKey);
  unsigned char* encMessage;
  size_t encMessageLength;
  bool authentic;
  Base64Decode(signatureBase64, &encMessage, &encMessageLength);
  bool result = RSAVerifySignature(publicRSA, encMessage, encMessageLength, plainText.c_str(), plainText.length(), &authentic);
  return result & authentic;
}


bool AppEngine::sign(QString path, QString name)
{
   /* std::unique_ptr<X509, decltype(&::X509_free)> certificate(X509_new(), ::X509_free);
    if (certificate == nullptr) {
        std::cerr << "Failed to create certificate" << std::endl;
        return -1;
    }

    const uint32_t serialNum = 20;
    bool res = setSerialNumber(certificate.get(), serialNum);
    if (!res) {
        std::cerr << "Failed to setSerialNumber" << std::endl;
        return -1;
    }

    const long ver = 0x0; // version 1
    res = setVersion(certificate.get(), ver);
    if (!res) {
        std::cerr << "Failed to setVersion" << std::endl;
        return -1;
    }

    static constexpr const char* key = "CN";
    static constexpr const char* value = "Common Name";
    res = updateSubjectName(certificate.get(), key, value);
    if (!res) {
        std::cerr << "Failed to updateSubjectName" << std::endl;
        return -1;
    }

    auto date = QDate::currentDate();
    const uint32_t y = date.year();
    const uint32_t m = date.month();
    const uint32_t d = date.day();
    const int32_t offset_days = 0;
    res = setNotAfter(certificate.get(), y, m, d, offset_days);
    if (!res) {
        std::cerr << "Failed to setNotAfter" << std::endl;
        return -1;
    }

    res = setNotBefore(certificate.get(), y, m, d, offset_days);
    if (!res) {
        std::cerr << "Failed to setNotBefore" << std::endl;
        return -1;
    }

    const int32_t bits = 2048;
    std::unique_ptr<EVP_PKEY, decltype(&::EVP_PKEY_free)> keyPair = generateKeyPair(bits);
    res = setPublicKey(certificate.get(), keyPair.get());
    if (!res) {
        std::cerr << "Failed to setPublicKey" << std::endl;
        return -1;
    }

    const int nid = NID_basic_constraints;
    static const char* extensionValue = "critical,CA:TRUE";

    /*
    res = addStandardExtension(certificate.get(), nullptr, nid, extensionValue);
    if (!res) {
        std::cerr << "Failed to addStandardExtension" << std::endl;
        return -1;
    }

    res = addCustomExtension(certificate.get(), "1.2.3", "myvalue", false);
    if (!res) {
        std::cerr << "Failed to addCustomExtension" << std::endl;
        return -1;
    }
    *//*

    res = signCert(certificate.get(), keyPair.get(), EVP_sha256());
    if (!res) {
        std::cerr << "Failed to signCert" << std::endl;
        return -1;
    }

    std::unique_ptr<X509, decltype(&::X509_free)> duplicate(X509_dup(certificate.get()), ::X509_free);
    if (duplicate == nullptr) {
        std::cerr << "Failed to duplicate certificate" << std::endl;
        return -1;
    }

    res = setIssuer(certificate.get(), duplicate.get());
    if (!res) {
        std::cerr << "Failed to setIssuer" << std::endl;
        return -1;
    }

    res = addIssuerInfo(certificate.get(), key, value);
    if (!res) {
        std::cerr << "Failed to addIssuerInfo" << std::endl;
        return -1;
    }

    res = signCert(certificate.get(), keyPair.get(), EVP_sha256());
    if (!res) {
        std::cerr << "Failed to signCert" << std::endl;
        return -1;
    }

    static const std::string filename = "certificate.pem";
    res = saveCertToPemFile(certificate.get(), filename);
    if (!res) {
        std::cerr << "Failed to saveCertToPemFile" << std::endl;
        return -1;
    }
//*/
//}

void AppEngine::loadCalendarRequest(int month, int year)
{
    client.loadCalendarRequest(month, year);
}

void AppEngine::setHolidayRequest(QDate date, QString name)
{
    client.setHolidayRequest(date, name);
}

/*
void AppEngine::GenerateCertificate()
{
    std::unique_ptr<X509, decltype(&::X509_free)> certificate(X509_new(), ::X509_free);
    if (certificate == nullptr)
    {
        qWarning() << "Failed to create certificate";
        return;
    }
}
bool AppEngine::setSerialNumber(X509* cert, uint32_t bytes)
{
    bool result = false;
    ASN1_STRING* serialNumber = X509_get_serialNumber(cert);

    if (serialNumber != nullptr && bytes != 0)
    {
        std::vector<unsigned char> serial(bytes);
        RAND_bytes(serial.data(), static_cast<int>(serial.size()));

        if (ASN1_STRING_set(serialNumber, serial.data(), static_cast<int>(serial.size())) == 1)
        {
            result = true;
        }
    }
    return result;
}

bool AppEngine::setVersion(X509* cert, long version)
{
    return X509_set_version(cert, version) == 1;
}

bool AppEngine::updateSubjectName(X509* cert, const char* key, const char* value)
{
    bool result = false;
    X509_NAME* subjectName = X509_get_subject_name(cert);

    if (subjectName != nullptr)
    {
        const int res = X509_NAME_add_entry_by_txt(subjectName, key, MBSTRING_ASC, (unsigned char*)value, -1, -1, 0);
        result = res == 1;
    }
    return result;
}

bool AppEngine::setNotAfter(X509* cert, uint32_t y, uint32_t m, uint32_t d, int32_t offset_days)
{
    struct tm base;
    memset(&base, 0, sizeof(base));
    base.tm_year = y - 1900;
    base.tm_mon = m - 1;
    base.tm_mday = d;
    time_t tm = mktime(&base);

    bool result = false;
    ASN1_STRING* notAfter = X509_getm_notAfter(cert);
    if (notAfter != nullptr)
    {
        X509_time_adj(notAfter, 86400L * offset_days, &tm);
        result = true;
    }
    return result;
}

bool AppEngine::setNotBefore(X509* cert, uint32_t y, uint32_t m, uint32_t d, int32_t offset_days)
{
    struct tm base;
    memset(&base, 0, sizeof(base));
    base.tm_year = y - 1900;
    base.tm_mon = m - 1;
    base.tm_mday = d;
    time_t tm = mktime(&base);

    bool result = false;
    ASN1_STRING* notBefore = X509_getm_notBefore(cert);
    if (notBefore != nullptr)
    {
        X509_time_adj(notBefore, 86400L * offset_days, &tm);
        result = true;
    }
    return result;
}

bool AppEngine::setIssuer(X509* cert, X509* issuer)
{
    bool result = false;
    X509_NAME* subjectName = X509_get_subject_name(issuer);
    if (subjectName != nullptr)
    {
        result = X509_set_issuer_name(cert, subjectName) == 1;
    }
    return result;
}

bool AppEngine::addIssuerInfo(X509* cert, const char* key, const char* value)
{
    bool result = false;
    X509_NAME* issuerName = X509_get_issuer_name(cert);

    if (issuerName != nullptr)
    {
        result = X509_NAME_add_entry_by_txt(issuerName, key, MBSTRING_ASC, (unsigned char*)value, -1, -1, 0) == 1;
    }
    return result;
}

std::unique_ptr<EVP_PKEY, decltype(&::EVP_PKEY_free)> AppEngine::generateKeyPair(int32_t bits)
{
    std::unique_ptr<EVP_PKEY, decltype(&::EVP_PKEY_free)> key(EVP_RSA_gen(bits), ::EVP_PKEY_free);
    return std::move(key);
}

bool AppEngine::setPublicKey(X509* cert, EVP_PKEY* key)
{
    return X509_set_pubkey(cert, key) == 1;
}

bool AppEngine::signCert(X509* cert, EVP_PKEY* key, const EVP_MD* algo)
{
    return X509_sign(cert, key, algo) != 0;
}

bool AppEngine::saveCertToPemFile(X509* cert, const std::string& file)
{
    bool result = false;
    std::unique_ptr<BIO, decltype(&::BIO_free)> bio(BIO_new(BIO_s_file()), ::BIO_free);

    if (bio != nullptr)
    {
        if (BIO_write_filename(bio.get(), const_cast<char*>(file.c_str())) > 0)
        {
            result = PEM_write_bio_X509(bio.get(), cert) == 1;
        }
    }

    return result;
}




    /*char * fileName = (path + "/" + name).toLocal8Bit().data();
    PDFDocHandle Doc = NULL;
    PDFLibHandle Lib = NULL;
    bool result = false;

    Lib = InitPDFLibrary(NULL, NULL);

    if (Lib)
    {
        qWarning() << "Init lib error";
        return false;
    }


    PDFTRY(Lib)
    {
        qDebug() << fileName;
        Doc = PDFDocLoadFromFile(Lib, fileName);
    }
    PDFEXCEPT(Lib)
    { }
    PDFTRYEND();

    if (!Doc)
    {
        qWarning() << "Doc not open";
        return false;
    }

    PDFTRY(Lib)
    {
        PDFDocAppendSignatureFromBuffer(Doc, buffer, )
    }
    PDFEXCEPT(Lib)
    { }
    PDFTRYEND();

    if (PPGetLastError(Lib))
    {
        qWarning() << PPGetLastError(Lib);
        return false;
    }

    ppInt32 size = 0;

    PDFTRY(Lib)
    {
        void* bytes = PDFDocSaveToBuffer(Doc, &size);

        result = true;
    }
    PDFEXCEPT(Lib)
    { }
    PDFTRYEND();

    PDFDocClose(Doc);

    DonePDFLibrary(&Lib);
    Lib = NULL;

    return result;*/
