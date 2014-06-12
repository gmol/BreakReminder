#include "traytimer.h"
#include <QTime>
#include "systemidlemonitor.h"

TrayTimer::TrayTimer(int interval, int breakTime, int postponeTime, QObject *parent) :
    QTimer(parent), mInterval(interval), mBreakTime(breakTime), mPostponeTime(postponeTime)
{
    mIdleMonitor = new SystemIdleMonitor(this);
    connect(mIdleMonitor, SIGNAL(notifyBusyAgain()), this, SLOT(restart()));

    qDebug() << "TrayTimer: Interval set:" << interval << ", postpone time:" << postponeTime;
    setInterval(interval);
    connect(this, SIGNAL(timeout()), this, SLOT(timerTimeout()));
    setSingleShot(true);
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert("FONT", "-adobe-helvetica-bold-r-normal--34-240-100-100-p-182-iso8859-1");
    env.insert("DISPLAY", ":0");
    this->process.setProcessEnvironment(env);
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
    qDebug() << "Break starts after " << convertToString(interval(), MILISECOND, MINUTE) << " minutes at " << QTime::currentTime().toString("hh:mm:ss");
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

void TrayTimer::postpone() {
    qDebug() << "postpone()";
    stop();
    start(interval() - mStartTime.elapsed() + mPostponeTime);
}

void TrayTimer::stop() {
    killOsd();
    QTimer::stop();
}

void TrayTimer::start() {
    qDebug() << "Break finished after " << convertToString(mBreakTimeTimer.interval(), MILISECOND, MINUTE) << " minutes at " << QTime::currentTime().toString("hh:mm:ss");
    mStartTime.start();
    QTimer::start();
}

void TrayTimer::start(int msec) {
    mStartTime.start();
    QTimer::start(msec);
}

int TrayTimer::remainingTime() const {
    return interval() - mStartTime.elapsed() + 1;
}

void TrayTimer::restart() {
    qDebug() << "restart()";
    stop();
    start(mInterval);
}

QString TrayTimer::convertToString(int value, TimeUnits from, TimeUnits to) {

    const int PRECISION = 2;
    // convert to miliseconds
    double microSec = -1;
    switch (from) {
    case MICROSECOND:
        microSec = value / 1000.0;
    case MILISECOND:
        // do nothing
        break;
    case SECOND:
        value = value * 1000;
        break;
    case MINUTE:
        value = value * 60 * 1000;
        break;
    case HOUR:
        value = value * 60 * 60 * 1000;
    default:
        return QString::number(-1);
    }

    switch (to) {
    case MICROSECOND:
        return QString::number(microSec, 'G', PRECISION);
    case MILISECOND:
        return QString::number(value);
    case SECOND:
        return QString::number((value / 1000.0), 'G', PRECISION);
    case MINUTE:
        return QString::number((value / 1000.0 / 60.0), 'G', PRECISION);
    case HOUR:
        return QString::number((value / 1000.0 / 60.0 / 60.0), 'G', PRECISION);
    }

    return QString::number(-1);
}

int TrayTimer::toMiliSeconds(int time, TimeUnits unit)
{

    switch(unit) {
    case MICROSECOND:
        time = time / 1000;
        break;
    case MILISECOND:
        // do nothing
        break;
    case SECOND:
        time = time * 1000;
        break;
    case MINUTE:
        time = time * 1000 * 60;
        break;
    case HOUR:
        time = time * 1000 * 60 * 60;
        break;
    default:
        time = -1;
        break;
    }
    return time;
}
