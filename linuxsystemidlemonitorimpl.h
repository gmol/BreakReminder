#ifndef LINUXSYSTEMIDLEMONITORIMPL_H
#define LINUXSYSTEMIDLEMONITORIMPL_H

#include "systemidlemonitorimpl.h"

#include <X11/extensions/scrnsaver.h>

class LinuxSystemIdleMonitorImpl : public SystemIdleMonitorImpl
{
    Q_OBJECT

    friend class IdleSystemMonitor;

private:
    explicit LinuxSystemIdleMonitorImpl(int idleTime, int monitoringInterval, QObject *parent = 0);
    Display *dpy;
    
signals:
    
public slots:
    void monitor();
    
};

#endif // LINUXSYSTEMIDLEMONITORIMPL_H
