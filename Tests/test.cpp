
//#include <gtest/gtest.h>

//#include <QTest>
//#include <QObject>

//#include "../Client/client.h"
//#include "../Server/server.h"
//#include "../Client/appengine.h"

#include <QObject>
#include <QTest>
#include <QSignalSpy>
#include <QTimer>
#include <QEventLoop>

#include "../Client/client.h"

class Tests : public QObject
{
    Q_OBJECT
private slots:
    void simpl();

    void initTestCase();
    void verify();

private:
    Client* cl;

};

void Tests::simpl()
{
    QVERIFY(true);
}

void Tests::initTestCase()
{
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


QTEST_MAIN(Tests)
#include "test.moc"
