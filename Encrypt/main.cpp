#include "encrypt.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Encrypt w;

    w.show();

    return a.exec();
}

