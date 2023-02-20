#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_docmgmt.h"

class DocMgmt : public QMainWindow
{
    Q_OBJECT

public:
    DocMgmt(QWidget *parent = nullptr);
    ~DocMgmt();

private:
    Ui::DocMgmtClass ui;
};
