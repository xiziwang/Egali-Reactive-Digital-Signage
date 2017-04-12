#include "egalisignage.h"
#include <QApplication>
#include<iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EgaliSignage signage;
    signage.show();
    int result = a.exec();
    return result;
}
