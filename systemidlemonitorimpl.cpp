#include "systemidlemonitorimpl.h"

SystemIdleMonitorImpl::SystemIdleMonitorImpl(int idleTime, int monitoringInterval, QObject *parent) :
    ISystemStateNotify(parent), mIdleTime(idleTime)
{
    QObject::connect(&mTimer, SIGNAL(timeout()), this, SLOT(monitor()));
    mTimer.start(monitoringInterval);
}
