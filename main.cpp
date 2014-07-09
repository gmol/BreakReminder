#include <QApplication>
#include <QSystemTrayIcon>
#include <QMessageBox>
#include <QAction>
#include <QIcon>
#include <QMenu>
#include <QDebug>
#include "tray.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Systray"),
                              QObject::tr("I couldn't detect any system tray "
                                          "on this system."));
//        return 1;
    }

    QStringList args = a.arguments();
    for (int i = 0; i < args.size(); ++i) {
         qDebug() << "arg[" << i << "]=" << args.at(i);
    }

    // 60 min
    int interval = 60 * 60 * 1000;
    // 10 min
    int postponeTime = 10 * 60 * 1000;
    if (args.size() > 1 ) {
        QString intervalStr(args.at(1));
        int tmp = intervalStr.toInt();
        if (tmp > 0)
            interval = tmp;
    }
    if (args.size() > 2) {
        QString postponeTimeStr(args.at(2));
        int tmp = postponeTimeStr.toInt();
        if (tmp > 0)
            postponeTime = tmp;
    }

    QApplication::setQuitOnLastWindowClosed(false);

    Tray tray(interval, postponeTime);

    QObject::connect(&tray, SIGNAL(quit()), &a, SLOT(quit()));

    return a.exec();
}
