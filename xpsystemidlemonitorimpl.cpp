#include "xpsystemidlemonitorimpl.h"

XpSystemIdleMonitorImpl::XpSystemIdleMonitorImpl(int idleTime, int monitoringInterval, QObject *parent) :
    SystemIdleMonitorImpl(idleTime, monitoringInterval, parent)
{
}

void XpSystemIdleMonitorImpl::monitor()
{
    qWarning() << "Idle system monitoring is not implemented for Windows platform yet";

}
