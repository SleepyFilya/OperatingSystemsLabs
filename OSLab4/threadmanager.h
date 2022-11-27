#pragma once

#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include <QObject>
#include <QString>
#include <QVector>

#include <windows.h>
#include "accumulatorpi.h"
#include "threadentity.h"

class ThreadEntity;

class ThreadManager : public QObject
{
    Q_OBJECT
public:
    explicit ThreadManager(QObject *parent = nullptr);
    ~ThreadManager();

    int createThread();
    void increaseThreadPriority(int threadId);
    void decreaseThreadPriority(int threadId);
    void pauseThread(int threadId);
    void resumeThread(int threadId);
    void deleteThread(int threadId);

    QString updateStatus();

signals:

public slots:

private:
    QVector<ThreadEntity*> _pThreadEntities;
    int _pIdCount;
    bool _pNoInfo;
    AccumulatorPi _pAccumulator;

    QVector<ThreadEntity*>::iterator findThread(int threadId);
};

#endif // THREADMANAGER_H
