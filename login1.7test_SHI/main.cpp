#include "login.h"
#include "form.h"
#include <QApplication>
#include <qdesktopwidget.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login w;

    QDesktopWidget *desktop = QApplication::desktop();
    w.move((desktop->width()-w.width())/2,(desktop->height() - w.height())/2);
    w.show();
    return a.exec();
}
