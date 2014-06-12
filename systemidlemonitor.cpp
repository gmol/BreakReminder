#include "systemidlemonitor.h"
#include "linuxsystemidlemonitorimpl.h"

SystemIdleMonitor::SystemIdleMonitor(QObject *parent) :
    ISystemStateNotify(parent)
{
    // mytodo
    mImpl = new LinuxSystemIdleMonitorImpl(10000, 2000, this);
}
