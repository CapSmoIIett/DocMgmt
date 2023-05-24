
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


QTEST_MAIN(Tests)
#include "test.moc"
