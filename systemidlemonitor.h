#ifndef SYSTEMIDLEMONITOR_H
#define SYSTEMIDLEMONITOR_H

#include "isystemstatenotify.h"
#include "systemidlemonitorimpl.h"

//mytodo IdleSystemMonitor could be a sigleton
class IdleSystemMonitor : public ISystemStateNotify
{
    Q_OBJECT
public:
    explicit IdleSystemMonitor(int idleTime, int monitoringInterval, QObject *parent = 0);
    
signals:
    
public slots:
private:
    SystemIdleMonitorImpl *mImpl;
    
};

#endif // SYSTEMIDLEMONITOR_H
