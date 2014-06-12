#include "systemidlemonitor.h"
#include "linuxsystemidlemonitorimpl.h"

SystemIdleMonitor::SystemIdleMonitor(QObject *parent) :
    ISystemStateNotify(parent)
{
#ifdef Q_WS_X11
    mImpl = new LinuxSystemIdleMonitorImpl(10000, 2000, this);
#endif

#ifdef Q_WS_WIN
    exit(1);
#endif

    connect(mImpl, SIGNAL(notifyBusyAgain()), this, SIGNAL(notifyBusyAgain()));
    connect(mImpl, SIGNAL(notifyIdle()), this, SIGNAL(notifyIdle()));
}
