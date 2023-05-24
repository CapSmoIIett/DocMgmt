
// Enabling this section disables all debug output from non-Qt code.
#define QT_NO_DEBUG_OUTPUT

#include <QObject>
#include <QTest>
#include <QSignalSpy>
#include <QTimer>
#include <QEventLoop>
#include <QtCore/QDebug>
#include <QDir>
#include <QDirIterator>

#include "../Client/client.h"

void noMessageOutput(QtMsgType, const QMessageLogContext&, const QString&)
{}

class Tests : public QObject
{
    Q_OBJECT
private slots:
    void simpl();

    void initTestCase();

    void verify();
    void verifyFalseLogin();
    void verifyFalsePassword();

    void loadFile();
    void loadFileFalseUser();

    void uploadFile();
    void uploadFileFalseUser();

    void deleteUser();
    void deleteUserFalseRights();

    void uploadUserDataOffice();
    void uploadUserDataName();


private:
    Client* cl;

};

void Tests::simpl()
{
    QVERIFY(true);
}

void Tests::initTestCase()
{
    qInstallMessageHandler(noMessageOutput);

    cl = new Client;
    cl->ConnectToServer();

    QVERIFY(cl->IsConnected());

    qApp->processEvents();
}

void Tests::verify()
{
    QTimer timer;
    timer.setSingleShot(true);
    QEventLoop loop;
    bool result = false;

    connect( cl, &Client::onVerified, this, [this, &loop, &result] (bool res) { result = res; emit loop.quit() ;} );
    connect( &timer, &QTimer::timeout, &loop, &QEventLoop::quit );
    timer.start(1000);

    cl->VerifyRequest("supervisor", "1111");

    loop.exec();

    QVERIFY(timer.isActive());
    QVERIFY(result);
}

void Tests::verifyFalseLogin()
{
    QTimer timer;
    timer.setSingleShot(true);
    QEventLoop loop;
    bool result = false;

    connect( cl, &Client::onVerified, this, [this, &loop, &result] (bool res) { result = res; emit loop.quit() ;} );
    connect( &timer, &QTimer::timeout, &loop, &QEventLoop::quit );
    timer.start(1000);

    cl->VerifyRequest("", "1111");

    loop.exec();

    QVERIFY(timer.isActive());
    QVERIFY(!result);

}

void Tests::verifyFalsePassword()
{
    QTimer timer;
    timer.setSingleShot(true);
    QEventLoop loop;
    bool result = false;

    connect( cl, &Client::onVerified, this, [this, &loop, &result] (bool res) { result = res; emit loop.quit() ;} );
    connect( &timer, &QTimer::timeout, &loop, &QEventLoop::quit );
    timer.start(1000);

    cl->VerifyRequest("supervisor", "");

    loop.exec();

    QVERIFY(timer.isActive());
    QVERIFY(!result);
}

void Tests::loadFile()
{
    cl->VerifyRequest("supervisor", "1111");

    QTimer timer;
    timer.setSingleShot(true);
    QEventLoop loop;
    bool result = false;

    connect( cl, &Client::onWarning, this, [this, &loop] (QString text) { emit loop.quit() ;} );
    connect( &timer, &QTimer::timeout, &loop, &QEventLoop::quit );
    timer.start(1000);
    cl->downloadFileRequest("difficultname.txt", 0);

    loop.exec();

    QVERIFY(!timer.isActive());

    QDirIterator it(QDir::currentPath(), QDirIterator::Subdirectories);

    while (it.hasNext()) {
        QString filename = it.next();
        QFileInfo file(filename);

        if (file.isDir()) { // Check if it's a dir
            continue;
        }

        if (file.fileName().contains("difficultname.txt", Qt::CaseInsensitive))
        {
            result = true;
            break;
        }
    }


    QVERIFY(result);
}

void Tests::loadFileFalseUser()
{
    cl->VerifyRequest("user", "1111");

    QTimer timer;
    timer.setSingleShot(true);
    QEventLoop loop;
    bool result = false;

    connect( cl, &Client::onWarning, this, [this, &loop] (QString text) { emit loop.quit() ;} );
    connect( &timer, &QTimer::timeout, &loop, &QEventLoop::quit );
    timer.start(1000);
    cl->downloadFileRequest("difficultname.txt", 0);

    loop.exec();

    QVERIFY(!timer.isActive());

    QDirIterator it(QDir::currentPath(), QDirIterator::Subdirectories);

    while (it.hasNext()) {
        QString filename = it.next();
        QFileInfo file(filename);

        if (file.isDir()) { // Check if it's a dir
            continue;
        }

        if (file.fileName().contains("difficultname.txt", Qt::CaseInsensitive))
        {
            result = true;
            break;
        }
    }

    QVERIFY(result);
}

void Tests::uploadFile()
{
    cl->VerifyRequest("supervisor", "1111");

    QTimer timer;
    timer.setSingleShot(true);
    QEventLoop loop;
    bool result = false;

    connect( cl, &Client::onWarning, this, [this, &loop] (QString text) { emit loop.quit() ;} );
    connect( &timer, &QTimer::timeout, &loop, &QEventLoop::quit );
    timer.start(1000);

    cl->uploadFile("difficultname.txt");

    loop.exec();

    QVERIFY(!timer.isActive());

    QDirIterator it(QDir::currentPath(), QDirIterator::Subdirectories);

    while (it.hasNext()) {
        QString filename = it.next();
        QFileInfo file(filename);

        if (file.isDir()) { // Check if it's a dir
            continue;
        }

        if (file.fileName().contains("difficultname.txt", Qt::CaseInsensitive))
        {
            result = true;
            break;
        }
    }

    QVERIFY(result);
}

void Tests::uploadFileFalseUser()
{
    cl->VerifyRequest("user", "1111");

    QTimer timer;
    timer.setSingleShot(true);
    QEventLoop loop;
    bool result = false;

    connect( cl, &Client::onWarning, this, [this, &loop] (QString text) { emit loop.quit() ;} );
    connect( &timer, &QTimer::timeout, &loop, &QEventLoop::quit );
    timer.start(1000);

    cl->uploadFile("difficultname.txt");

    loop.exec();

    QVERIFY(!timer.isActive());

    QDirIterator it(QDir::currentPath(), QDirIterator::Subdirectories);

    while (it.hasNext()) {
        QString filename = it.next();
        QFileInfo file(filename);

        if (file.isDir()) { // Check if it's a dir
            continue;
        }

        if (file.fileName().contains("difficultname.txt", Qt::CaseInsensitive))
        {
            result = true;
            break;
        }
    }


    QVERIFY(result);
}

void Tests::deleteUser()
{
    cl->VerifyRequest("supervisor", "1111");

    QTimer timer;
    timer.setSingleShot(true);
    QEventLoop loop;

    connect( cl, &Client::onWarning, this, [this, &loop] (QString text) { emit loop.quit() ;} );
    connect( &timer, &QTimer::timeout, &loop, &QEventLoop::quit );
    timer.start(1000);

    cl->removeUserRequest(1);

    loop.exec();

    QVERIFY(timer.isActive());
}

void Tests::deleteUserFalseRights()
{
    cl->VerifyRequest("user", "1111");

    QTimer timer;
    timer.setSingleShot(true);
    QEventLoop loop;

    connect( cl, &Client::onWarning, this, [this, &loop] (QString text) { emit loop.quit() ;} );
    connect( &timer, &QTimer::timeout, &loop, &QEventLoop::quit );
    timer.start(1000);

    cl->removeUserRequest(1);

    loop.exec();

    QVERIFY(!timer.isActive());
}

void Tests::uploadUserDataOffice()
{
    QTimer timer;
    timer.setSingleShot(true);
    QEventLoop loop;
    bool result = false;

    connect( cl, &Client::onWarning, this, [this, &loop] (QString text) { emit loop.quit() ;} );
    connect( &timer, &QTimer::timeout, &loop, &QEventLoop::quit );
    timer.start(1000);

    User user;
    user.i_ID = 0;
    user.s_Full_Name = "supervisor";
    user.s_Office = "New Office";
    user.s_Right = "";

    cl->uploadUserData(user);

    loop.exec();

    QVERIFY(timer.isActive());
}


void Tests::uploadUserDataName()
{
    QTimer timer;
    timer.setSingleShot(true);
    QEventLoop loop;
    bool result = false;

    connect( cl, &Client::onWarning, this, [this, &loop] (QString text) { emit loop.quit() ;} );
    connect( &timer, &QTimer::timeout, &loop, &QEventLoop::quit );
    timer.start(1000);

    User user;
    user.i_ID = 0;
    user.s_Full_Name = "supersuper";
    user.s_Office = "";
    user.s_Right = "";

    cl->uploadUserData(user);

    loop.exec();

    QVERIFY(timer.isActive());
}


QTEST_MAIN(Tests)
#include "test.moc"
