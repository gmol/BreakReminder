#include "tray.h"
#include <QEvent>

Tray::Tray(int interval, int postponeTime, QObject *parent) :
    QObject(parent), timer(interval, postponeTime)
{
    trayIcon.setIcon(QIcon("://tray"));
    laterAction = new QAction(QIcon("://later3"),"&Later", &trayIcon);
    laterAction->setIconVisibleInMenu(true);

    soonerAction = new QAction(QIcon("://sooner"),"&Sooner", &trayIcon);
    soonerAction->setIconVisibleInMenu(true);

    quitAction = new QAction(QIcon("://quit"), "&Quit", &trayIcon);
    quitAction->setIconVisibleInMenu(true);
    restartAction = new QAction(QIcon("://restart"), "&Restart", &trayIcon);
    restartAction->setIconVisibleInMenu(true);
    trayIconMenu = new QMenu();
    trayIconMenu->addAction(restartAction);
    trayIconMenu->addAction(laterAction);
    trayIconMenu->addAction(soonerAction);
    trayIconMenu->addAction(quitAction);
    trayIcon.setContextMenu(trayIconMenu);

    QObject::connect(quitAction, SIGNAL(triggered()), &timer, SLOT(stop()));
    QObject::connect(quitAction, SIGNAL(triggered()), this, SIGNAL(quit()));
    QObject::connect(laterAction, SIGNAL(triggered()), &timer, SLOT(later()));
    QObject::connect(soonerAction, SIGNAL(triggered()), &timer, SLOT(sooner()));
    QObject::connect(restartAction, SIGNAL(triggered()), &timer, SLOT(restart()));
    trayIcon.installEventFilter(this);
    trayIcon.show();
    timer.start();
}

bool Tray::eventFilter(QObject *, QEvent *e) {
    if (e->type() == QEvent::ToolTip) {
        QString toolTip("");
        if (timer.isWorkTime())
            toolTip = QString("%1 minutes to the next break").arg(timer.remainingTime() / 1000 /60);
        else
            toolTip = QString("%1 minutes till the end of the break").arg(TrayTimer::convertToString(timer.remainingTime(), TrayTimer::MINUTE));
        trayIcon.setToolTip(toolTip);
    }
    return QObject::event(e);
}
