#include "tray.h"
#include <QEvent>

Tray::Tray(int interval, int postponeTime, QObject *parent) :
    QObject(parent), timer(interval, postponeTime)
{
    trayIcon.setIcon(QIcon("://tray"));
    postponeAction = new QAction(QIcon("://later3"),"&Later", &trayIcon);
    postponeAction->setIconVisibleInMenu(true);

    soonerAction = new QAction(QIcon("://sooner"),"&Sooner", &trayIcon);
    soonerAction->setIconVisibleInMenu(true);

    quitAction = new QAction(QIcon("://quit"), "&Quit", &trayIcon);
    quitAction->setIconVisibleInMenu(true);
    restartAction = new QAction(QIcon("://restart"), "&Restart", &trayIcon);
    restartAction->setIconVisibleInMenu(true);
    trayIconMenu = new QMenu();
    trayIconMenu->addAction(restartAction);
    trayIconMenu->addAction(postponeAction);
    trayIconMenu->addAction(soonerAction);
    trayIconMenu->addAction(quitAction);
    trayIcon.setContextMenu(trayIconMenu);

    QObject::connect(quitAction, SIGNAL(triggered()), &timer, SLOT(stop()));
    QObject::connect(quitAction, SIGNAL(triggered()), this, SIGNAL(quit()));
    QObject::connect(postponeAction, SIGNAL(triggered()), &timer, SLOT(postpone()));
    QObject::connect(soonerAction, SIGNAL(triggered()), &timer, SLOT(sooner()));
    QObject::connect(restartAction, SIGNAL(triggered()), &timer, SLOT(restart()));
    trayIcon.installEventFilter(this);
    trayIcon.show();
    timer.start();
}

bool Tray::eventFilter(QObject *, QEvent *e) {
    if (e->type() == QEvent::ToolTip) {
        QString toolTip = QString("%1 minutes to the next break").arg(timer.remainingTime() / 1000 /60);
        trayIcon.setToolTip(toolTip);
    }
    return QObject::event(e);
}
