#include "systemidlemonitorimpl.h"

SystemIdleMonitorImpl::SystemIdleMonitorImpl(int idleTime, QObject *parent) :
    ISystemStateNotify(parent), mIdle(false), mIdleTime(idleTime)
{
    QObject::connect(&mTimer, SIGNAL(timeout()), this, SLOT(monitor()));
}
