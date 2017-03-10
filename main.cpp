#include "dialog.h"
#include <QApplication>
#include"servers.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();
   // servers x;
   // x.show();

    return a.exec();
}
