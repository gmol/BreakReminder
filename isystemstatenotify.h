#ifndef ISYSTEMSTATENOTIFY_H
#define ISYSTEMSTATENOTIFY_H

#include <QObject>

class ISystemStateNotify : public QObject
{
    Q_OBJECT
public:
    explicit ISystemStateNotify(QObject *parent = 0);
    
signals:
    void notifyIdle();
    void notifyBusyAgain();
    
public slots:
    
};

#endif // ISYSTEMSTATENOTIFY_H
