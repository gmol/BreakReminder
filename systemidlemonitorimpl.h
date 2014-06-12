#ifndef SYSTEMIDLEMONITORIMPL_H
#define SYSTEMIDLEMONITORIMPL_H

#include <QTimer>
#include "isystemstatenotify.h"

class SystemIdleMonitorImpl : public ISystemStateNotify
{
    Q_OBJECT
public:
    explicit SystemIdleMonitorImpl(int idleTime, int monitoringInterval, QObject *parent = 0);
    
signals:
    
public slots:
    virtual void monitor() = 0;

protected:
    const int mIdleTime;
private:
    QTimer mTimer;

    
};

#endif // SYSTEMIDLEMONITORIMPL_H
