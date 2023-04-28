#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlProperty>


#include "header.h"
#include "client.h"

#include "appengine.h"
#include "personalmodel.h"
#include "rightsmodel.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //qmlRegisterType<PersonalTableModel>("PersonalModel", 1, 0, "PersonalModel");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/DocMgmtQt/qml/main.qml"_qs);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    AppEngine appEngine;
    engine.rootContext()->setContextProperty("app", &appEngine);

    PersonalTableModel ptable(&appEngine);
    engine.rootContext()->setContextProperty("personalTableModel", &ptable);

    RightsTableModel rtable(&appEngine);
    engine.rootContext()->setContextProperty("rightsTableModel", &rtable);



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
