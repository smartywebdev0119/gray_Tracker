#include "mysavethread.h"

MySaveThread::MySaveThread(QObject *parent) : QThread(parent)
{

}

void MySaveThread::run(){
    act->saveScreenshots();
    quick->saveTasks();
}
