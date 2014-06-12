#ifndef SYSTEMIDLEMONITOR_H
#define SYSTEMIDLEMONITOR_H

#include "isystemstatenotify.h"
#include "systemidlemonitorimpl.h"

//mytodo IdleSystemMonitor should be a sigleton
//mytodo change the name from SystemIdleMonitor for IdleSystemMonitor
class SystemIdleMonitor : public ISystemStateNotify
{
    Q_OBJECT
public:
    explicit SystemIdleMonitor(QObject *parent = 0);
    
signals:
    
public slots:
private:
    SystemIdleMonitorImpl *mImpl;
    
};

#endif // SYSTEMIDLEMONITOR_H
