#include <QApplication>
#include "serialmonitor.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    SerialMonitor s;
    s.show();

    return app.exec();
}
