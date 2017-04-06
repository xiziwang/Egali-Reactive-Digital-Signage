#include "egalisignage.h"
#include <QApplication>
#include<iostream>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(resources);
    QApplication a(argc, argv);
    EgaliSignage signage;
    signage.show();
//    a.connect( &a, SIGNAL(lastWindowClosed()), &a, SLOT( quit()));
    int result = a.exec();
    return result;
}
