#ifndef TRAYTIMER_H
#define TRAYTIMER_H

#include <QTimer>
#include <QTime>
#include <QProcess>
#include <QDebug>
#include "systemidlemonitor.h"

class TrayTimer : public QTimer
{
    Q_OBJECT
public:
    explicit TrayTimer(int interval = ONEHOUR, int breakTime = (5 * ONEMINUTE), int postponeTime = (10 * ONEMINUTE), QObject *parent = 0);

    enum TimeUnits { MILISECOND, SECOND, MINUTE, HOUR };
    enum MilisecondValues { ONESECOND = (1000), ONEMINUTE = (1000 * 60), ONEHOUR = (1000 * 60 * 60) };

    static int toMiliSeconds(int time, TimeUnits unit);
    static QString convertToString(int value, TimeUnits to, TimeUnits from=TrayTimer::MILISECOND);
    bool isWorkTime();

signals:

public slots:
    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void processReadyReadStandardError();
    void processReadyReadStandardOutput();
    void processStarted();
    void processStateChanged(QProcess::ProcessState newState);
    void later();
    void sooner();
    void stop();
    void start();
    void start(int msec);
    int remainingTime() const;
    void restart();

private slots:
    void timerTimeout();

private:
    void killOsd();


    const int mInterval;
    const int mBreakTime;
    const int mPostponeTime;

    QProcess process;
    QTime mStartTime;
    QTimer mBreakTimeTimer;
    IdleSystemMonitor* mIdleMonitor;

};

#endif // TRAYTIMER_H
