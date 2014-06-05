#ifndef TRAYTIMER_H
#define TRAYTIMER_H

#include <QTimer>
#include <QTime>
#include <QProcess>
#include <QDebug>

class TrayTimer : public QTimer
{
    Q_OBJECT
public:
    explicit TrayTimer(int interval = (60 * 60 * 1000), int postponeTime = (10 * 60 * 1000), QObject *parent = 0);

signals:

public slots:
    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void processReadyReadStandardError();
    void processReadyReadStandardOutput();
    void processStarted();
    void processStateChanged(QProcess::ProcessState newState);
    void postpone();
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
    const int mPostponeTime;
    QProcess process;
    QTime mStartTime;
};

#endif // TRAYTIMER_H
