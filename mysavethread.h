#ifndef MYSAVETHREAD_H
#define MYSAVETHREAD_H

#include <QThread>

#include "activity.h"
#include "quicklogging.h"

class MySaveThread : public QThread
{
    Q_OBJECT
public:
    explicit MySaveThread(QObject *parent = nullptr);
public:
    Activity *act;
    QuickLogging *quick;
    void run();
};

#endif // MYSAVETHREAD_H
