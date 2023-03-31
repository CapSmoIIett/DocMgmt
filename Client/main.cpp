#include <QGuiApplication>
#include <QQmlApplicationEngine>


#include "header.h"
#include "client.h"

void test::hello()
{
    Client cl;
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/DocMgmtQt/main.qml"_qs);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    test t;
    QObject *qml = engine.rootObjects()[0];

    QObject::connect(qml, SIGNAL(hello()),
                     &t, SLOT(hello()));

    QObject* qtquick2Themes = engine.rootObjects()[0]->findChild<QObject*>("qtquick2Themes");
    //qtquick2Themes->setProperty("text", qgetenv("QT_QUICK_CONTROLS_STYLE"));
    //qtquick2Themes->setProperty("text", qgetenv("Default"));
    /*
        Default
        Fusion
        Imagine
        Material
        Universal 
    */

    return app.exec();
}
