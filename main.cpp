#include "widget.h"

#include <QApplication>

#include "UI/uiwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.init();
    w.show();

    return a.exec();
}
