#include "RLAS.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RLAS w;
    w.show();
    return a.exec();
}
