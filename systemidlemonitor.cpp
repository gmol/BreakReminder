#include "systemidlemonitor.h"
#include "linuxsystemidlemonitorimpl.h"
#include "xpsystemidlemonitorimpl.h"
#include "traytimer.h"

IdleSystemMonitor::IdleSystemMonitor(int idleTime, int monitoringInterval, QObject *parent) :
    ISystemStateNotify(parent)
{
    qDebug() << "Idle time is set to " << TrayTimer::convertToString(idleTime, TrayTimer::MINUTE)
             << ". Idle system monitoring is done every " << TrayTimer::convertToString(monitoringInterval, TrayTimer::MINUTE);

    qDebug() << "Choose implementation of Idle System Monitor ...";
#ifdef Q_WS_X11
    qDebug() << "Linux implementation of Idle System Monitor";
    mImpl = new LinuxSystemIdleMonitorImpl(idleTime, monitoringInterval, this);
#else
    qWarning() << "Windows platform is not supported at the moment";
    mImpl = new XpSystemIdleMonitorImpl(idleTime, monitoringInterval, this);
#endif

    connect(mImpl, SIGNAL(notifyBusyAgain()), this, SIGNAL(notifyBusyAgain()));
    connect(mImpl, SIGNAL(notifyIdle()), this, SIGNAL(notifyIdle()));
}
