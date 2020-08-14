#include "RLAS.h"
#include <QtWidgets/QApplication>
#include <QtGui>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("Windows-1251"));
    RLAS w;
    w.show();
    return a.exec();
}
