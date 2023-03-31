#pragma once

#include <iostream>

#include "QObject"

class test : public QObject
{
    Q_OBJECT

public slots:
    void hello();
};
