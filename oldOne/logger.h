#pragma once

#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QDateTime>
#include <QHash>


class Logger
{
public:
    static void Init();
    static void clean();

    static void messageOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg);

private:
    static QFile* logFile;
    static bool isInit;
    static QHash<QtMsgType, QString> contextNames;
};


/*
 * class Logger
{
public:
    //_Logger();

    //_Logger (_Logger const&) = delete;
    //void operator= (_Logger const&) = delete;

    static QTextStream operator()()
    {
        return QTextStream(stderr);
    };

    QFile file;
};
*/

/*
 * class Logger : QTextStream
{
    static unsigned int level;

    QString s_FunctionName;
public:
    QString GetTime();

    Logger(QString functionName)
    {
        s_FunctionName = functionName;
        QString text;
        text += QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zz000") + " [m] " + "\\ Begin: " + s_FunctionName + "\n";

        //for (int i = 0; i <= level) text << " \ ";

        QTextStream(stdout) << text;

        //return *this;
    }
    ~Logger()
    {
        QString text;
        text += QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zz000") + " [m] " + "/ End: " + s_FunctionName + "\n";
    }

    template<class T>
    Logger& operator<<(const T& t)
    {
        QTextStream(stdout) << t;

        return *this;
    }


};

/*_LoggerStream Logger()
{
    return _LoggerStream();

}
/*
    QFile file (p_dir->path() + '/' + name);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Error open file";
        qDebug() << file.errorString();
    }

    QTextStream in(&file);

    QString text = in.readAll();

    file.close();
*/
