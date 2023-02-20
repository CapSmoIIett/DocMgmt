#include "docmgmt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DocMgmt w;
    w.show();
    return a.exec();
}
