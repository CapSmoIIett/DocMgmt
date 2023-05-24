#pragma once

#include <QObject>
#include <QString>
#include <qqml.h>
#include <QFile>

//#include <cryptopp/cryptlib.h>
#include <openssl/x509v3.h>
#include <openssl/rand.h>
#include <openssl/pem.h>
#include <openssl/evp.h>
#include <iostream>
#include <openssl/aes.h>
#include <openssl/rsa.h>
#include <openssl/ssl.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <assert.h>

typedef evp_pkey_st EVP_PKEY;

#include <memory>

#include "client.h"

class AppEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userName READ userName WRITE setUserName)
    Q_PROPERTY(QString password READ password WRITE setPassword)
    Q_PROPERTY(QString office READ office WRITE setOffice)
    Q_PROPERTY(QString right READ right WRITE setRight)
    Q_PROPERTY(int id READ id WRITE setID)

    Q_PROPERTY(QString ip READ ip WRITE setIP NOTIFY onChangeIP)
    Q_PROPERTY(QString port READ port WRITE setPort NOTIFY onChangePort)

    QML_ELEMENT

public:
    explicit AppEngine(QObject *parent = nullptr);
    ~AppEngine();

    QString userName();
    void setUserName(const QString &userName);

    QString password();
    void setPassword(const QString &password);

    QString office();
    void setOffice(const QString &password);

    QString right();
    void setRight(const QString &password);

    int id();
    void setID(const int &ip);

    QString ip();
    void setIP(const QString &ip);

    QString port();
    void setPort(const QString &port);


    Client& GetClient();

    Q_INVOKABLE bool verify();
    Q_INVOKABLE void usersListRequest();
    Q_INVOKABLE void addUserRequest();

    Q_INVOKABLE void loadCurUserDataRequest();
    Q_INVOKABLE void loadUserDataRequest(int id);
    Q_INVOKABLE void loadRightsRequest();
    Q_INVOKABLE void addRightsRequest();
    Q_INVOKABLE void removeUserRequest(int id);
    Q_INVOKABLE void loadOfficesRequest();
    Q_INVOKABLE void addOfficesRequest();
    Q_INVOKABLE void loadOfficeRequest(int id);
    Q_INVOKABLE void loadRightRequest(int id);

    Q_INVOKABLE void loadFilesRequest(QString path);

    Q_INVOKABLE void downloadFileRequest(QString path, QString name, User user);
    Q_INVOKABLE void changeAccessLvl(QString path, QString name, int lvl);
    Q_INVOKABLE User getCurUser();

    Q_INVOKABLE bool sign(QString path, QString name);


    void uploadUserData(User user);
    void uploadRightData(Right right);

    Q_INVOKABLE void uploadFile(QString path);


    Q_INVOKABLE void sendMessage(QString text, int id);
    Q_INVOKABLE void uploadMessages(int id);

    Q_INVOKABLE QString getIcon50UrlById(int id);
    Q_INVOKABLE QString getIcon100UrlById(int id);

    Q_INVOKABLE void loadCalendarRequest(int month, int year);
    Q_INVOKABLE void setHolidayRequest(QDate date, QString name);

signals:
    void verified(bool result);
    void onChangeIP();
    void onChangePort();

public slots:
    void GetCurUser(User user);

private:
    /*void GenerateCertificate();
    bool setSerialNumber(X509* cert, uint32_t bytes);
    bool setVersion(X509* cert, long version);
    bool updateSubjectName(X509* cert, const char* key, const char* value);
    bool setNotAfter(X509* cert, uint32_t y, uint32_t m, uint32_t d, int32_t offset_days);
    bool setNotBefore(X509* cert, uint32_t y, uint32_t m, uint32_t d, int32_t offset_days);

    bool setIssuer(X509* cert, X509* issuer);
    bool addIssuerInfo(X509* cert, const char* key, const char* value);

    std::unique_ptr<EVP_PKEY, decltype(&::EVP_PKEY_free)> generateKeyPair(int32_t bits);
    bool setPublicKey(X509* cert, EVP_PKEY* key);
    bool signCert(X509* cert, EVP_PKEY* key, const EVP_MD* algo);
    bool saveCertToPemFile(X509* cert, const std::string& file);
*/


    Client client;

    User user;
    QString s_Password;
    QString s_IP;
    QString s_Port;

};

