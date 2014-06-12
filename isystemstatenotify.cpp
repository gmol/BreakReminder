#include "isystemstatenotify.h"

ISystemStateNotify::ISystemStateNotify(QObject *parent) :
    QObject(parent), mIdle(false)
{
}
