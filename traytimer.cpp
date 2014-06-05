#include "traytimer.h"
#include <QTime>

TrayTimer::TrayTimer(int interval, int postponeTime, QObject *parent) :
    QTimer(parent),  mInterval(interval), mPostponeTime(postponeTime)
{
    qDebug() << "TrayTimer: Interval set:" << interval << ", postpone time:" << postponeTime;
    setInterval(interval);
    connect(this, SIGNAL(timeout()), this, SLOT(timerTimeout()));
    setSingleShot(true);
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert("FONT", "-adobe-helvetica-bold-r-normal--34-240-100-100-p-182-iso8859-1");
    env.insert("DISPLAY", ":0");
    this->process.setProcessEnvironment(env);
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
    qDebug() << "Timer timeout after " << interval() << " msec at " << QTime::currentTime().toString("hh:mm:ss");
    setInterval(mInterval);
    qDebug() << "Start for "<< interval() << " msec";

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

    start();
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
    start(mPostponeTime);
}

void TrayTimer::stop() {
    killOsd();
    QTimer::stop();
}

void TrayTimer::start() {
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
