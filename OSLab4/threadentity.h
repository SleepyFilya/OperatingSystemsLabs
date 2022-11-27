#pragma once
//#ifndef THREADENTITY_H
//#define THREADENTITY_H

//#include <QThread>
#include <thread>

#include "threadmanager.h"
#include "mathmethod.h"

class ThreadEntity
{
public:
    ThreadEntity(int id, AccumulatorPi* pAccumulator);
    ~ThreadEntity();

    void pause();
    void resume();

    void increasePriority();
    void decreasePriority();

    QString getStatus();

    int getId() const { return _pId; }
    void threadProc();

signals:

public slots:

private:
    int _pId;
    MathMethod _pMathMetod;
    AccumulatorPi* _pAccumulator;
    /*std::thread**/ HANDLE _pThread;
    int _pPriority;
    std::atomic_bool _pNeedTerminate;
    std::atomic_int _pCalcsCount;
    int _pLastCalcs;
    bool _pPaused;


};

//#endif // THREADENTITY_H
