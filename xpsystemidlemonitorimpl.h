#ifndef XPSYSTEMIDLEMONITORIMPL_H
#define XPSYSTEMIDLEMONITORIMPL_H

#include "systemidlemonitorimpl.h"

class XpSystemIdleMonitorImpl : public SystemIdleMonitorImpl
{
    Q_OBJECT

    friend class SystemIdleMonitor;

private:
    explicit XpSystemIdleMonitorImpl(int idleTime, QObject *parent = 0);
    
signals:
    
public slots:
    void monitor();

    
};

#endif // XPSYSTEMIDLEMONITORIMPL_H
