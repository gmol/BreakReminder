#ifndef SYSTEMIDLEMONITOR_H
#define SYSTEMIDLEMONITOR_H

#include "isystemstatenotify.h"

class SystemIdleMonitor : public ISystemStateNotify
{
    Q_OBJECT
public:
    explicit SystemIdleMonitor(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // SYSTEMIDLEMONITOR_H
