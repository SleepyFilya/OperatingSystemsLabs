#pragma once

#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include <QObject>
#include <QString>
#include <QVector>

#include <windows.h>
#include "accumulatorpi.h"
#include "threadentity.h"

//using ThreadId = int;
class ThreadEntity;

class ThreadManager : public QObject
{
    Q_OBJECT
public:
    explicit ThreadManager(QObject *parent = nullptr);
    ~ThreadManager();

    /*ThreadId*/ int createThread();
    void increaseThreadPriority(/*ThreadId*/ int threadId);
    void decreaseThreadPriority(/*ThreadId*/ int threadId);
    void pauseThread(/*ThreadId*/ int threadId);
    void resumeThread(/*ThreadId*/ int threadId);
    void deleteThread(/*ThreadId*/ int threadId);

    QString updateStatus();

signals:

public slots:

private:
    QVector<ThreadEntity*> _pThreadEntities;
    /*ThreadId*/ int _pIdCount;
    bool _pNoInfo;
    AccumulatorPi _pAccumulator;

    QVector<ThreadEntity*>::iterator findThread(/*ThreadId*/ int threadId);
};

#endif // THREADMANAGER_H
