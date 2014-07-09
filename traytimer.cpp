#include "traytimer.h"
#include <QTime>
#include "systemidlemonitor.h"

TrayTimer::TrayTimer(int interval, int breakTime, int postponeTime, QObject *parent) :
    QTimer(parent), mInterval(interval), mBreakTime(breakTime), mPostponeTime(postponeTime)
{
    // idle system monitor settins
    mIdleMonitor = new IdleSystemMonitor(30 * ONEMINUTE, 1 * ONEMINUTE, this);
    connect(mIdleMonitor, SIGNAL(notifyBusyAgain()), this, SLOT(restart()));

    // main timer settings
    qDebug() << "TrayTimer: Interval set:" << convertToString(interval, SECOND)  << ", postpone time:" << convertToString(postponeTime, SECOND) << " [s]";
    setSingleShot(true);
    setInterval(interval);
    connect(this, SIGNAL(timeout()), this, SLOT(timerTimeout()));

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert("FONT", "-adobe-helvetica-bold-r-normal--34-240-100-100-p-182-iso8859-1");
    env.insert("DISPLAY", ":0");
    this->process.setProcessEnvironment(env);

    // breakTime timer settings
    mBreakTimeTimer.setSingleShot(true);
    connect(&mBreakTimeTimer, SIGNAL(timeout()), this, SLOT(start()));
}

void TrayTimer::processFinished(int exitCode, QProcess::ExitStatus exitStatus) {
    qDebug() << "processFinished with exit code:" << exitCode << " and exit status:" << exitStatus;
}

void TrayTimer::processReadyReadStandardError() {
    qDebug() << "STDERR: " << process.readAllStandardError();
}

void TrayTimer::processReadyReadStandardOutput() {
    qDebug() << "STDOUT:" << process.readAllStandardOutput();
}

void TrayTimer::processStarted() {
    qDebug() << "processStarted";
}

void TrayTimer::processStateChanged(QProcess::ProcessState newState) {

    switch (newState) {
    case QProcess::NotRunning:
        qDebug() << "Process: NotRunning";
        break;
    case QProcess::Starting:
        qDebug() << "Process: Starting";
        break;
    case QProcess::Running:
        qDebug() << "Process: Running";
        break;
    default:
        break;
    }
}

void TrayTimer::timerTimeout() {
    qDebug() << "Break starts after " << convertToString(interval(), MINUTE) << " minutes at " << QTime::currentTime().toString("hh:mm:ss");
    setInterval(mInterval);

    // display OSD
    QString program = "bash";
    qDebug() << "Command:" << program;
    QString txt = "GO FOR BREAK";
    QString osdCmd = "echo " + txt + " | /usr/bin/osd_cat --font=$FONT  --color=yellow --pos=top --align=right --delay=300 --indent=920 --offset 200 -shadow=0 --shadowcolour=white --outline=1 --outlinecolour=red  --lines=5 --wait";
    QStringList arguments;
    arguments << "-c" << osdCmd;
    qDebug() << "Process state(" << process.state() << ")" ;
    if (process.state() == QProcess::NotRunning) {
        process.start(program, arguments);
    } else {
        qDebug() << "Can not run another process before finished the previous one";
    }

    mBreakTimeTimer.start(mBreakTime);
    mStartTime.start();
}

void TrayTimer::killOsd() {
    QString program = "bash";
    QStringList arguments;
    arguments << "-c" <<"pkill osd_cat";
    QProcess p;
    p.start(program, arguments);
    process.kill();
    if (!p.waitForFinished())
        qDebug() << "pkill failed:" << p.errorString();
    else
        qDebug() << "pkill output:" << p.readAll();
}

void TrayTimer::later() {
    qDebug() << "later() at " << QTime::currentTime().toString("hh:mm:ss") ;
    stop();
    int remainingtime = remainingTime();
    int msec = remainingtime + mPostponeTime;
    qDebug() << "Remaining time " << convertToString(remainingtime, MINUTE) << "minutes. Next break in later in" << convertToString(msec, MINUTE) << "minutes";
    start(msec);
}

void TrayTimer::sooner() {
    qDebug() << "sooner() at " << QTime::currentTime().toString("hh:mm:ss") ;
    stop();
    int remainingtime = remainingTime();
    int msec = 0;

    if (remainingtime < (10 * ONEMINUTE)) {
        qDebug() << "The next break will be sooner than in 10 minutes";
        msec = remainingtime / 2;
    } else {
        msec = remainingtime - mPostponeTime;
    }
    qDebug() << "Remaining time " << convertToString(remainingtime, MINUTE) << "minutes. Next break will be sooner in" << convertToString(msec, MINUTE) << "minutes";
    start(msec);
}

void TrayTimer::stop() {
    killOsd();
    QTimer::stop();
}

void TrayTimer::start() {
    qDebug() << "Break finished after " << convertToString(mBreakTimeTimer.interval(), MINUTE) << " minutes at " << QTime::currentTime().toString("hh:mm:ss");
    mStartTime.start();
    QTimer::start();
}

void TrayTimer::start(int msec) {
    mStartTime.start();
    QTimer::start(msec);
}

int TrayTimer::remainingTime() const {

    if (isActive()) {
        // work time
        return interval() - mStartTime.elapsed() + 1;
    } else {
        // break time
        return mBreakTimeTimer.interval() - mStartTime.elapsed() + 1;
    }
}

void TrayTimer::restart() {
    qDebug() << "restart(). Interval:" << convertToString(mBreakTimeTimer.interval(), MINUTE) << ". Remaining time:" << convertToString(remainingTime(), MINUTE);
    stop();
    start(mInterval);
}

bool TrayTimer::isWorkTime() {
    return isActive();
}

QString TrayTimer::convertToString(int value, TimeUnits to, TimeUnits from) {

    const int PRECISION = 6;
    // convert to miliseconds
    switch (from) {
    case MILISECOND:
        // do nothing
        break;
    case SECOND:
        value = value * ONESECOND;
        break;
    case MINUTE:
        value = value * ONEMINUTE;
        break;
    case HOUR:
        value = value * ONEHOUR;
    default:
        return QString::number(-1);
    }

    switch (to) {
    case MILISECOND:
        return QString::number(value);
    case SECOND:
        return QString::number((value / ONESECOND), 'g', PRECISION);
    case MINUTE:
        return QString::number((value / ONEMINUTE), 'g', PRECISION);
    case HOUR:
        return QString::number((value / ONEHOUR), 'g', PRECISION);
    }

    return QString::number(-1);
}

int TrayTimer::toMiliSeconds(int time, TimeUnits unit)
{

    switch(unit) {    
    case MILISECOND:
        // do nothing
        break;
    case SECOND:
        time = time * ONESECOND;
        break;
    case MINUTE:
        time = time * ONEMINUTE;
        break;
    case HOUR:
        time = time * ONEHOUR;
        break;
    default:
        time = -1;
        break;
    }
    return time;
}
