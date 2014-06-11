/* gcc -o getIdleTime getIdleTime.c -lXss */
#include <X11/extensions/scrnsaver.h>
#include <stdio.h>

#include <unistd.h>

int main(void) {
  Display *dpy = XOpenDisplay(NULL);

  if (!dpy) {
    return(1);
  }

/*    bool _idleDetectionPossible;
    int event_base, error_base;
    if(XScreenSaverQueryExtension(QX11Info::display(), &event_base, &error_base))
        _idleDetectionPossible = true;
    else
        _idleDetectionPossible = false
    printf("%u\n", _idleDetectionPossible);
*/
  while(true)  {
      XScreenSaverInfo *info = XScreenSaverAllocInfo();
      XScreenSaverQueryInfo(dpy, DefaultRootWindow(dpy), info);
      unsigned int microseconds = 2000000;

      usleep(microseconds);
      printf("%u\n", (info->idle + 500) / 1000);
  }

  return(0);
}


/*
class abstract ISystemStateNotify {

    void notifyIdle() = 0;
    vpod notifyBusyAgain() = 0;
}
class SystemIdleMonitor : public ISystemStateNotify {
public:    
    SystemIdleMonitor() {
        switch (system) {
        case Linux:
            impl = new LinuxImplementator();
        break;
        case WIN:
            impl = new XpImplementator();
        break;
        }

//        connect(impl, SIGNAL(notifyIdle), this, SIGNAL(notifyIdle()));
//        connect(impl, SIGNAL(notifyBusyAgain), this, SIGNAL(notifyBusyAgain()));
    }
    void notifyIdle() { emit idle() ;}
    vpod notifyBusyAgain() { emit busyAgain(); }

SIGNALS:
    void idle();
    void busyAgain();

pirvate:
    Implementator impl;
}

class Implementator {
    ISystemStateNotify mCallback;
private:
    void setCallback(ISystemStateNotify calback) {
        mCallback = calback;
    }

}


class XpImplementator : public Implementator {
}
class LinuxImplementator : public Implementator {
}

*/




/**************************
  ** OR
***************************   
class ISystemStateNotify {
public signals:
    void notifyIdle() = 0;
    vpod notifyBusyAgain() = 0;
}
class SystemIdleMonitor : public ISystemStateNotify {
public:    
    SystemIdleMonitor(int idleTime, TimeUnits unit) {

        switch (system) {
        case Linux:
            impl = new LinuxImplementator(idleTime);
        break;
        case WIN:
            impl = new XpImplementator(idleTime);
        break;
        }

        connect(impl, SIGNAL(notifyIdle), this, SIGNAL(notifyIdle()));
        connect(impl, SIGNAL(notifyBusyAgain), this, SIGNAL(notifyBusyAgain()));
    }

pirvate:
    ISystemStateNotify impl;
}


class Implementator : public ISystemStateNotify {
protected:
    bool mIdle;
    const int mIdleTime;
    Implementator(int idleImte) : mIdle(false), mIdleTime(idleTime){
        connect(mTimer, SIGNAL(timeout), this, SLOT(monitor));
    }
    QTimer mTimer;
    void monitor() = 0;
    
}

class XpImplementator : public Implementator {
friend class SystemIdleMonitor;
    private:
    XpImplementator() {
    }
}
class LinuxImplementator : public ISystemStateNotify {
friend class SystemIdleMonitor;
private:
    LinuxImplementator() {
    }
}

toMiliseconds(int time, TimeUnits unit)
        switch(unit) {
            case MICROSECOND:
            break;
            case MILISECOND:
            // do nothing
            break;
            case SECOND:
                idleTime = idleTime * 1000;
            break;
            case MINUTE:
                idleTime = idleTime * 1000 * 60;                
            break;
            case HOUR:
                idleTime = idleTime * 1000 * 60 * 60;                
            break;
            default:
            break;
        }


*/
