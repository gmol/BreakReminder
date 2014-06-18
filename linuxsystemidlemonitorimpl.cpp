#include "linuxsystemidlemonitorimpl.h"
#include <QTime>
#include <X11/extensions/scrnsaver.h>
#include "traytimer.h"

LinuxSystemIdleMonitorImpl::LinuxSystemIdleMonitorImpl(int idleTime, int monitoringInterval, QObject *parent) :
    SystemIdleMonitorImpl(idleTime, monitoringInterval, parent)
{
    dpy = XOpenDisplay(0);
}


void LinuxSystemIdleMonitorImpl::monitor()
{

    if (!dpy) {
        mIdle = false;
    }

    /*
      bool _idleDetectionPossible;
      int event_base, error_base;
      if(XScreenSaverQueryExtension(QX11Info::display(), &event_base, &error_base))
          _idleDetectionPossible = true;
      else
          _idleDetectionPossible = false
      printf("%u\n", _idleDetectionPossible);
    */
    XScreenSaverInfo *info = XScreenSaverAllocInfo();
    XScreenSaverQueryInfo(dpy, DefaultRootWindow(dpy), info);

    qDebug() << "LinuxSystemIdleMonitorImpl::monitor() at" << QTime::currentTime().toString("hh:mm:ss") << ". System was idle for " << ((info->idle + 500) / TrayTimer::ONESECOND) << " seconds";

    if (info->idle > mIdleTime) {
        mIdle = true;
        qDebug() << "System is idle";

    }

    if (mIdle) {
        if (info->idle < mIdleTime) {
            mIdle = false;
            qDebug() << "User is back";
            emit notifyBusyAgain();
        }
    }

}
