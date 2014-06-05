#ifndef TRAY_H
#define TRAY_H

#include <QObject>

#include <QSystemTrayIcon>
#include <QMessageBox>
#include <QAction>
#include <QIcon>
#include <QMenu>
#include <QDebug>
#include "traytimer.h"

class Tray : public QObject
{
    Q_OBJECT
public:
    explicit Tray(int interval, int postponeTime, QObject *parent = 0);

signals:
    void quit();

public slots:

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:
    QSystemTrayIcon trayIcon;
    QAction* postponeAction;
    QAction* restartAction;
    QAction* quitAction;
    QMenu* trayIconMenu;

    TrayTimer timer;

};

#endif // TRAY_H
