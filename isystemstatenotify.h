#ifndef ISYSTEMSTATENOTIFY_H
#define ISYSTEMSTATENOTIFY_H

#include <QObject>
#include <QDebug>

class ISystemStateNotify : public QObject
{
    Q_OBJECT
public:
    explicit ISystemStateNotify(QObject *parent = 0);
    bool isIdle() { return mIdle; }
    
signals:
    void notifyIdle();
    void notifyBusyAgain();
    
public slots:
protected:
    bool mIdle;
    
};

#endif // ISYSTEMSTATENOTIFY_H
