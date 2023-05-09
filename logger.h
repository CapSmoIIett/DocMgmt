#pragma once

#include <QTextStream>

class Logger* _log = nullptr;



class Logger : QTextStream
{
    Logger();

    Logger(Logger const&) = delete;
    void operator=(Logger const&) = delete;

};
