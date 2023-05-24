
//#include <gtest/gtest.h>

//#include <QTest>
//#include <QObject>

//#include "../Client/client.h"
//#include "../Server/server.h"
//#include "../Client/appengine.h"

#include <QObject>
#include <QTest>


class Tests : public QObject
{
    Q_OBJECT
private slots:
    void simpl();
};

void Tests::simpl()
{
    QVERIFY(true);
}



QTEST_MAIN(Tests)
#include "test.moc"

/*
    ../Client/header.h
    ../Client/client.cpp
    ../Client/client.h
    ../Client/qml.qrc
    ../Client/personalmodel.cpp
    ../Client/personalmodel.h
    ../Client/appengine.cpp
    ../Client/appengine.h
    ../Client/rightsmodel.cpp
    ../Client/rightsmodel.h
    ../Client/officemodel.cpp
    ../Client/officemodel.h
    ../Client/userpage.cpp
    ../Client/userpage.h
    ../Client/officepage.cpp
    ../Client/officepage.h
    ../Client/rightpage.cpp
    ../Client/rightpage.h
    ../Client/filesmodel.cpp
    ../Client/filesmodel.h
    ../Client/messenger.h
    ../Client/messenger.cpp
    ../Client/calendar.cpp
    ../Client/calendar.h
    ../Client/images.qrc


    ../encrypter.cpp
    ../encrypter.h

    ../logger.h
    ../logger.cpp

    ../messages.h
    ../datastructures.h
 */

/*
TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(SignInTest, SignInTest)
{
    //AppEngine app;
    Client client;
    Server server;
    bool isVerified = false;

    QTimer timer;
    QEventLoop loop;

    client.ConnectToServer();

    connect(&client, &Client::onVerified, &loop, &QEventLoop::quit );
    connect( &timer, &QTimer::timeout, &loop, &QEventLoop::quit );
    connect(&client, &Client::onVerified, this, [this, &isVerified](bool result) {  isVerified = result; });

    client.ConnectToServer();

    client.VerifyRequest("supervisor", "1111");

  //Server server;


  //connect(&client, &Client::onVerified, this, [this](bool result) { });

  EXPECT_TRUE(true);
}
/*int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}*/
