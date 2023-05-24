#include "test_case.h"

#include <gtest/gtest.h>

#include <QObject>
#include <QSignalSpy>

#include "../Client/client.h"
#include "../Server/server.h"
#include "../Client/appengine.h"

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
