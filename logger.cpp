#include "logger.h"


QFile* Logger::logFile = Q_NULLPTR;

bool Logger::isInit = false;

QHash<QtMsgType, QString> Logger::contextNames = {
    {QtMsgType::QtDebugMsg,		"Debug"},
    {QtMsgType::QtInfoMsg,		"Info"},
    {QtMsgType::QtWarningMsg,	"Warning"},
    {QtMsgType::QtCriticalMsg,	"Critical"},
    {QtMsgType::QtFatalMsg,		"Fatal"}
};

void Logger::Init()
{
    if (isInit)
        return;

    QDir dir("log");
    if (!dir.exists()){
        dir.mkdir(".");
    }

    logFile = new QFile("log\\" + QDateTime::currentDateTime().toString("yyyyMMdd") + ".log");
    logFile->open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text);

    qInstallMessageHandler(Logger::messageOutput);

    Logger::isInit = true;

}

void Logger::clean()
{
    if (logFile != Q_NULLPTR)
    {
        logFile->close();
        delete logFile;
    }
}

void Logger::messageOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    QString log = QString("%1 [%2] %3: %4 | %5 | %6\n")
        .arg(QDateTime::currentDateTime().toString("yyyy-mm-dd hh:mm:ss"))
        .arg(Logger::contextNames.value(type)[0])
        .arg(QString(context.file).section('/', -1))
        .arg(context.line)
        .arg(QString(context.function).section('(', -2, -2).section(' ', -1).section(':', -1))
        .arg(msg);

    Logger::logFile->write(log.toLocal8Bit());
    Logger::logFile->flush();

    QTextStream(stdout) << log;
}
