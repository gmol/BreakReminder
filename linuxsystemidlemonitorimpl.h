#ifndef LINUXSYSTEMIDLEMONITORIMPL_H
#define LINUXSYSTEMIDLEMONITORIMPL_H

#include "systemidlemonitorimpl.h"

class LinuxSystemIdleMonitorImpl : public SystemIdleMonitorImpl
{
    Q_OBJECT

    friend class SystemIdleMonitor;

private:
    explicit LinuxSystemIdleMonitorImpl(int idleTime, QObject *parent = 0);
    
signals:
    
public slots:
    void monitor();
    
};

#endif // LINUXSYSTEMIDLEMONITORIMPL_H
