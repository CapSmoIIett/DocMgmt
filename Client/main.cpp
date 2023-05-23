#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlProperty>
#include <QIcon>


#include "header.h"
#include "client.h"

#include "appengine.h"
#include "personalmodel.h"
#include "rightsmodel.h"
#include "officemodel.h"
#include "filesmodel.h"
#include "userpage.h"
#include "officepage.h"
#include "rightpage.h"
#include "messenger.h"
#include "calendar.h"

#include "../logger.h"


int main(int argc, char *argv[])
{
    qputenv("QT_QUICK_CONTROLS_STYLE", QByteArray("Material"));
    qputenv("QT_QUICK_CONTROLS_MATERIAL_THEME", QByteArray("Light"));

    QGuiApplication app(argc, argv);

    //app.setWindowIcon(QIcon("qrc:/images/fox_icon.png"));
    app.setWindowIcon(QIcon("fox_icon.ico"));
    //'qrc:/images/baseline-more_vert-24px.svg'

    //qmlRegisterType<PersonalTableModel>("PersonalModel", 1, 0, "PersonalModel");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/qml/main.qml"_qs);

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

    OfficeTableModel otable(&appEngine);
    engine.rootContext()->setContextProperty("officeTableModel", &otable);

    FilesTableModel ftable(&appEngine);
    engine.rootContext()->setContextProperty("filesTableModel", &ftable);

    UserPage upage(&appEngine);
    engine.rootContext()->setContextProperty("userPage", &upage);

    OfficePage opage(&appEngine);
    engine.rootContext()->setContextProperty("officePage", &opage);

    RightPage rpage(&appEngine);
    engine.rootContext()->setContextProperty("rightPage", &rpage);

    Messenger msger(&appEngine);
    engine.rootContext()->setContextProperty("messenger", &msger);

    Calendar calendar(&appEngine);
    engine.rootContext()->setContextProperty("calendar", &calendar);

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
