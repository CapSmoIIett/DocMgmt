#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>


#include "header.h"
#include "client.h"
#include "database.h"
#include "model.h"
#include "appengine.h"

void test::hello()
{
    Client cl;
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/DocMgmtQt/main.qml"_qs);
    //const QUrl url(u"qrc:/DocMgmtQt/authenticationWindow.qml"_qs);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    AppEngine appEngine;
    //engine.rootContext()->setContextProperty(main);

    DataBase database;
    // Объявляем и инициализируем модель представления данных
    Model *model = new Model();
    /* Поскольку Мы отнаследовались от QSqlQueryModel, то
     * для выборки данных нам необходимо выполнить SQL-запрос,
     * в котором мы выберем все необходимы поля из нужной нам таблицы
     * */
    //model->setQuery("SELECT " TABLE_EMPLOYEE_NAME ", " TABLE_EMPLOYEE_OFFICE " FROM " TABLE_EMPLOYEE);
    model->setQuery("select full_name, office_id from employee");

    //engine.rootContext()->setContextProperty("myModel", model);

    //engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    //engine.load(QUrl(QStringLiteral("qrc:/DocMgmtQt/authenticationWindow.qml")));


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
